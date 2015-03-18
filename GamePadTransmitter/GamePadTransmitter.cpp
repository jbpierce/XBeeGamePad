//
//  GamePadTransmitter.cpp
//  
//
//  Created by Jason Pierce on 3/17/15.
//
//

#include "Arduino.h"
#include "GamePadTransmitter.h"

#define shakeMotorPin 2


/*** GamePadTransmitter Implementation ***/

GamePadTransmitter::GamePadTransmitter() {
    _refreshInterval = 0;
    _timer = 0;
}

void GamePadTransmitter::begin(int baudRate) {
    Serial1.begin(baudRate);
    
    for(int i = 3; i < 17; i++) pinMode(i, INPUT); 
    pinMode(shakeMotorPin, OUTPUT);
    digitalWrite(shakeMotorPin, LOW);  // Stop shaking of the gamepad    
}

void GamePadTransmitter::update() {
    if (millis() - _timer > _refreshInterval) {
        // first we write a 255 to mark the start
        // of the series
        Serial1.write(255);
        
        // write boolean values for pins 3 through 16
        for (int i = 3; i < 17; i++) {
            Serial1.write(digitalRead(i));
        }
        
        // write analog inputs
        for (int i = 0; i < 6; i++) {
            Serial1.write(this->encodeAnalog(i));
        }
        
        _timer = millis();
    }    
}

void GamePadTransmitter::setRefeshInterval(int refreshInterval) {
    _refreshInterval = refreshInterval;
}

int GamePadTransmitter::encodeAnalog(int pin) {
    return min(analogRead(pin) / 4, 254);    
}