
#include <LEDCube.h>
LEDCube cube(9);

byte pwm[8][8][8] = {0};
boolean onOff[8][8][8] = {false};

volatile int count = 0;


void timerTest()
{
  if(count < 6)
  {
      digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }

  count = (count+1)%10;
  
}

void setup() 
{

  pwm[0][0][0] = 0;
  onOff[0][0][0] = true;
  pwm[0][0][1] = 1;
  onOff[0][0][1] = true;
  pwm[0][0][2] = 2;
  onOff[0][0][2] = true;
  pwm[0][0][3] = 3;
  onOff[0][0][3] = true;
  pwm[0][0][4] = 4;
  onOff[0][0][4] = true;
  pwm[0][0][5] = 5;
  onOff[0][0][5] = true;
  pwm[0][0][6] = 6;
  onOff[0][0][6] = true;
  pwm[0][0][7] = 7;
  onOff[0][0][7] = true;
  pwm[0][1][0] = 8;
  onOff[0][1][0] = true;
  pwm[0][1][1] = 9;
  onOff[0][1][1] = true;

  cli();

  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0

   // set compare match register for 2khz increments * CHANGED FOR ~700 Hz, 1024 prescaler
  OCR0A = 24;// = (16*10^6) / (700*1024) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
 // Set CS10 and CS12 bits for 1024 prescaler
  TCCR0B |= (1 << CS12) | (1 << CS10);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  sei();//allow interrupts
  
}

ISR(TIMER0_COMPA_vect)
{
  //loop through all values in the cube and check if they should be turned on for this cycle
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
      for(int z = 0; z < 8; z++)
      {
        //if count < pwm value and LED should be on, turn it on
        if(count < pwm[x][y][z] && onOff[x][y][z])
        {
          cube.setVal(x, y, z, true);
        }
        else
        {
          cube.setVal(x, y, z, false);
        }
        
      }
    }
  }
  cube.updateCube();
  //increment count
  count = (count+1)%10;
}


void loop() {

  


}
