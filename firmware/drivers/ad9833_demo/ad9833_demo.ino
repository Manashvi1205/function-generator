#include <MD_AD9833.h>
#include <SPI.h>

const uint8_t FNC_PIN = 5;
const uint8_t LED_PIN = 2;

MD_AD9833 generator(FNC_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // ESP32 VSPI: SCK=18, MISO=19, MOSI=23, SS=5.
  SPI.begin(18, 19, 23, FNC_PIN);
  generator.begin();
  generator.setMode(MD_AD9833::MODE_OFF);
  delay(10);

  // Values follow Listing 5. Its comments and status text contradicted these calls.
  generator.setMode(MD_AD9833::MODE_SINE);
  generator.setFrequency(MD_AD9833::CHAN_0, 10.0);
  Serial.println("Generating a 10 Hz sine wave");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
