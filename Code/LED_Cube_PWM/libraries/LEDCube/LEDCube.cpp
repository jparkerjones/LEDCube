#include "Arduino.h"
#include "LEDCube.h"
#include "SPI.h"

/*
 *  Constructor for the LEDCube
 */
LEDCube::LEDCube(int loadPin)
{
    _loadPin = loadPin;
    pinMode(_loadPin, OUTPUT);
    digitalWrite(_loadPin, LOW);
    SPI.begin();
    initCube();
}

/*
 * Function to initialize cube.  From datasheet, decode mode, intensity, and scan limit must be set before turning cube to normal operation mode.
 */
void LEDCube::initCube()
{
  uint8_t commands[8][2];
  //initialization values.  These are, in order:  decode mode off, intensity ~50%, scan limit 8 digits, normal operation mode)
  uint8_t initVals[4] = {0x00, 0x09, 0x0F, 0x01};

  //4 commands must be sent.  Addresses 0x09(decode mode), 0x0A(intensity), 0x0B(scan limit) and 0x0C(operating mode).
  for(uint8_t addr = 0x09; addr < 0x0D; addr++)
  {
    for(int i = 0; i < 8; i++)
    {
      commands[i][0] = addr;
      commands[i][1] = initVals[addr - 0x09];
    }
    sendCommands(commands);
    
  }

  //intialize cube LEDS to off
  updateCube();

}

/*
 * Update the LED cube to display the current values in the matrix array.
 */
void LEDCube::updateCube()
{
  //array of commands to send.  Command structure from MAX7219 datasheet is : XXXXAAAA DDDDDDDD    X- Dont Care A-Address D-Data.  Sent MSB to LSB
  uint8_t commands[8][2];
  //Each row has a different address, and must be updated in a separate command.
  for (uint8_t row = 0; row < 8; row++)
  {
    //Due to shift register operation, command for the last module is sent first.  
    for (int depth = 7; depth >= 0; depth--)
    {
      //create address bits for the command.  From the datasheet, the address of each row register(digit) is row + 1.  Place in first byte to send.
      commands[abs(depth - 7)][0] = (row + 1);
      
      uint8_t dataBits = 0b00000000;
      for (int column = 0; column < 8; column++)
      {
        //If LED is on, write a 1 in the correct location
        if(matrix[depth][row][column])
        {
          dataBits = dataBits + (0b00000001 << column);
        }
      }
      //save data in second byte to send.
      commands[abs(depth - 7)][1] = dataBits;
    }

    sendCommands(commands);
  
  }
}

/*
 * Function to send 8 commands to cube.
 */
void LEDCube::sendCommands(uint8_t commands[8][2])
{
  //SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  //pull load pin low.
  digitalWrite(_loadPin, LOW);
  //send 8 spi commands.  Send bytes 1 at a time.  No 
  for(int i = 0; i < 8; i++)
  {
    SPI.transfer(commands[i][0]);
    SPI.transfer(commands[i][1]);
  }
  //pull load pin high.
  digitalWrite(_loadPin, HIGH);
  //SPI.endTransaction();

}

/*
 *  Setter for values in the LED Matrix. Call the update() function to update the actual LEDs being displayed
 */
void LEDCube::setVal(int x, int y, int z, bool value)
{
    matrix[x][y][z] = value;
}

/*
 *  Getter for values in the LED Matrix. Returns value in matrix
 */
bool LEDCube::getVal(int x, int y, int z)
{
    return matrix[x][y][z];
}