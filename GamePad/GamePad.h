//
//  GamePad.h
//  
//
//  Created by Jason Pierce on 3/16/15.
//
//

#ifndef _GamePad_h
#define _GamePad_h

#include "Arduino.h"
#include "SoftwareSerial.h"

#define BUTTON_SELECT       0
#define BUTTON_START        1
#define BUTTON_UP           2
#define BUTTON_LEFT         3
#define BUTTON_DOWN         4
#define BUTTON_RIGHT        5
#define BUTTON_1            6
#define BUTTON_4            7
#define BUTTON_2            8
#define BUTTON_3            9
#define BUTTON_R1           10
#define BUTTON_R2           11
#define BUTTON_L1           12
#define BUTTON_L2           13
#define BUTTON_JOY_RIGHT    14
#define BUTTON_JOY_LEFT     15
#define RIGHT_AXIS_Y        16
#define RIGHT_AXIS_X        17
#define LEFT_AXIS_Y         18
#define LEFT_AXIS_X         19

// Represents the interface to the GamePad on the
// receiving Arduino.
class GamePad {
public:
    // Construct a GamePad receiver on the given
    // SoftwareSerial stream.
    GamePad(SoftwareSerial* softwareSerial);
    
    // Construct a GamePad receiver on the given
    // HardwareSerial stream.
    GamePad(HardwareSerial* hardwareSerial);
    
    // Must be called once during each iteration
    // of the loop function.
    void update();
    
    // The following methods return true
    // if the associated button is pressed,
    // false otherwise.
    boolean select();
    boolean start();
    boolean up();
    boolean down();
    boolean left();
    boolean right();
    boolean button1();
    boolean button2();
    boolean button3();
    boolean button4();
    boolean buttonR1();
    boolean buttonR2();
    boolean buttonL1();
    boolean buttonL2();
    boolean buttonJoyLeft();
    boolean buttonJoyRight();
    
    // The following methods return a value
    // int the range [0, 100] that represents
    // the position of the associated joystick
    // axis.
    int leftAxisX();
    int leftAxisY();
    int rightAxisX();
    int rightAxisY();
    
private:
    void init();
    int read();
    boolean available();
    boolean buttonValue(int index);
    int normalizeJoystick(int raw);
    
    boolean _readyToRead;
    int _offset;
    unsigned char _state[20];
    int _deadzone;
    
    SoftwareSerial* _softSerial;
    HardwareSerial* _hardSerial;
};

#endif
