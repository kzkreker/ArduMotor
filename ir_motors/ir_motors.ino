//информационные строки
String analogSensorMSG;
String convBuffer;
String motorStatus;

//статус моторов
int mode, leftSpeed, rightSpeed;

//Привязка выходов платы к чипу L296
int pwm_a = 3;  //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //dir control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //dir control for motor outputs 3 and 4 is on digital pin 13

//////////////////////////////////////////////////////////////////
///установка базовых настроек платы
//////////////////////////////////////////////////////////////////

void setup() {
    // устанавливаем скорость UART 
    Serial.begin(9600);
    
    // изменение конфигурации пинов(выходы)
    pinMode(pwm_a, OUTPUT); 
    pinMode(pwm_b, OUTPUT);
    pinMode(dir_a, OUTPUT);
    pinMode(dir_b, OUTPUT);
  
    analogWrite(pwm_a, 0);        
    analogWrite(pwm_b, 0);
}

///////////////////////////////////////////////////////////////
///цикл обработки
///////////////////////////////////////////////////////////////
void loop() {
    
    //статус моторов
    getIrMotorStatus();
    //прием настроек
    resivMotors();
    //отправка статуса на компьютер
    messageConc();
       
    delay(100); 

}

////////////////////////////////////////////////////////////
///Формирование строки состояния платы
////////////////////////////////////////////////////////////
void messageConc()
{   
    //собираем строку
    motorStatus="MT:"+String(mode)+","+String(leftSpeed)+","+String(rightSpeed); 
    
    Serial.println(motorStatus+"," + analogSensorMSG);
}

//////////////////////////////////////////////////////////
///Прием скорости и режима работы двигателей
//////////////////////////////////////////////////////////
void resivMotors()
{
 while (Serial.available() > 0) {

    // последовательно разбираем строку полученную с ПК
    mode = Serial.parseInt(); 
    leftSpeed = Serial.parseInt(); 
    rightSpeed = Serial.parseInt(); 
    
    //если строка закончилась * устанавливаем скорость мотора
    if (Serial.read() == '*') 
    {
        setMotorSpeed();
    }
  }
}


//////////////////////////////////////////////////////////
///установка режима работы двигателя и его скорости
//////////////////////////////////////////////////////////
void setMotorSpeed()
{
//проверка валидности полученных данных
if (mode>=0 && mode<=5 && leftSpeed>=0 && 
    leftSpeed<=255 && rightSpeed>=0 &&  rightSpeed<=255)
    {
    switch (mode) {
    case 0:    
        digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
        digitalWrite(dir_b, LOW);
        analogWrite(pwm_a, leftSpeed);        
        analogWrite(pwm_b, rightSpeed);  
    break;
    
    case 1:    
        digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
        digitalWrite(dir_b, HIGH);
        analogWrite(pwm_a, leftSpeed);        
        analogWrite(pwm_b, rightSpeed);  
    break;
    
    case 2:    
        digitalWrite(dir_a, HIGH);  //Set motor direction, 1 low, 2 high
        digitalWrite(dir_b, LOW);
        analogWrite(pwm_a, leftSpeed);        
        analogWrite(pwm_b, rightSpeed);  
    break;
   
    case 3:    
        digitalWrite(dir_a, HIGH);  //Set motor direction, 1 low, 2 high
        digitalWrite(dir_b, HIGH);
        analogWrite(pwm_a, leftSpeed);        
        analogWrite(pwm_b, rightSpeed);  
    break;
   
    }   
  }
}

//////////////////////////////////////////////////////////
///поочередный опрос датчиков и формирование строки с препятствиями.
//////////////////////////////////////////////////////////
void getIrMotorStatus()
{
  for (int i=0; i<6; i++)
  {
    convBuffer=String(analogRead(i));
    
    if(i==0)
    {
     analogSensorMSG="AN:"+ convBuffer+",";
    }
    else if(i>0 && i<5)
    {
      analogSensorMSG= analogSensorMSG + convBuffer+",";
    }
    else if(i==5)
    {
      analogSensorMSG= analogSensorMSG + convBuffer;
    }
  } 
}
