#include <Wire.h>
#include <SenseMeBluetooth.h>
#include <SenseMe.h>
//Author: VS
//An AT Command terminal for Bluetooth. 

//Allow debug print statement in the drivers
#define DEBUG
#define BTDELAY 100

void BTsetCmdMode(int);

void setup() 
{
  Serial.begin(9600);
  SenseMeBluetooth.begin();
  delay(3000); 
  // Uncomment the line to carry out once
  //SenseMeBluetooth.setMaster();
  
  //Start AT Command Mode
  BTSERIAL.begin(9600);
  SenseMeBluetooth.setCmdMode(1);
}

int mode = 0;
 
void loop() 
{
  String content = "";
  String BTcontent = "";
  char character;
  
  //Use Serial to send commands to Bluetooth
  //'q' to quit ATcommand mode, 's' to start
  while(Serial.available()) 
  {
      character = Serial.read();
      content.concat(character);
  }
  if (content.length() >= 1) 
  {
    Serial.println(content);
    if (mode == 0)
      BTSERIAL.println(content);
  }
  if (content[0]=='q'||content[0]=='Q') {
      //quit AT mode
     // SenseMeBluetooth.setCmdMode(0);
     BTsetCmdMode(0);
      //delay(100);
      //SenseMeBluetooth.reset();
      //BTreset();
      mode = 1;
      Serial.println("quit AT command mode");
  }
  if (content[0]=='s'||content[0]=='S') {
      //quit AT mode
      BTsetCmdMode(1);
      //SenseMeBluetooth.setCmdMode(1);
      //delay(100);
      //SenseMeBluetooth.reset();
      //BTreset();
      mode = 0;
      Serial.println("start AT command mode");
  }



  while(BTSERIAL.available()) 
  {
      character = BTSERIAL.read();
      BTcontent.concat(character);
  }
  // check if BT receive anything
  if (BTcontent.length() >= 1) 
  {
    Serial.println(BTcontent);
  }
  
  delay(50); 
}

void BTreset()  //200, 2000. 500
{
  digitalWrite(BTRESETPIN, LOW);
  delay(50);
  digitalWrite(BTRESETPIN, HIGH);
  delay(50);
}

void BTsetCmdMode(int i_cmdMode)
{
  //PRINT("BtSetCmdMode ");    
  //PRINTLN(i_cmdMode);    
  digitalWrite(BTCMDPIN, (1 == i_cmdMode) ? HIGH : LOW);
  BTreset();

  //Serial1.begin((1 == i_cmdMode) ? 38400 : 57600);
  Serial1.begin((1 == i_cmdMode) ? 38400 : 38400);
}
