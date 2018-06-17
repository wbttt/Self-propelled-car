#include <Boards.h>
#include <Firmata.h>

#include <Servo.h> 
Servo leftright; 
Servo updown;
int i=0;
int posX=90;
int posY=55;
int a=0;
int on=0;
int c=0;
float F_distance=0;
float R_distance=0;
float L_distance=0;

int pinLF=14;
int pinLB=15;
int pinRF=16;
int pinRB=17;

int MotorRPWM=3;
int MotorLPWM=5;

int inputPin1 = 9;  // 定義超音波信號接收腳位
int outputPin2 =8;  // 定義超音波信號發射腳位
int inputPin3 = 6;  // 定義超音波信號接收腳位
int outputPin4 =4;  // 定義超音波信號發射腳位
int inputPin5 = 13;  // 定義超音波信號接收腳位
int outputPin6 =12;  // 定義超音波信號發射腳位



int Fspeedd=0;
int Rspeedd=0;
int Lspeedd=0;
Servo myservo;


void setup() 
{
   Serial.begin(9600);
   leftright.attach(10); 
   updown.attach(11);
   leftright.write(90);
   updown.write(48);

   pinMode(pinLB,OUTPUT);
   pinMode(pinLF,OUTPUT); 
   pinMode(pinRB,OUTPUT); 
   pinMode(pinRF,OUTPUT);
   
   pinMode(MotorLPWM,OUTPUT);
   pinMode(MotorRPWM,OUTPUT);

   myservo.attach(4);
      
   pinMode(inputPin1, INPUT);    // 定義超音波輸入腳位
   pinMode(outputPin2, OUTPUT);  // 定義超音波輸出腳位 
   pinMode(inputPin3, INPUT);    // 定義超音波輸入腳位
   pinMode(outputPin4, OUTPUT);  // 定義超音波輸出腳位 
   pinMode(inputPin5, INPUT);    // 定義超音波輸入腳位
   pinMode(outputPin6, OUTPUT);  // 定義超音波輸出腳位   
   
   delay(200);
   Serial.println("Ready");
}

void ask_pin_F()   // 量出左邊距離 
    { 
      digitalWrite(outputPin2, LOW);   // 讓超聲波發射低電壓2μs
      delayMicroseconds(2);
      digitalWrite(outputPin2, HIGH);  // 讓超聲波發射高電壓10μs，這裡至少是10μs
      delayMicroseconds(10);
      digitalWrite(outputPin2, LOW);    // 維持超聲波發射低電壓
      F_distance = pulseIn(inputPin1, HIGH);  // 讀差相差時間
      F_distance= F_distance/5.8/10;       // 將時間轉為距離距离（單位：公分）
      //Serial.print("F distance:");       //輸出距離（單位：公分）
      //Serial.println(F_distance);         //顯示距離
    }
    
void ask_pin_R()   // 量出左邊距離 
    { 
      digitalWrite(outputPin4, LOW);   // 讓超聲波發射低電壓2μs
      delayMicroseconds(2);
      digitalWrite(outputPin4, HIGH);  // 讓超聲波發射高電壓10μs，這裡至少是10μs
      delayMicroseconds(10);
      digitalWrite(outputPin4, LOW);    // 維持超聲波發射低電壓
      R_distance = pulseIn(inputPin3, HIGH);  // 讀差相差時間
      R_distance= R_distance/5.8/10;       // 將時間轉為距離距离（單位：公分）
      //Serial.print("R distance:");       //輸出距離（單位：公分）
      //Serial.println(R_distance);         //顯示距離
    }
    
void ask_pin_L()   // 量出左邊距離 
    { 
      digitalWrite(outputPin6, LOW);   // 讓超聲波發射低電壓2μs
      delayMicroseconds(2);
      digitalWrite(outputPin6, HIGH);  // 讓超聲波發射高電壓10μs，這裡至少是10μs
      delayMicroseconds(10);
      digitalWrite(outputPin6, LOW);    // 維持超聲波發射低電壓
      L_distance = pulseIn(inputPin5, HIGH);  // 讀差相差時間
      L_distance= L_distance/5.8/10;       // 將時間轉為距離距离（單位：公分）
      //Serial.print("L distance:");       //輸出距離（單位：公分）
      //Serial.println(L_distance);         //顯示距離
    }
    
    
    
void foward(int f)
{
   digitalWrite(pinRB,LOW);
   digitalWrite(pinRF,HIGH);
   analogWrite(MotorRPWM,f);
   digitalWrite(pinLB,LOW);
   digitalWrite(pinLF,HIGH);
   analogWrite(MotorLPWM,f);
}

void back(float b)
{
   digitalWrite(pinRB,HIGH);
   digitalWrite(pinRF,LOW);
   analogWrite(MotorRPWM,120);
   digitalWrite(pinLB,HIGH);
   digitalWrite(pinLF,LOW);
   analogWrite(MotorLPWM,120);
   delay(b*100);
}

void turnR(int r)
{
   digitalWrite(pinRB,HIGH);
   digitalWrite(pinRF,LOW);
   analogWrite(MotorRPWM,r);
   digitalWrite(pinLB,LOW);
   digitalWrite(pinLF,HIGH);
   analogWrite(MotorLPWM,r);
}

void turnL(int l)
{
   digitalWrite(pinRB,LOW);
   digitalWrite(pinRF,HIGH);
   analogWrite(MotorRPWM,l);
   digitalWrite(pinLB,HIGH);
   digitalWrite(pinLF,LOW);
   analogWrite(MotorLPWM,l);
}

void stopp()
{
   digitalWrite(pinRB,LOW);
   digitalWrite(pinRF,LOW);
   analogWrite(MotorRPWM,200);
   digitalWrite(pinLB,LOW);
   digitalWrite(pinLF,LOW);
   analogWrite(MotorLPWM,200);
}

void loop() {
   if (Serial.available()>0)
{  
    
   i=Serial.read();
   
   switch (i){
    case 'R' :
      posX-=1;
      leftright.write(posX);
      delay(100);
      break;
      
    case 'T' :
      posX-=3;
      leftright.write(posX);
      delay(100);
      break;
      
    case 'Y' :
      posX-=5;
      leftright.write(posX);
      delay(100);
      break;
      
    case 'L' :
      posX+=1;
      leftright.write(posX);
      delay(100);
      break;
      
    case 'K' :
      posX+=3;
      leftright.write(posX);
      delay(100);
      break;
      
    case 'J' :
      posX+=5;
      leftright.write(posX);
      delay(100);
      break;
      
    case 'Q' :
      posX+=0;
      leftright.write(posX);
      delay(100);
      break;
      
      
    default:
      break;
   }  
      
   i=Serial.read();   
   switch (i){  
    case 'U' :
      posY-=1;
      updown.write(posY);
      delay(100);
      break;
      
    case 'H' :
      posY-=3;
      updown.write(posY);
      delay(100);
      break;  
      
    case 'D' :
      posY+=1;
      updown.write(posY);
      delay(100);
      break;
      
    case 'Z' :
      posY+=3;
      updown.write(posY);
      delay(100);
      break;  
      
    default:
      break;
   }
   
   i=Serial.read();
   
   switch(i){
     case'S':
     a=0;
     break;
     case'G':
     a=1;
     break;
     
     default:
     break;
   }
       ask_pin_F();
       ask_pin_R();
       ask_pin_L();
       if(F_distance<=30){
        if(R_distance>L_distance){
          
          while(true){
       
          stopp();
          delay(100);
          turnR(250);
          delay(600);
          stopp();
          delay(100);
          foward(140);
          delay(800);
          stopp();
          delay(100);
          turnL(250);
          delay(585);
          stopp();
          delay(1000);
          ask_pin_L();
          ask_pin_F();
          
          if(L_distance<=35||F_distance<=30){
          }
          else{
            
            foward(140);
            delay(1000);
            stopp();
            posY-=5;
            updown.write(posY);
            delay(100);
            a=0;
            
            break;
          }
        }
        }
        else if(L_distance>R_distance){
          
          while(true){
       
          stopp();
          delay(100);
          turnL(250);
          delay(585);
          stopp();
          delay(100);
          foward(140);
          delay(800);
          stopp();
          delay(100);
          turnR(250);
          delay(600);
          stopp();
          delay(1000);
          ask_pin_R();
          ask_pin_F();
          
          if(R_distance<=35||F_distance<=30){
          }
          else{
            
            foward(140);
            delay(1000);
            stopp();
            posY-=5;
            updown.write(posY);
            delay(100);
            a=0;
            break;
          }
        }
        }
       } 
       else if(R_distance<=30){
        
        turnL(225);
        delay(185);
        foward(140);
        delay(400);
        posX-=15;
        leftright.write(posX);
        stopp();
        delay(200);
        
       }
       
       else if(L_distance<=30){
        
        turnR(225);
        delay(200);
        foward(140);
        delay(400);
        posX+=15;
        leftright.write(posX);
        stopp();
        delay(200);
       }
       
   if(a==0){
    if(posX>110){
      posX=90;
      leftright.write(posX);
      turnL(250);
      delay(205);
      stopp();
}
   else if(posX<70){
      posX=90;
      leftright.write(posX);
      turnR(250);
      delay(220);
      stopp();
      
}
   else if(posX>=70 && posX<=110){
      stopp();
      delay(200);
}
}
   else if(a==1){
    if(posX>110){
      posX=90;
      leftright.write(posX);
      turnL(250);
      delay(205);
      stopp();
}
   else if(posX<70){
      posX=90;
      leftright.write(posX);
      turnR(250);
      delay(220);
      stopp();
}
   else if(posX>=70 && posX<=110){
      foward(140);
      delay(100);
}
}
}
else{
  stopp();
  delay(1000);
  if (Serial.available()>0){
  }
  else{  
    posY=48;
    updown.write(posY);
    for(posX=130 ; posX>=50 ; posX-=20){
      leftright.write(posX);
      stopp();
      delay(2000);
    if (Serial.available()>0){
      if(posX>=130){
      posX=90;
      leftright.write(posX);
      turnL(250);
      delay(335);
      stopp();
      break;
}
  else if(posX<=50){
      posX=90;
      leftright.write(posX);
      turnR(250);
      delay(350);
      stopp();
      break;
}
  else {
      break;
}
}
   else if(posX==50){
     turnR(250);
     delay(800);
     stopp();
     break;
}
}
}
}
}




















