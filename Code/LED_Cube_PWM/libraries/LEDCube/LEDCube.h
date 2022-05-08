#ifndef LEDCube_h
#define LEDCube_h

#include "Arduino.h"
#include "SPI.h"
class LEDCube
{
    public:
        LEDCube(int loadPin);
        void updateCube();
        void setVal(int x, int y, int z, bool value);
        bool getVal(int x, int y, int z);

    private:
        void initCube();
        void sendCommands(uint8_t commands[8][2]);
        int _loadPin;
        bool matrix[8][8][8] = {false};

};
#endif