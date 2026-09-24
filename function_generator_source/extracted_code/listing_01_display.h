# ifndef DISPLAY_H
# define DISPLAY_H
# include < Arduino .h >
# include " ../ app / app . h " // For AppState
// Initialize display subsystem
void display_init ( void ) ;
// Update display based on current application state
void display_update ( const AppState * state ) ;
enum WaveType { W_SINE =0 , W_SQUARE =1 , W_TRI =2 };
enum Channel { CH1 =0 , CH2 };
struct ScreenState {
double freq = 1000.00;
WaveType wave = W_SINE ;
double amp = 5.00;
double offset = 0.00;
bool outOn = true ;
int cursorPos = 0;
bool editing = false ;
};
# endif // DISPLAY_H
.7 Hardware Design
The hardware architecture of the prototype consists of several functional blocks including
the controller, waveform generator, signal conditioning stage, and output interface.
A block diagram of the system architecture is included to show the interaction between
these modules.
Figure 15: Circuit diagram of the waveform generation system (placeholder)
ESP32
Controller
AD9833
DDS Generator
OPA810
Amplifier
MCP4131
Digital Potentiometer
BNC
Output
SPI
SPI
Analog Signal
Figure 16: Block diagram of the waveform generation hardware architecture
.8 Front Panel Usage
The front panel serves as the primary interface between the user and the function generator. It contains all input controls, display elements, and output connectors required for
operating the device.
The layout is designed to provide clear visibility of the displayed parameters while
allowing convenient access to the control elements.
The front panel includes the following components:
• OLED Display for displaying waveform parameters such as frequency and amplitude.
• Numeric Keypad for entering frequency values.
• Additional Control Buttons for navigation and waveform selection.
• Potentiometers for analog control of parameters such as amplitude or offset.
• ON/OFF Switch for powering the device.
• BNC Connectors for waveform output connections.
• Wire Slot for routing internal wiring to the electronics mounted inside the enclosure.
Figure 17: Annotated front panel layout showing keypad, OLED display, control buttons,
potentiometers, and cable routing slot.
Figure 18: Bottom section of the front panel showing the power switch and BNC output
connectors.
Figure 19: Electrical connections for the front panel components
.9 Firmware and Embedded Code
The firmware for the function generator is implemented in C and runs on the ESP32 microcontroller. The project follows a modular architecture where different subsystems such
as signal generation, display control, and input handling are separated into independent
modules.
.9.1 Firmware Directory Structure
The firmware is organized into multiple directories to improve maintainability and modularity.
• app – Main application logic and configuration
• display – OLED display control and GUI
• drivers – Hardware drivers for peripherals
• input – Input handling from keypad and controls
• signal – Waveform generation and signal processing
.9.2 Application Module
