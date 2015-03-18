#include <SoftwareSerial.h>
#include <GamePad.h>

// Construct a SoftwareSerial on pins 2 and 3 for the XBee
SoftwareSerial xbee(2, 3); // RX, TX
// Construct a GamePad with the XBee SoftwareSerial
GamePad gamePad(&xbee);

unsigned long timer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xbee.begin(9600);
}

void loop() {
  // update the GamePad's state
  gamePad.update();
  
  // Every 100 milliseconds, we'll write
  // out the state of our joystick axes.
  if (millis() - timer > 100) {
    Serial.print(gamePad.leftAxisX());
    Serial.print(" ");
    Serial.print(gamePad.leftAxisY());
    Serial.print(" ");
    Serial.print(gamePad.rightAxisX());
    Serial.print(" ");
    Serial.print(gamePad.rightAxisY());
    Serial.println();
    timer = millis();    
  }
}
