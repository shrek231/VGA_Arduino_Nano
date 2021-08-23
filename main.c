int AllCycles = 0;
int maxX = 640;
int maxY = 350;
int Y = 0;
int X_ADDR[12]; //replace with 14 later
int X_BUFFER_BIN[8];
int X_BUFFER[640];
void setup(){
  Serial.begin(9600);
  pinMode(A0, INPUT);//data input 0
  pinMode(A1, INPUT);//data input 1
  pinMode(A2, INPUT);//data input 2
  pinMode(A3, INPUT);//data input 3
  pinMode(A4, INPUT);//data input 4
  pinMode(A5, INPUT);//data input 5
  pinMode(A6, INPUT);//data input 6
  pinMode(A7, INPUT);//data input 7

  pinMode(2, OUTPUT);//address line 0
  pinMode(3, OUTPUT);//address line 1
  pinMode(4, OUTPUT);//address line 2
  pinMode(5, OUTPUT);//address line 3
  pinMode(6, OUTPUT);//address line 4
  pinMode(7, OUTPUT);//address line 5
  pinMode(8, OUTPUT);//address line 6
  pinMode(9, OUTPUT);//address line 7
  pinMode(10, OUTPUT);//address line 8
  pinMode(11, OUTPUT);//address line 9
  pinMode(12, OUTPUT);//address line 10
  pinMode(13, OUTPUT);//address line 11
  //address line 12
  //address line 13
  //address line 14
}
void loop(){
  int count=0;
  //horizontal
  for(int x_ = 0;x_<=maxX;x_++){
    //display x by setting a pin to 1 if X_BUFFER[x_] is 1
    AllCycles++;
  }for(int FP = 0;FP<=16;FP++){
    //display nothing
  }for(int SyncP = 0;SyncP<=96;SyncP++){
    //set Hsync low during this time
  }for(int BP = 0;BP<=48;BP++){
    //display nothing
    if (count == 0){
      int count2 = 0;
      for(int i = 1; i<=640; i=count2+1){ //this loop will most likely not work becuse it loops 640 times and i only have 48 
        //set X buffer addr
        int_to_bin_array(AllCycles + i, 11, X_ADDR);//replace with 14 later
        for (int i = 2,x = 0; i <= 11; i++,x++){//replace with 14 later
          if(X_ADDR[x] == 1){
            digitalWrite(i, HIGH);//high if X_ADDR[0-12] is 1
          } else {
            digitalWrite(i, LOW);//high if X_ADDR[0-12] is 0
          }
        }
        //Set X Buffer
        X_BUFFER_BIN[0] = digitalRead(A0);
        X_BUFFER_BIN[1] = digitalRead(A1);
        X_BUFFER_BIN[2] = digitalRead(A2);
        X_BUFFER_BIN[3] = digitalRead(A3);
        X_BUFFER_BIN[4] = digitalRead(A4);
        X_BUFFER_BIN[5] = digitalRead(A5);
        X_BUFFER_BIN[6] = digitalRead(A6);
        X_BUFFER_BIN[7] = digitalRead(A7);
        //set x buffer binary to int then add to the x buffer
        /*
        Serial.print(X_BUFFER_BIN[0]);
        Serial.print(X_BUFFER_BIN[1]);
        Serial.print(X_BUFFER_BIN[2]);
        Serial.print(X_BUFFER_BIN[3]);
        Serial.print(X_BUFFER_BIN[4]);
        Serial.print(X_BUFFER_BIN[5]);
        Serial.print(X_BUFFER_BIN[6]);
        Serial.println(X_BUFFER_BIN[7]);*/
        X_BUFFER[count2] = X_BUFFER_BIN[0];
        X_BUFFER[count2 + 1] = X_BUFFER_BIN[1];
        X_BUFFER[count2 + 2] = X_BUFFER_BIN[2];
        X_BUFFER[count2 + 3] = X_BUFFER_BIN[3];
        X_BUFFER[count2 + 4] = X_BUFFER_BIN[4];
        X_BUFFER[count2 + 5] = X_BUFFER_BIN[5];
        X_BUFFER[count2 + 6] = X_BUFFER_BIN[6];
        X_BUFFER[count2 + 7] = X_BUFFER_BIN[7];
        count2+=8;
      }
    } else {
      //extra space
    }
  count++;
  }
  //vertical
  Y++;
  if(Y <= 350){
    //display nothing
    
    AllCycles++;
  }if(Y = 350+1 && Y <= 350+37){
    //display nothing, FP
  }if(Y >= 350+37+1 && Y <= 350+37+2){
    //set Vsync low during this time
  }if(Y = 350+37+2+1 && Y <= 350+37+2+60){
    //display nothing, BP
  }if(Y >= 449){
    //End of frame
    Y = 0;
  }
}
void int_to_bin_array(unsigned int in, int count, int* out){
    unsigned int mask = 1U << (count-1);
    int i;
    for (i = 0; i < count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
}
