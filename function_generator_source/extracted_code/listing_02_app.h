# ifndef APP_H
# define APP_H
// --------------------
// Includes
// --------------------
# include < Arduino .h >
// --------------------
// Public Types
// --------------------
// Supported waveform types
typedef enum {
WAVE_SINE = 0 ,
WAVE_SQUARE ,
WAVE_TRIANGLE ,
WAVEFORM_COUNT
// Future : SAW , NOISE , etc .
} WaveformType ;
// Output channel selection
typedef enum {
CHANNEL_NONE = 0 ,
CHANNEL_1 ,
CHANNEL_2 ,
CHANNEL_BOTH ,
CHANNEL_MODE_COUNT
} ChannelMode ;
// High - level application mode
typedef enum {
APP_VIEW_MODE = 0 , // Normal operation
APP_EDIT_MODE // Editing parameters
} AppMode ;
// What parameter is currently being edited
// * might need changes
typedef enum {
EDIT_NONE = 0 ,
EDIT_FREQ ,
EDIT_AMP ,
EDIT_DC ,
EDIT_TARGET_COUNT
} EditTarget ;
// Magnitude for numeric input
typedef enum {
MAG_HZ = 0 ,
MAG_KHZ ,
MAG_MHZ ,
MAG_COUNT
} Magnitude ;
typedef struct {
float frequency ;
float amplitude ;
float dc_offset ;
WaveformType waveform ;
} ChannelState ;
// --------------------
// Application State
// --------------------
typedef struct {
ChannelState ch [2]; // ch [0] = CH1 , ch [1] = CH2
ChannelMode output_mode ; // NONE / CH1 / CH2 / BOTH
int active_channel ; // 0 or 1 (UI focus )
AppMode mode ; // view or edit mode
EditTarget edit_target ; // What is being edited
int digits [4]; // 4 - digit input buffer
int digit_index ; // Active digit (0 3 )
Magnitude magnitude ; // Hz / kHz / MHz (or power of 10
multiplier )
bool edit_negative ; // Sign for current edit buffer
bool output_enabled ; // * might not be needed
} AppState ;
// --------------------
// Public API
// --------------------
// Initialize the application ( called once from setup )
void app_init ( void ) ;
// Main application loop ( called repeatedly from loop )
void app_run ( void ) ;
// Get current application state (read - only access )
const AppState * app_get_state ( void ) ;
# endif // APP_H
