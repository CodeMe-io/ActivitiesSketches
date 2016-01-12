float LT = 0.5;
float HT = 1.5;
float TT = 0.3;
int orient = 0;

/*************************************************************
 getOrientation function
 *************************************************************/
int getOrientation() {
  float xyz[3];
  char message[] = "0";
  
  //Task 2.3: Read the Accelerometer sensor data
  
  int newOrient;
  
  if (abs(xyz[1]) > LT && abs(xyz[1]) < HT) {
    if (xyz[0] > TT) {
      newOrient = 1;
    }
    else if (xyz[0]< -TT) { 
      newOrient = 2;
    }
    
    else if (xyz[2] > TT) {
      newOrient = 3;
    }
    else if (xyz[2]< -TT) { 
      newOrient = 4;
    }
    else {
      newOrient = 5;
    }
  }
  else {
    newOrient = 0;
  }
  
  //Task 2.4: Print the orientation
  
    return newOrient;
}

