#include <Wire.h>
#include <SenseMeLEDMatrix.h>
#include <SenseMeAccelerometer.h>
#include <SenseMeNeopixel.h>
#include <SenseMeBluetooth.h>

static const uint8_t PROGMEM
  leftArrow[] =
  { B00000000,
    B00000000,
    B01000000,
    B11110000,
    B11110000,
    B01000000,
    B00000000,
    B00000000 },
  rightArrow[] =
  { B00000000,
    B00000000,
    B00000010,
    B00001111,
    B00001111,
    B00000010,
    B00000000,
    B00000000 },
  upArrow[] =
  { B00011000,
    B00111100,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
  downArrow[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00111100,
    B00011000 },
  centreSquare[] =
  { B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000 },
  cross[] =
  { B10000001,
    B01000010,
    B00100100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B10000001 },
  robot[] =
  { B00011000,
    B00111100,
    B00111100,
    B01011010,
    B10111101,
    B00100100,
    B00100100,
    B00100100 };  
    
    
#define DEBUG false

float LT = 0.5;
float HT = 1.5;
float TT = 0.3;
int orient = 0;

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  SenseMeLEDMatrix.begin(); //initialise matrix
  SenseMeAccelerometer.begin(); //initialise acceleromete
  
  SenseMeLEDMatrix.clear();
  SenseMeLEDMatrix.writeDisplay();
  
  Serial.begin(9600);
  SenseMeBluetooth.begin();
  //Do these the first time only
  //SenseMeBluetooth.reset();
  SenseMeBluetooth.setMaster();
  SenseMeBluetooth.setPairingMode(SPECIFIC);
  //SenseMeBluetooth.getDeviceList();  
  
  //testing scripts
  //SenseMeBluetooth.sendCommand("AT+INIT");
  //SenseMeBluetooth.sendCommand("AT+role=1");
  //SenseMeBluetooth.sendCommand("AT+INQC");
  //SenseMeBluetooth.sendCommand("AT+INQM");
  delay(1000);
  Serial1.begin(38400);
  //delay(1000);
  //SenseMeBluetooth.sendCommand("AT+INQ");
  

  //delay(10000);
}

int tilt=0;

void loop() {
  //print out all the Bluetooth messages to serial for debugging
   if (Serial1.available())
  {
    // Forward everything to the PC terminal.
    char recChar = Serial1.read();
    Serial.print(recChar);

  }
  
  // Get the orientation of the accelerometer and display an arrow. 
  int newOrient = getOrientation();
  if (DEBUG)   Serial.println(newOrient);
  if (newOrient != orient) {
    drawBitmap(newOrient);
  }
  orient = newOrient;
  delay(200);
}


/*************************/
/* Get orientation of the cube and display the arrow */
/*************************/
int getOrientation() {
  float xyz[3];
  char message[] = "0";
  SenseMeAccelerometer.xyz(xyz);
  int newOrient;
  
  //if the LED panel is on the top
  /*
  if (abs(xyz[0]) > LT && abs(xyz[0]) < HT) {
    if (xyz[0] < 1)
      orient = 1;
    if (xyz[0]>1) 
      orient = 2;
  }
  */ 
  
  if (abs(xyz[1]) > LT && abs(xyz[1]) < HT) {
    if (xyz[0] > TT) {
      newOrient = 1;
      message[0] = '1';
    }
    else if (xyz[0]< -TT) { 
      newOrient = 2;
      message[0] = '2';
    }
    
    else if (xyz[2] > TT) {
      newOrient = 3;
      message[0] = '3';
    }
    else if (xyz[2]< -TT) { 
      newOrient = 4;
      message[0] = '4';
    }
    else {
      newOrient = 5;
      message[0] = '5';
    }
  }
  else {
    newOrient = 0;
    message[0] = '0';
  }
  Serial1.print(message);
  /*
  else if (xyz[2] > LT && xyz[2] < HT) {
    if (xyz[0] < 1)
      orient = 5;
    if (xyz[0]>1) 
      orient = 6;
  }
  */
  
  
  if (DEBUG) {
      Serial.print("Accelerometer x=");
      Serial.print(xyz[0]);
      Serial.print(", y=");
      Serial.print(xyz[1]);
      Serial.print(", z=");
      Serial.print(xyz[2]);
      Serial.print(", O=");
      Serial.println(orient);
    }
    return newOrient;
}

void drawBitmap(int newOrient){
  Serial.println(newOrient);
     SenseMeLEDMatrix.clear();
     switch(newOrient) {
      case 0:
         SenseMeLEDMatrix.drawBitmap(0, 0, cross, 8, 8, LED_ON);
         break; 
      case 1:
         SenseMeLEDMatrix.drawBitmap(0, 0, upArrow, 8, 8, LED_ON);
         break; 
      case 2:
         SenseMeLEDMatrix.drawBitmap(0, 0, downArrow, 8, 8, LED_ON);
         break; 
      case 3:
         SenseMeLEDMatrix.drawBitmap(0, 0, leftArrow, 8, 8, LED_ON);
         break; 
      case 4:
         SenseMeLEDMatrix.drawBitmap(0, 0, rightArrow, 8, 8, LED_ON);
         break;  
      case 5:
         SenseMeLEDMatrix.drawBitmap(0, 0, centreSquare, 8, 8, LED_ON);
         break;
     }
    SenseMeLEDMatrix.writeDisplay();
  
}
