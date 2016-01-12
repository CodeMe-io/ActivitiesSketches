/********************************************
 inPlayField function
 ********************************************/
 
boolean inPlayField(int x, int y){
  return (x>=0) && (x<8) && (y>=0) && (y<8);
}

/********************************************
 isPartOfSnake function
 ********************************************/
boolean isPartOfSnake(int x, int y){
  for(int i=0; i<snakeLength-1; i++){
    if((x == snakeX[i]) && (y == snakeY[i])){
      return true;
    }
  }
  return false;
}
