#ifndef LEDCube_h
#define LEDCube_h

#include "Arduino.h"
#include "SPI.h"
class LEDCube
{
    public:
        LEDCube(int loadPin);
        void updateCube();
        //This setter used to turn an LED ON or OFF
        void setVal(int x, int y, int z, bool value);
        //This setter used to turn an LED ON or OFF with PWM.  valid values for byte 0-10 inclusive.  0 is off, 10 is on, brightness scaled
        void setVal(int x, int y, int z, byte value);
        //returns true if LED is on in any PWM state, false if OFF
        bool getVal(int x, int y, int z);

    private:
        void initCube();
        void sendCommands(uint8_t commands[8][2]);
        int _loadPin;
        byte matrix[8][8][8] = {false};
        int pwm_cycle;
        //ISR(TIMER0_COMPA_vect);

};
#endif