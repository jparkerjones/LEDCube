
#include <LEDCube.h>

LEDCube cube(9);



int val1 = 0;
int val2 = 0;
int val3 = 0;


void setup() 
{
  //Serial port for debugging
  Serial.begin(9600);
}


void loop() {

  //Two test functions below to verify that arduino can control each individual .  First makes diagonal streaks that wrap around the cube.  The other turns on each LED in order.
  //Comment out the function that you dont want to use.  These are t

  //3 diagonal wrapping streaks
  if(cube.getVal(val1, val1, val1))
  {
    cube.setVal(val1, val1, val1, false);
  }
  else
  {
    cube.setVal(val1, val1, val1, true);
  }

  if(cube.getVal(val2, val2, val2 + 2))
  {
    cube.setVal(val2, val2, val2 + 2, false);
  }
  else
  {
    cube.setVal(val2, val2, val2 + 2, true);
  }

  if(cube.getVal(val3+4, val3+4, val3))
  {
    cube.setVal(val3+4, val3+4, val3, false);
  }
  else
  {
    cube.setVal(val3+4, val3+4, val3, true);
  }
   
  cube.updateCube();
  delay(100);
  val1++;
  val2++;
  val3++;
  //prevent overflow
   if(val1 == 8)
   {
    val1 = 0;
   }
   if(val2 == 6)
   {
    val2 = 0;
   }
   if(val3 == 4)
   {
    val3 = 0;
   }


}
