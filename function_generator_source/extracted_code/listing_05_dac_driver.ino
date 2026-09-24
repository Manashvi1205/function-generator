# include < MD_AD9833 .h >
# include < SPI .h >
// --- PIN DEFINITIONS ---
const uint8_t FNC_PIN = 5; // GPIO 5 ( Chip Select )
const uint8_t LED_PIN = 2; // GPIO 2 ( Onboard LED )
// Create the generator object
MD_AD9833 gen ( FNC_PIN ) ;
void setup () {
// 1. Initialize Serial
Serial . begin (115200) ;
while (! Serial ) ;
Serial . println ( " \n - - - ␣ ESP32 ␣ AD9833 ␣ Square ␣ Wave ␣ Generator ␣ ---" ) ;
// 2. CRITICAL FIX : Configure the LED pin as an Output
pinMode ( LED_PIN , OUTPUT ) ;
// 3. Initialize ESP32 Hardware SPI
// SCK =18 , MISO =19 , MOSI =23 , SS =5
SPI . begin (18 , 19 , 23 , 5) ;
// 4. Initialize the AD9833
gen . begin () ;
// 5. Force Reset ( Clear registers )
gen . setMode ( MD_AD9833 :: MODE_OFF ) ;
delay (10) ;
// 6. Set Output to SQUARE WAVE ( Changed from MODE_SINE )
gen . setMode ( MD_AD9833 :: MODE_SINE ) ;
// gen. setMode ( MD_AD9833 :: MODE_SQUARE1 );
// gen. setMode ( MD_AD9833 :: MODE_TRIANGLE );
// 7. Set Frequency to 1 kHz (1000.0 Hz)
gen . setFrequency ( MD_AD9833 :: CHAN_0 , 10.0) ;
Serial . println ( " Status : ␣ Generating ␣ 1 ␣ kHz ␣ Square ␣ Wave " ) ;
}
void loop () {
// 8. Blink the LED explicitly
digitalWrite ( LED_PIN , HIGH ) ; // LED ON
delay (500) ; // Wait 0.5 second
digitalWrite ( LED_PIN , LOW ) ; // LED OFF
delay (500) ; // Wait 0.5 second
}
.9.5 Input Handling
