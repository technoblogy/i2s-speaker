/* I2S Speaker for QT Py - Bluetooth Speaker
   See: http://www.technoblogy.com/show?4ECO.
*/

#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dp_sink;
I2SStream i2s;

void setup() {
  auto cfg = i2s.defaultConfig(TX_MODE);
  // The I2S Speaker uses these pin positions for I2S:
  cfg.pin_bck  = MISO;
  cfg.pin_ws   = MOSI;
  cfg.pin_data = SCK;
  i2s.begin(cfg);
  a2dp_sink.start("QT Py Speaker");
}

void loop() {
}
