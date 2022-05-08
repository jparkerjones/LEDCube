
#include <LEDCube.h>
LEDCube cube(9);
volatile bool value = false;



void setup() 
{
  setupTimer();


   cube.setVal(0, 0, 0, true);

  cube.setVal(0, 1, 1, (byte)3);

  cube.setVal(0, 2, 2, (byte)5);

  cube.setVal(0, 3, 3, (byte)7);

   cube.setVal(0, 4, 4, (byte)10);

   cube.updateCube();

}

void loop() 
{
  
 for(int i = 0; i < 5; i++)
 {
   cube.setVal(7, 0, i, (byte)(i+2));
   delay(100000);
   cube.setVal(7, 0, i, false);
   delay(100000);
  
 }

  
 

}



//interrupt routine.  Occurs every ~700 Hz
//Attempted to merge this into the library, ran into errors
ISR(TIMER0_COMPA_vect)
{
  //call the updateCube function to refresh the cube.  This function handles all PWM timers.
  cube.updateCube();
}


//Setup hardware timer for PWM.
//attempted to merge this into the library, ran into errors
//https://www.instructables.com/Arduino-Timer-Interrupts/
//Setup taken from this instructable.  Swapping to another timer should resolve the delay scaling issues.
void setupTimer()
{
  //enable interrupt function for PWM
  cli();

  //set timer0 interrupt at ~700 Hz
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
