#define D1 12          // Направление вращение двигателя 1
#define M1 3          // ШИМ вывод для управления двигателем 1
#define D2 13          // Направление вращение двигателя 2
#define M2 11          // ШИМ вывод для управления двигателем 2

#include <Servo.h> 
 

Servo myservo;

String analogSensorMSG;
String convBuffer;
String servoStatus;

int irSensorBC = 0;
int irSensorFV = 1;

int valSensorBC =0;
int valSensorFV =0;

float sensorValue, inches, cm; 

int statusPC=0;

int obFV[5];


boolean statusRad=0;

void setup() 
{ 
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);  
  myservo.attach(9);

  Serial.begin(9600);
} 

void loop() 
{ 
  while (Serial.available() > 0) {
  statusPC = Serial.parseInt(); }
  
  if (statusPC==1 && statusPC!=0){ 
  // forvard();
  // back();
  // left(); 
  // right();
  // stopf();
  servoradar();
  analis();
  }
  else {
  stopservoradar();
  }
  if (statusPC==0){
    myservo.write(90); 
  }
  
} 

void analis()
{
  for(int pos =0 ; pos <= 4; pos += 1)  
  {
    if (pos!=4){  
      Serial.print(obFV[pos]);
      Serial.print(",");}
    else {
      Serial.println(obFV[pos]);}
  }
  
  if ()

}



void stopservoradar()
{
  valSensorBC  = analogRead(irSensorBC);
  delay(1500); 
  valSensorFV= analogRead(irSensorFV);
  Serial.println(valSensorFV);
}

void servoradar()
{
    int ang[4];
  
    ang[0] = 10; ang[1] = 45; ang[2] = 90;
    ang[3] = 135; ang[4] = 160; 
  
    
  for(int pos =0 ; pos <= 4; pos += 1)  
  {  
    myservo.write(ang[pos]); 

    delay(100);
    valSensorFV = analogRead(irSensorFV);
    obFV[pos]=valSensorFV;
    
    Serial.print(ang[pos]);
    Serial.print(",");
    Serial.println(valSensorFV);
    
  }
  
  myservo.write(10); 
  delay(250);
}

void forvard()
{
  ///////////////////////////////////////////////////
  analogWrite(D1, 0);  
  analogWrite(M1, 255);

  analogWrite(D2, 0);
  analogWrite(M2, 255);       

  delay(2000);
  ////////////////////////////////////////////////////
}

void back()
{
  ////////////////////////////////////////////////////
  analogWrite(D1, 255);  
  analogWrite(M1, 0);

  analogWrite(D2, 255);
  analogWrite(M2, 0);       

  delay(2000);
  /////////////////////////////////////////////////////
}


void left()
{
  ////////////////ВПРАВО///////////////////////////////  
  analogWrite(D1, 255);  
  analogWrite(M1, 0);

  analogWrite(D2, 0);
  analogWrite(M2, 255);       

  delay(2000);
  ////////////////////////////////////////////////////

}

void right()
{

  ////////////////ВПРАВО///////////////////////////////  
  analogWrite(D1, 255);  // Задаем направление вращения
  analogWrite(M1, 0);

  analogWrite(D2, 0);
  analogWrite(M2, 255);       // Задаем скорость вращения 

  delay(2000);
  //////////////////////////////////////////////////

}

void stopf()
{
  ///////////////////////////////////////////////////
  analogWrite(D1, 0);  
  analogWrite(M1, 0);

  analogWrite(D2, 0);
  analogWrite(M2, 0);       

  delay(2000);
  ////////////////////////////////////////////////////
}

