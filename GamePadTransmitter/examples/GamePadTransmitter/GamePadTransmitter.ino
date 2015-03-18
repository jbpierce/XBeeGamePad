
#include <GamePadTransmitter.h>

// Construct a GamePadTransmitter
GamePadTransmitter gamePadTransmitter;

void setup() {
  // Intialize GamePadTransmitter I/O
  gamePadTransmitter.begin(9600);
}

void loop() {
  // poll the transmitter
  gamePadTransmitter.update();
}
