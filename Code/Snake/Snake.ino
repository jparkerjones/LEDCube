
#include <LEDCube.h>

LEDCube cube(9);





int snake[15][3] = {0};
int len = 3;
int dir = 0;

int joyVal;

void setup() 
{
  pinMode(A2, INPUT);
  //Serial port for debugging
  Serial.begin(9600);
  //init snake 
  snake[0][0] = 0;
  snake[0][1] = 0;
  snake[0][2] = 3;
  
  snake[1][0] = 0;
  snake[1][1] = 0;
  snake[1][2] = 2;
  
  snake[2][0] = 0;
  snake[2][1] = 0;
  snake[2][2] = 1;

  cube.setVal(snake[0][0], snake[0][1], snake[0][2], true);
  cube.setVal(snake[1][0], snake[1][1], snake[1][2], true);
  cube.setVal(snake[2][0], snake[2][1], snake[2][2], true);
  cube.updateCube();
}


void loop() 
{
  //turn off tail of snake
  cube.setVal(snake[len-1][0], snake[len-1][1], snake[len-1][2], false);
  Serial.println("cleared tail");


  //read joystick
  joyVal = analogRead(A2);
  Serial.println(joyVal);
  if(joyVal < 150)
  {
    dir = (dir - 1)%4;
  }
  else if(joyVal > 500)
  {
    dir = (dir + 1)%4;
  }
  
  
  //find new head coords:
  int headx = 0;
  int heady = 0;
  int headz = 0;

  

  if(dir == 0)
  {
     headx = snake[0][0];
     heady = snake[0][1];
     headz = (snake[0][2] + 1)%8;
     Serial.println("Moving head + z");
     Serial.println(headz);
  }
  else if(dir == 1)
  {
     headx = snake[0][0];
     heady = (snake[0][1] + 1)%8;
     headz = snake[0][2];
  }
  else if(dir == 2)
  {
     headx = snake[0][0];
     heady = snake[0][1];
     headz = (snake[0][2] - 1)%8;
  }
  else
  {
     headx = snake[0][0];
     heady = (snake[0][1] - 1)%8;
     headz = snake[0][2];
  }
  
  //turn on head of snake
  cube.setVal(headx, heady, headz, true);

  //shift all coords
  for(int i = len - 1; i > 0; i--)
  {
    snake[i][0] = snake[i - 1][0];
    snake[i][1] = snake[i - 1][1];
    snake[i][2] = snake[i - 1][2];
  }
  snake[0][0] = headx;
  snake[0][1] = heady;
  snake[0][2] = headz;

  cube.updateCube();
   

  delay(1000);
 
}
