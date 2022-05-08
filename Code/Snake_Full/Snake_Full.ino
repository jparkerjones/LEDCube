
#include <LEDCube.h>

LEDCube cube(9);





int snake[20][3] = {0};
int len = 3;

int joyValx;
int joyValy;


enum directions{pos_x, neg_x, pos_y, neg_y, pos_z, neg_z};
enum directions dir;

int fruit[3] = {0};

void setup() 
{
  setupTimer();
  
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
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
  cube.setVal(snake[1][0], snake[1][1], snake[1][2], (byte)(2));
  cube.setVal(snake[2][0], snake[2][1], snake[2][2], (byte)(2));

  dir = pos_z;

  //seed random function with unconnected pin
  randomSeed(analogRead(0));
  newFruitLocation();
  
  cube.updateCube();
}


void loop() 
{
  //turn off tail of snake
  cube.setVal(snake[len-1][0], snake[len-1][1], snake[len-1][2], false);


  //read joystick
  joyValx = analogRead(A2);
  joyValy = analogRead(A3);

  //from joystick readings, determine new direction.

  switch(dir)
  {
    //if currently moving in pos_x direction
    case pos_x:
      //moving to pos_z direction
      if(joyValx < 100)
      {
        dir = pos_z;
      }
      //moving to neg_z direction
      else if(joyValx > 700)
      {
        dir = neg_z;
      }
      //moving to pos_y direction
      else if(joyValy > 700)
      {
        dir = pos_y;
      }
      //moving to neg_y direction
      else if(joyValy < 100)
      {
        dir = neg_y;
      }
      //if none of these, direction stays pos_x
      break;

    //if currently moving in neg_x direction
    case neg_x:
      //moving to pos_z direction
      if(joyValx > 700)
      {
        dir = pos_z;
      }
      //moving to neg_z direction
      else if(joyValx < 100)
      {
        dir = neg_z;
      }
      //moving to pos_y direction
      else if(joyValy > 700)
      {
        dir = pos_y;
      }
      //moving to neg_y direction
      else if(joyValy < 100)
      {
        dir = neg_y;
      }
      //if none of these, direction stays neg_x
      break;

    //if currently moving in pos_y direction
    case pos_y:
      //moving to pos_z direction
      if(joyValx < 100)
      {
        dir = pos_z;
      }
      //moving to neg_z direction
      else if(joyValx > 700)
      {
        dir = neg_z;
      }
      //moving to neg_x direction
      else if(joyValy > 700)
      {
        dir = neg_x;
      }
      //moving to pos_x direction
      else if(joyValy < 100)
      {
        dir = pos_x;
      }
      //if none of these, direction stays pos_y
      break;

    //if currently moving in neg_y direction
    case neg_y:
      //moving to pos_z direction
      if(joyValx < 100)
      {
        dir = pos_z;
      }
      //moving to neg_z direction
      else if(joyValx > 700)
      {
        dir = neg_z;
      }
      //moving to neg_x direction
      else if(joyValy < 100)
      {
        dir = neg_x;
      }
      //moving to pos_x direction
      else if(joyValy > 700)
      {
        dir = pos_x;
      }
      //if none of these, direction stays neg_y
      break;

    //if currently moving in pos_z direction
    case pos_z:
      //moving to pos_z direction
      if(joyValx > 700)
      {
        dir = pos_x;
      }
      //moving to neg_z direction
      else if(joyValx < 100)
      {
        dir = neg_x;
      }
      //moving to pos_y direction
      else if(joyValy > 700)
      {
        dir = pos_y;
      }
      //moving to neg_y direction
      else if(joyValy < 100)
      {
        dir = neg_y;
      }
      //if none of these, direction stays pos_x
      break;

    //if currently moving in neg_z direction
    case neg_z:
      //moving to pos_x direction
      if(joyValx < 100)
      {
        dir = pos_x;
      }
      //moving to neg_x direction
      else if(joyValx > 700)
      {
        dir = neg_x;
      }
      //moving to pos_y direction
      else if(joyValy > 700)
      {
        dir = pos_y;
      }
      //moving to neg_y direction
      else if(joyValy < 100)
      {
        dir = neg_y;
      }
      //if none of these, direction stays pos_x
      break;  
  }
  
  
  //find new head coords:
  int headx = snake[0][0];
  int heady = snake[0][1];
  int headz = snake[0][2];

  //update head coords based on new direction
  switch(dir)
  {
    case pos_x:

      //increment x coord.  wrap with modulo
      headx = (headx+1)%8;
      break;

    case neg_x:

      //decrement x coord.  modulo doesnt handle wrapping of negative.
      headx--;
      if(headx < 0)
      {
        headx = headx + 8;
      }

      break;
      
    case pos_y:
      //increment y coord.  wrap with modulo
      heady = (heady+1)%8;
      break;

    case neg_y:

      //decrement y coord.  modulo doesnt handle wrapping of negative.
      heady--;
      if(heady < 0)
      {
        heady = heady + 8;
      }
      
      break;
      
    case pos_z:
      //increment z coord.  wrap with modulo
      headz = (headz+1)%8;
      break;

    case neg_z:

      //decrement x coord.  modulo doesnt handle wrapping of negative.
      headz--;
      if(headz < 0)
      {
        headz = headz + 8;
      }

      break;
  }

  //compare new head location to fruit location

  if(fruit[0] == headx && fruit[1] == heady && fruit[2] == headz)
  {
    //head and fruit overlap.  increase length and make a new fruit
    len++;
    newFruitLocation();
  } 

  //shift all coords
  for(int i = len - 1; i > 0; i--)
  {
    snake[i][0] = snake[i - 1][0];
    snake[i][1] = snake[i - 1][1];
    snake[i][2] = snake[i - 1][2];
  }
  //update new head
  snake[0][0] = headx;
  snake[0][1] = heady;
  snake[0][2] = headz;

  //turn on head of snake
  cube.setVal(headx, heady, headz, true);

  //lower pwm value of previous head LED
  cube.setVal(snake[1][0], snake[1][1], snake[1][2], (byte)(2));


   //compare new head location to rest of snake
   for(int i = 1; i < len; i++)
   {

      if(snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1] && snake[0][2] == snake[i][2])
      {
        //snake overlapped.  GAME OVER
        resetGame();
        break;
      }
    
   }
   
  //delay
  delay(50000);
 
}



void newFruitLocation()
{
  //generate new fruit location, make sure its not on the snake
  bool onSnake = true;
  while(onSnake)
  {
    onSnake = false;
     //generate random x, y, z location
    fruit[0] = random(8);
    fruit[1] = random(8);
    fruit[2] = random(8);

     for(int i = 0; i < len; i++)
      {
          //if the new coords match the snake, try again.
          if(snake[i][0] == fruit[0] && snake[i][1] == fruit[1] && snake[i][2] == fruit[2])
          {
            onSnake = true;
            break;
          }

      }
    
  }

  //new coords found.  Turn on LED
   cube.setVal(fruit[0], fruit[1], fruit[2], (byte)(5));
 
}


void resetGame()
{
  //reset old snake
  for(int i = 0; i < len; i++)
  {
    cube.setVal(snake[i][0],snake[i][1], snake[i][2],false);
  }
  len = 3;

  //reset old fruit
   cube.setVal(fruit[0], fruit[1], fruit[2], false);





  //init snake in starting position
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
  cube.setVal(snake[1][0], snake[1][1], snake[1][2], (byte)(5));
  cube.setVal(snake[2][0], snake[2][1], snake[2][2], (byte)(5));

  dir = pos_z;

  //seed random function with unconnected pin
  randomSeed(analogRead(0));
  newFruitLocation();
  
  cube.updateCube();

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
