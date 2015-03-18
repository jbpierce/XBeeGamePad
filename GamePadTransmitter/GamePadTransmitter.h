//
//  GamePadTransmitter.h
//  
//
//  Created by Jason Pierce on 3/17/15.
//
//

#ifndef ____GamePadTransmitter__
#define ____GamePadTransmitter__

#include "Arduino.h"

class GamePadTransmitter {
public:
    // Constructs the GamePadTransmitter.
    GamePadTransmitter();
    
    // Should be called during the setup function.
    // Initializes I/O with the given baud rate.
    void begin(int baudRate);
    
    // Must be called once during each iteration
    // of the loop function.
    void update();
    
    // Sets the refresh interval in milliseconds.
    // This determines how often the game pad is
    // polled and data sent to the receiver.
    void setRefeshInterval(int refreshInterval);
    
private:
    int encodeAnalog(int pin);
    int _refreshInterval;
    unsigned long _timer = 0;
};

#endif /* defined(____GamePadTransmitter__) */
