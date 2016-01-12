/********************************************
 nextstep function
 ********************************************/
void nextstep(){
  /* Task 3.1 - Prepare for the next Snake location */
  
    
  /* Task 3.2 - User direction to determine waht the next step is */
  
  /* Task 3.3 - Check if the snake has eaten the Fruit */
}

/********************************************
 makeFruit function
 ********************************************/
void makeFruit(){
  int x, y;
  x = random(0, 8);
  y = random(0, 8);
  while(isPartOfSnake(x, y)){
    x = random(0, 8);
    y = random(0, 8);
  }
  fruitX = x;
  fruitY = y;
}



