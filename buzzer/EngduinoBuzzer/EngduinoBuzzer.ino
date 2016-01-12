/*
  Engduino buzzer
 Receive a bluetooth message and buzz the corresponding buzzer
*/

#define buzzer1 A2
#define buzzer2 A3
#define buzzer3 5
#define buzzer4 6

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // Initialise the button pins
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer3, OUTPUT);
  pinMode(buzzer4, OUTPUT);
  pinMode(13, OUTPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  char recChar;
  if (Serial1.available())
  {
    // Forward everything to the PC terminal.
    recChar = Serial1.read();
    Serial.print(recChar);
  }
  
  //turn it all off first  
  switch (recChar) {
     case '1':
         digitalWrite(buzzer1, HIGH);
         break;
     case '2':
         digitalWrite(buzzer2, HIGH);
         break;
     case '3':
         digitalWrite(buzzer3, HIGH);
         break;
     case '4':
         digitalWrite(buzzer4, HIGH);
         break;
     case '0':
     case '5':
         digitalWrite(buzzer1, LOW);
         digitalWrite(buzzer2, LOW);
         digitalWrite(buzzer3, LOW);
         digitalWrite(buzzer4, LOW);
         break;
  }
}


//a test routine
void loopBuzzer() {

  digitalWrite(13,HIGH);

  digitalWrite(buzzer1, HIGH);
  delay(1000);
  digitalWrite(buzzer1, LOW);
  
  digitalWrite(buzzer2, HIGH);
  delay(1000);
  digitalWrite(buzzer2, LOW);

  digitalWrite(13, LOW);
  
  digitalWrite(buzzer3, HIGH);
  delay(1000);
  digitalWrite(buzzer3, LOW);
  
  digitalWrite(buzzer4, HIGH);
  delay(1000);
  digitalWrite(buzzer4, LOW);

}

