/********************************************
 draw function
 update the LED matrix
 ********************************************/
void draw(){
  SenseMeLEDMatrix.clear();
  drawSnake();
  drawFruit();
  SenseMeLEDMatrix.writeDisplay();
}

/********************************************
 drawFruit function
 ********************************************/
void drawFruit(){
  if(inPlayField(fruitX, fruitY)){
    unsigned long currenttime = millis();
    if(currenttime - fruitPrevTime >= fruitBlinkTime){
      fruitLed = (fruitLed == LED_ON) ? LED_OFF : LED_GREEN;
      fruitPrevTime = currenttime;
    }
    SenseMeLEDMatrix.drawPixel(fruitX, fruitY, fruitLed);
  }
}

/********************************************
 drawSnake function
 ********************************************/
void drawSnake(){
  for(int i=0; i<snakeLength; i++){
    SenseMeLEDMatrix.drawPixel(snakeX[i], snakeY[i], LED_YELLOW);
  }
}
