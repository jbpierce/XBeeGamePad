//
//  GamePad.cpp
//  
//
//  Created by Jason Pierce on 3/16/15.
//
//

#include "Arduino.h"
#include "SoftwareSerial.h"

#include "GamePad.h"

/*** GamePad Implementation ***/

GamePad::GamePad(SoftwareSerial* softwareSerial) {
    _softSerial = softwareSerial;
    this->init();
}

GamePad::GamePad(HardwareSerial* hardwareSerial) {
    _hardSerial = hardwareSerial;
    this->init();
}

void GamePad::init() {
    _deadzone = 6;
    _readyToRead = false;
    for (int i = BUTTON_SELECT; i <= BUTTON_L2; i++) {
        _state[i] = 1; // button up
    }
    for (int i = BUTTON_JOY_RIGHT; i <= LEFT_AXIS_X; i++) {
        _state[i] = 127; // centered
    }
}

void GamePad::update() {    
    if (this->available()) {         
        if (!_readyToRead) {
            unsigned char b = this->read();
            if (b == 255) {
                _readyToRead = true;
                _offset = 0;
            }
        }
        
        if (_readyToRead && this->available()) {
            unsigned char b = this->read();
            if (b == 255) {
                _offset = 0;
                _readyToRead = false;  
            } else {
                _state[_offset] = b;
                _offset++;
                
                if (_offset > LEFT_AXIS_X) {
                    _offset = 0;
                    _readyToRead = false;  
                }
            }
        }
    }
}

int GamePad::read() {
    if (_hardSerial) {
        return _hardSerial->read();
    } else if (_softSerial) {
        return _softSerial->read();
    }
    return 0;
}

boolean GamePad::available() {
    if (_hardSerial) {
        return _hardSerial->available();
    } else if (_softSerial) {
        return _softSerial->available();
    }
    return false;
}

boolean GamePad::buttonValue(int index) {
    return !(_state[index] > 0);
}

boolean GamePad::select() {
    return this->buttonValue(BUTTON_SELECT);
}

boolean GamePad::start() {
    return this->buttonValue(BUTTON_START);
}

boolean GamePad::up() {
    return this->buttonValue(BUTTON_UP);
}

boolean GamePad::down() {
    return this->buttonValue(BUTTON_DOWN);
}

boolean GamePad::left() {
    return this->buttonValue(BUTTON_LEFT);
}

boolean GamePad::right() {
    return this->buttonValue(BUTTON_RIGHT);
}

boolean GamePad::button1() {
    return this->buttonValue(BUTTON_1);
}

boolean GamePad::button2() {
    return this->buttonValue(BUTTON_2);
}

boolean GamePad::button3() {
    return this->buttonValue(BUTTON_3);
}

boolean GamePad::button4() {
    return this->buttonValue(BUTTON_4);
}

boolean GamePad::buttonR1() {
    return this->buttonValue(BUTTON_R1);
}

boolean GamePad::buttonR2() {
    return this->buttonValue(BUTTON_R2);
}

boolean GamePad::buttonL1() {
    return this->buttonValue(BUTTON_L1);
}

boolean GamePad::buttonL2() {
    return this->buttonValue(BUTTON_L2);
}

boolean GamePad::buttonJoyLeft() {
    return this->buttonValue(BUTTON_JOY_LEFT);
}

boolean GamePad::buttonJoyRight() {
    return this->buttonValue(BUTTON_JOY_RIGHT);
}

int GamePad::normalizeJoystick(int raw) {
    if (raw < 127) {
        if (raw > 127 - _deadzone) {
            return 50;
        }
        return raw * 50 / (127 - _deadzone);
    }
    
    if (raw < 127 + _deadzone) {
        return 50;
    }
    
    return ((raw - 127 - _deadzone) * 50 / (254 - 127 - _deadzone)) + 50;
}

int GamePad::leftAxisX() {
    return 100 - normalizeJoystick(_state[LEFT_AXIS_X]);
}

int GamePad::leftAxisY() {
    return normalizeJoystick(_state[LEFT_AXIS_Y]);
}

int GamePad::rightAxisX() {
    return 100 - normalizeJoystick(_state[RIGHT_AXIS_X]);
}

int GamePad::rightAxisY() {
    return normalizeJoystick(_state[RIGHT_AXIS_Y]);
}

