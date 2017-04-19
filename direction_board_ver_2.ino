#include <Servo.h>
  #define Register_ID 0
  #define Register_2D 0x2D
  #define Register_X0 0x32
  #define Register_X1 0x33
  #define Register_Y0 0x34
  #define Register_Y1 0x35
  #define Register_Z0 0x36
  #define Register_Z1 0x37

  #include <Wire.h>

  int ADXAddress = 0xA7 >> 1; // the default 7-bit slave address
  int reading = 0;
  int val=0;
  int X0,X1,X_out;
  int Y0,Y1,Y_out;
  int Z1,Z0,Z_out;
  int led = 13;
  int led1 = 12;
  int led2 = 11;
  int led3 =10;
  int led4 = 9;
  int led5=8;
  int led6=7;
  int led7=6;
  int enable1 = 5;
  int unable = 4;
  double Xg,Yg,Zg;
  double angle=0;
  int buttonPin1 = 3;
  int buttonPin2 = 2;
  int buttonPin3 = 1;
  int buttonState1 = 0;
  int buttonState2 = 0;
  int buttonState3 = 0;
  int ap1=0;
  int ap2=0;
  int ap3=0;
  int state1=0;
  int state2=0;
  
  Servo servo;

void setup()
{
  Wire.begin(); 
  Serial.begin(9600); 
  servo.attach(2);
  delay(100);
  // enable to measute g data
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8); //measuring enable
  Wire.endTransmission(); // stop transmitting
  pinMode(A1,INPUT);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(enable1, OUTPUT);  
  pinMode(unable, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2,INPUT);
  
 
 
}

void loop()
{
//--------------X
  Wire.beginTransmission(ADXAddress); // transmit to device
   Wire.write(Register_X0);
  Wire.write(Register_X1);
  Wire.endTransmission();
   Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2) 
   {
    X0 = Wire.read();
     X1 = Wire.read(); 
     X1=X1<<8;
     X_out=X0+X1; 
   }

//------------------Y
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
   if(Wire.available()<=2) 
  {
     Y0 = Wire.read();
     Y1 = Wire.read(); 
     Y1=Y1<<8;
     Y_out=Y0+Y1;
  }
  //------------------Z
   Wire.beginTransmission(ADXAddress); // transmit to device
   Wire.write(Register_Z0);
  Wire.write(Register_Z1);
   Wire.endTransmission();
   Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2) 
  {
    Z0 = Wire.read();
    Z1 = Wire.read(); 
    Z1=Z1<<8;
    Z_out=Z0+Z1;
  }
//
  Xg=X_out/256.0;
  Yg=Y_out/256.0;
  Zg=Z_out/256.0;
  angle = acos(Xg/sqrt(pow(Xg,2)+pow(Yg,2)));
  angle = (angle/3.14)*180;
  Serial.println(angle);
  servo.write(angle);
  Serial.print("X= ");
  Serial.print(Xg);
  Serial.print(" ");
  Serial.print("Y= ");
  Serial.print(Yg);
  Serial.print(" ");
  Serial.print("Z= ");
  Serial.print(Zg);
  Serial.println(" ");
  delay(500);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(A1);
  //--------------------------------------
    if (buttonState1==HIGH && ap1==0)
    {
      delay(200);
      if(buttonState1==HIGH && ap1==0)
      {
        state1=1;
        ap1=1;
      }
    }  
    if (buttonState1==LOW && ap1==1)
    {
      delay(200);
      if(buttonState1==LOW && ap1==1)
      {
        ap1=0;
      }
    }  
      //-----------------------------------
    if (buttonState2==HIGH && ap2==0)
    {
      delay(200);
      if(buttonState2==HIGH && ap2==0)
      {
        ap2=1;
        state2=1;
        
      }
    }  
    if (buttonState2==LOW && ap2==1)
    {
      delay(200);
      if(buttonState2==LOW && ap2==1)
      {
        ap2=0;
      }
    }
    //-----------------------
    if (buttonState3==HIGH && ap3==0)
    {
      delay(200);
      if(buttonState3==HIGH && ap3==0)
      {
        
        state1=0;
        state2=0;
        ap3=1;
      }
    }  
    if (buttonState3==LOW && ap3==1)
    {
      delay(200);
      if(buttonState3==LOW && ap3==1)
      {
        ap3=0;
      }
    }
    //----------------------
   if(state1==1 || Xg>0.30)
  { 
  digitalWrite(enable1, LOW);//left side
  digitalWrite(unable, HIGH);
  digitalWrite(led7, HIGH);
  delay(50);
  digitalWrite(led6, HIGH);
  delay(50);
  digitalWrite(led5, HIGH);
  delay(50);
  digitalWrite(led4, HIGH);
  delay(50);
  digitalWrite(led3, HIGH);
  delay(50);
  digitalWrite(led2, HIGH);
  delay(50);
  digitalWrite(led1, HIGH);
  delay(50);
  digitalWrite(led, HIGH);
  delay(50);
  digitalWrite(led7, LOW);
  delay(50);
  digitalWrite(led6, LOW);
  delay(50);
  digitalWrite(led5, LOW);
  delay(50);
  digitalWrite(led4, LOW);
  delay(50);
  digitalWrite(led3, LOW);
  delay(50);
  digitalWrite(led2, LOW);
  delay(50);
  digitalWrite(led1, LOW);
  delay(50);
  digitalWrite(led, LOW);
  delay(50);
 }
  if(state2==1 || Xg<0.20)
  {
    digitalWrite(enable1, HIGH);//right side
    digitalWrite(unable, LOW);
    digitalWrite(led7, HIGH);
    delay(50);
    digitalWrite(led6, HIGH);
    delay(50);
    digitalWrite(led5, HIGH);
    delay(50);
    digitalWrite(led4, HIGH);
    delay(50);
    digitalWrite(led3, HIGH);
    delay(50);
    digitalWrite(led2, HIGH);
    delay(50);
    digitalWrite(led1, HIGH);
    delay(50);
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led7, LOW);
    delay(50);
    digitalWrite(led6, LOW);
    delay(50);
    digitalWrite(led5, LOW);
    delay(50);
    digitalWrite(led4, LOW);
    delay(50);
    digitalWrite(led3, LOW);
    delay(50);
    digitalWrite(led2, LOW);
    delay(50);
    digitalWrite(led1, LOW);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);
  } 
}
      
