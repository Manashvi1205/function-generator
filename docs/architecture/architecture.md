# System architecture

## Evidence-backed blocks

The latest report consistently identifies these functional blocks:

1. **ESP32-WROOM-32** — central controller, local UI state, OLED rendering, SPI
   control, and Wi-Fi web server.
2. **Two AD9833 modules** — one DDS source per output channel for sine, square, and
   triangle waveforms.
3. **Signal conditioning** — filtering, buffering, amplification, and DC offset using
   high-speed op-amps. OPA810 and LM7171 are both discussed.
4. **Local interface** — monochrome OLED, numeric keypad, navigation/function buttons,
   physical amplitude controls, and offset potentiometers.
5. **Output interface** — two nominal 50 Ω BNC outputs.
6. **Remote interface** — an ESP32-hosted browser UI communicating through HTTP.

```text
                  ┌──────────────┐
keypad/buttons ──▶│              │── SPI ─▶ AD9833 CH1 ─┐
OLED ◀────────────│    ESP32     │── SPI ─▶ AD9833 CH2 ─┼──▶ analog stages ──▶ BNC
browser ◀─ Wi-Fi ─│              │── DAC ─▶ MUX ─────────┘
                  └──────────────┘       later enhancement
```

## Software split recorded in the report

- `app`: application state, edit modes, and channel selection
- `display`: OLED initialization and state rendering
- `drivers`: peripheral drivers and the AD9833 demonstration
- `input`: UI events and keypad mapping
- `signal`: channel frequency, amplitude, offset, waveform, and routing API
- web frontend: dual-channel controls and animated waveform preview
- web backend: access point, HTTP routes, JSON status, and in-memory state

Only declarations were supplied for most modular firmware components. The backend listing
contains serial-log placeholders where hardware integration would normally occur.

## Conflicting and evolving specifications

The report combines requirements, early design decisions, and later changes:

- Frequency appears as 2 Hz–2 MHz, 10 Hz–1 MHz in the web UI, and up to 2.5 MHz in
  meeting notes. AD9833 output is described as clean to approximately 1 MHz.
- Early requirements mention ±12 V input, while later meeting notes mention ±15 V.
  The specification section also describes a 12 V DC input.
- The OLED is described as both 1.3-inch/4-pin and 0.96-inch/7-pin in different sections.
- A 20-key interface is specified, but the extracted keypad mapping is 4×4.
- A digital potentiometer appears in an architecture figure; later work explicitly
  replaces it with a physical potentiometer.
- Early notes say the DAC would not be used; later enhancements use the ESP32 DAC for
  arbitrary waveforms through a multiplexer.

These are preserved as design history, not silently resolved into a new schematic.

## Missing integration details

The package does not establish:

- separate chip-select pin assignments for two AD9833 devices;
- OLED pins/address and exact controller;
- multiplexer type, pins, or analog routing;
- op-amp circuit values, gains, filters, compensation, or protection;
- amplitude/offset ADC pins and transfer functions;
- complete power-rail generation and grounding;
- implementations for the declared module interfaces.

Those details must be recovered from original project sources or established by a new,
reviewed hardware design before an integrated build is attempted.
