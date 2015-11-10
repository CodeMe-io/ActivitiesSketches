#include <Wire.h>
#include <SenseMeLEDMatrix.h>
//#include <SenseMeMatrixTwo.h>
#include <SenseMeBluetooth.h>
#include <SenseMeAccelerometer.h>

String content = "";
char character;
/* choose one of these instruments */
#define PIANO 0
#define XYLOPHONE 1
#define DRUM 2

#define INSTRUMENT  XYLOPHONE

#define STOP 'X'
#define SEND 'T'

#if (INSTRUMENT == XYLOPHONE)
  #define N '1'
  #define NE '2'
  #define E '3'
  #define SE '4'
  #define S '5'
  #define SW '6'
  #define W '7'
  #define NW '8'
#elif (INSTRUMENT == PIANO)
  #define N 'c'
  #define NE 'd'
  #define E 'e'
  #define SE 'f'
  #define S 'g'
  #define SW 'a'
  #define W 'b'
  #define NW 'C'
#elif (INSTRUMENT == DRUM)
  #define N 'w'
  #define NE STOP
  #define E 'x'
  #define SE STOP
  #define S 'y'
  #define SW STOP
  #define W 'z'
  #define NW STOP
#endif 



float LT = 0.5;
float HT = 1.5;
float TT1 = 0.4;    //The pure direction has a higher threshold
float TT2 = 0.2;    //The mixed direction has a lower threshold

char orient = '0';

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
  northEast[] =
  { B00001111,
    B00000011,
    B00000101,
    B00001001,
    B00010000,
    B00000000,
    B00000000,
    B00000000},
  southWest[] = 
  { B00000000,
    B00000000,
    B00000000,
    B00001000,
    B10010000,
    B10100000,
    B11000000,
    B11110000}, 
  southEast[] =
  { B00000000,
    B00000000,
    B00000000,
    B00010000,
    B00001001,
    B00000101,
    B00000011,
    B00001111},
  northWest[] = 
  { B11110000,
    B11000000,
    B10100000,
    B10010000,
    B00001000,
    B00000000,
    B00000000,
    B00000000},
  cross[] =
  { B10000001,
    B01000010,
    B00100100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B10000001 },
  blue_bmp[] =
  { B00011000,
    B10010100,
    B01010010,
    B00110100,
    B00111000,
    B01010100,
    B10010010,
    B00011100 };

    
void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   Serial1.begin(9600); // initialization
   SenseMeLEDMatrix.begin();  // pass in the address
   SenseMeLEDMatrix.clear();
   SenseMeLEDMatrix.writeDisplay();
   SenseMeLEDMatrix.drawBitmap(0, 0, blue_bmp, 8, 8, LED_ON);
   SenseMeLEDMatrix.writeDisplay();
   SenseMeBluetooth.begin();
   SenseMeAccelerometer.begin();
}



long lastSent = 0;
void loop() {
  // put your main code here, to run repeatedly:
  float xyz[3];
  char message[] = "0";
  int tiltX = 0;
  int tiltY = 0;

  
  SenseMeAccelerometer.xyz(xyz);
  
  // detect X tilt
  if (xyz[0] > TT2) tiltX = 1;
  if (xyz[0] < -TT2) tiltX = -1;
  
  // detect Y tilt
  if (xyz[2] > TT2) tiltY = 1;
  if (xyz[2] < -TT2) tiltY = -1;
  
  
  
  message[0] = '0';
  
  if (abs(xyz[1]) > LT && abs(xyz[1]) < HT) {//we want LED matrix face up
  
      /* Y = 1 => W
         Y = -1 => E
         X = 1 => N
         X = -1 => S
         */
      message[0] = STOP;
      if (tiltY==1) {    // Y is West
        if (tiltX==1) message[0] = NW;
        else if (tiltX==-1) message[0] = SW;
        else if (tiltX==0 && (xyz[2] > TT1)) message[0] = W;
      }
      else if (tiltY == 0) {
        if (tiltX==0) message[0] = STOP;
        else if (tiltX==1 && (xyz[0] > TT1)) message[0] = N;
        else if (tiltX==-1 && (xyz[0] < -TT1)) message[0] = S;
      }
      else if (tiltY == -1) {
        if (tiltX==1) message[0] = NE;
        else if (tiltX==-1) message[0] = SE;
        else if (tiltX==0 && (xyz[2] < -TT1)) message[0] = E;
      }
  
  }
  else message[0] = SEND;

  
  if (message[0] != orient) {
    drawBitmap(message[0]);
    if (message[0] != 0 && message[0]!=STOP) {
      Serial1.println(message[0]);  
    }
    Serial.println(message[0]);
  }
  orient = message[0];
  delay(100);
  BluetoothListen();
}

// Bluetooth receiver, display any received messages

void BluetoothListen() {
  //Serial.println("Bluetooth");
  //Serial1.println("HC-05");
  content = "";
  
  while(Serial1.available()) 
  {
      character = Serial1.read();
      content.concat(character);
      Serial.println(character);
      //content[sizeof(content)]=character;
      delay(50);
  }
  
  if (content.length() >0) 
  {
    
    Serial.println(content.length());
    Serial.println(content);
    //int led = content.toInt();  // use atoi to convert the string to an int
    
          SenseMeLEDMatrix.setTextSize(1);
          SenseMeLEDMatrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
          SenseMeLEDMatrix.setTextColor(LED_ON);

          int len=content.length();
          for (int8_t x=0; x>=-((len+1)*6); x--) {
            SenseMeLEDMatrix.clear();
            SenseMeLEDMatrix.setCursor(x,0);
            SenseMeLEDMatrix.print(content);
            SenseMeLEDMatrix.writeDisplay();
            delay(100);
          }
          
          SenseMeLEDMatrix.clear();
          SenseMeLEDMatrix.writeDisplay();
          

    content = "";
    //delay(10); 
  }
  
  
}

#define LED_COLOUR LED_GREEN
void drawBitmap(char newOrient){
  Serial.println(newOrient);
     SenseMeLEDMatrix.clear();
     switch(newOrient) {
      case '0':
         SenseMeLEDMatrix.drawBitmap(0, 0, cross, 8, 8, LED_COLOUR);
         break; 
      case N:
         SenseMeLEDMatrix.drawBitmap(0, 0, upArrow, 8, 8, LED_COLOUR);
         break;  
      case S:
         SenseMeLEDMatrix.drawBitmap(0, 0, downArrow, 8, 8, LED_COLOUR);
         break; 
      case W:
         SenseMeLEDMatrix.drawBitmap(0, 0, leftArrow, 8, 8, LED_COLOUR);
         break; 
      case E:
         SenseMeLEDMatrix.drawBitmap(0, 0, rightArrow, 8, 8, LED_COLOUR);
         break;  
#if (INSTRUMENT!=DRUM)
      case NE:
         SenseMeLEDMatrix.drawBitmap(0, 0, northEast, 8, 8, LED_COLOUR);
         break;
      case SE:
         SenseMeLEDMatrix.drawBitmap(0, 0, southEast, 8, 8, LED_COLOUR);
         break;
      case NW:
         SenseMeLEDMatrix.drawBitmap(0, 0, northWest, 8, 8, LED_COLOUR);
         break;
      case SW:
         SenseMeLEDMatrix.drawBitmap(0, 0, southWest, 8, 8, LED_COLOUR);
         break;
#endif
      case SEND:
        SenseMeLEDMatrix.drawBitmap(0, 0, cross, 8, 8, LED_COLOUR);
      case STOP:
         SenseMeLEDMatrix.drawBitmap(0, 0, centreSquare, 8, 8, LED_COLOUR);
         break;
     }

    SenseMeLEDMatrix.writeDisplay();
  
}
