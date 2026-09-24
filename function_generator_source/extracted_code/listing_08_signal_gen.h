# ifndef SIGNAL_GEN_H
# define SIGNAL_GEN_H
# include < Arduino .h >
# include " ../ app / app . h "
// Initialize signal generator hardware
void signal_init ( void ) ;
// Per - channel setters
void signal_set_frequency (int ch , float freq ) ;
void signal_set_amplitude (int ch , float amp ) ;
void signal_set_offset (int ch , float offset ) ;
void signal_set_waveform (int ch , WaveformType w ) ;
// Output routing
void signal_set_output_mode ( ChannelMode mode ) ;
# endif
.10 Web-Based Control Interface
In addition to the physical control interface, the system also provides a web-based interface that allows the function generator to be controlled remotely using a browser. The
ESP32 microcontroller hosts a lightweight web server which serves a user interface to
connected devices over Wi-Fi.
This interface allows the user to monitor parameters and control the function generator
without requiring a dedicated mobile application.
.10.1 Web Application Architecture
The web control system consists of two main components:
• Frontend Interface (index.html) – A browser-based user interface that allows
users to interact with the device.
• Backend Firmware (sketch.ino) – The ESP32 firmware that hosts the web server
and processes requests from the web interface.
.10.2 Web Interface Implementation
