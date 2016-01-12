// Snake game on SenseMe
// 2015-9-05 Venus Shum

#include <Wire.h>
#include <SenseMeMatrixTwo.h>
// for version 1 cubes 
// #include <SenseMeMatrixOne.h> 
/* Task 2.1: Include the Accelerometer library */

/********************************************
 Variables declaration
 ********************************************/
const int MAX_SNAKE_LENGTH = 10;    // Snake variables

const int TOP    = 1;                              // Define direction variables
const int RIGHT  = 4;
const int BOTTOM = 2;
const int LEFT   = 3;

int direction = TOP;                               // initial direction of movement
int snakeX[MAX_SNAKE_LENGTH];                      // X-coordinates of snake
int snakeY[MAX_SNAKE_LENGTH];                      // Y-coordinates of snake
int snakeLength = 1;                               // nr of parts of snake
unsigned long prevTime = 0;                        // initial varialbe for gamedelay (ms)
unsigned long delayTime = 100;                     // Game step in ms - this determine how fast the snake goes

int fruitX, fruitY;                                // Fruit location
unsigned long fruitPrevTime = 0;
unsigned long fruitBlinkTime = 1000/250;
int fruitLed = LED_ON;
int tilt = 0;    //accelerometer tilt
int DEBUG = 0;  //parameter to print out extra messages when in debugging mode. 0-disable, 1-enable

static const uint8_t PROGMEM    // Icon definitions
  cross[] =
  { B10000001,
    B01000010,
    B00100100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B10000001 };
   
/********************************************
 setup function
 ********************************************/
void setup(){
  Serial.begin(9600);
  Serial.println("Snake is started");
  randomSeed(analogRead(0));  // Randomize the seed so the random number sequence won't be the same every time. 
  
  // initialise led matrix
  SenseMeLEDMatrix.begin(); //initialise matrix
  SenseMeLEDMatrix.clear();
  SenseMeLEDMatrix.writeDisplay();

  // Snake initial position
  snakeX[0] = 4;
  snakeY[0] = 7;
  for(int i=1; i<MAX_SNAKE_LENGTH; i++){
    snakeX[i] = snakeY[i] = -1;
  }
  
  // Fruit initial position
  makeFruit();
  
  /* Task 2.2: Initialise the accelerometer sensor */
}

/********************************************
 loop function
 ********************************************/
void loop(){
  
   /* Task 2.5 - call getOirnetation */
	
   /* Task 3.4 - delete code from Task 2.5 - control speed of snake */
	
   /* Task 1 program logic - replace this line with your code */
}






