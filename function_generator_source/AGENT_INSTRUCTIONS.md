# Function Generator Project — Agent Handoff

## Goal
Build a polished GitHub repository for the ESP32-based dual-channel function generator project from the materials in this package. Treat the report content as source material, not as a claim that every extracted code block is directly compilable.

## Source priority
1. `LATEST_INDEXED_REPORT_FULL_TEXT.txt` — complete text extracted from the latest indexed 109-page report (`ELP305_2__1___2_(1).pdf`).
2. `source_reports/ELP305_2__4_accessible_raw.pdf` — an older 105-page raw PDF version that was available for byte-level extraction; use it for original PDF pages and raster media.
3. `extracted_code/` — code listings extracted from the latest report. PDF extraction inserted spaces/wrapping, so reconstruct syntax carefully and do not silently invent missing code.
4. `assets/` — embedded images and rendered report pages.

## Recommended repository structure
```text
function-generator/
├── README.md
├── LICENSE
├── docs/
│   ├── report/
│   ├── architecture/
│   ├── hardware/
│   └── media/
├── firmware/
│   ├── app/
│   ├── display/
│   ├── drivers/
│   ├── input/
│   ├── signal/
│   └── main/
├── web/
│   └── index.html
├── hardware/
│   ├── schematics/
│   ├── bom/
│   └── enclosure/
├── media/
├── test/
└── .github/
```

## Project facts to preserve
- ESP32 is the central controller.
- AD9833 is used for DDS waveform generation; report describes sine, square, and triangle generation.
- OLED display, keypad, control buttons/potentiometers, BNC outputs, and signal-conditioning op-amps are part of the system.
- The report describes Wi-Fi/web control, with an ESP32 web server and browser UI.
- Later enhancements include arbitrary waveform support using the ESP32 DAC plus AD9833 with a mux, additional waveform options, improved amplitude control, Wi-Fi access information, and a redesigned enclosure.

## Important evidence handling
- Do not claim that CAD source files, Gerbers, PCB files, videos, or original standalone firmware repositories were present in the report unless a source file is actually included in this package.
- The report itself contains figures/photos and code listings, but the latest 109-page PDF could not be copied as raw bytes. Its complete extracted text is included.
- The accessible raw PDF is an earlier 105-page version and is included specifically so the agent has the original PDF plus extracted media.
- No explicit video URL or embedded video file was found in the report.

## Suggested README sections
Overview → Features → System Architecture → Hardware → Firmware → Web Interface → Waveform Generation → Enclosure → Bill of Materials → Setup/Build → Usage → Testing → Results → Media → Team/Contributions → Future Work → References.
