/* I2S Speaker for QT Py - SD-Card MP3 Player
   See: http://www.technoblogy.com/show?4ECO.
*/

#include "AudioTools.h"
#include "AudioLibs/AudioSourceSD.h"
#include "AudioCodecs/CodecMP3Helix.h"

const char *startFilePath="/";
const char* ext="mp3";
AudioSourceSD source(startFilePath, ext, TX); // SS
I2SStream i2s;
MP3DecoderHelix decoder;
AudioPlayer player(source, i2s, decoder);

void setup() {
  // Move the SPI port to these pins:
  SPI.begin(SCL, SDA, A3, TX); // CLK, MISO, MOSI, SS

  auto cfg = i2s.defaultConfig(TX_MODE);
  // The I2S Speaker board uses these pin positions for I2S:
  cfg.pin_bck  = MISO;
  cfg.pin_ws   = MOSI;
  cfg.pin_data = SCK;
  i2s.begin(cfg);
  player.setVolume(0.25);
  player.setAutoNext(true);
  player.begin();
}

void loop() {
  player.copy();
}
