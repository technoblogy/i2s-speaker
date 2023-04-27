/* I2S Speaker for QT Py - Internet Radio
   See: http://www.technoblogy.com/show?4ECO.
*/

#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"

const char *urls[] = {
  "https://stream.resonance.fm/resonance",  // Resonance FM, London
  "http://stream.srg-ssr.ch/m/rsj/mp3_128"  // Radio Swiss Jazz
};
const char *wifi = "Manticore";
const char *password = "silversurfer2";

URLStream urlStream(wifi, password);
AudioSourceURL source(urlStream, urls, "audio/mp3");
I2SStream i2s;
MP3DecoderHelix decoder;
AudioPlayer player(source, i2s, decoder);

// #define BUTTON 0; // BOOT button; uncomment for ESP32-S2

void setup() {
  auto cfg = i2s.defaultConfig(TX_MODE);
  // The I2S Speaker board uses these pin positions for I2S:
  cfg.pin_bck  = MISO;
  cfg.pin_ws   = MOSI;
  cfg.pin_data = SCK;
  pinMode(BUTTON, INPUT_PULLUP);
  i2s.begin(cfg);
  player.setVolume(0.25); // 1.0 maximum
  player.begin();
}

void loop() {
  // Moves to the next url when you press BOOT
  if (digitalRead(BUTTON) == 0) {
    player.next();
    while(digitalRead(BUTTON) == 0);
  }
  player.copy();
}
