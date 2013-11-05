//int pwm_a = 10; //PWM control for motor outputs 1 and 2 is on digital pin 10
int pwm_a = 3;  //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //dir control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //dir control for motor outputs 3 and 4 is on digital pin 13

int sensorPin = 0; //analog pin 0

void setup()
{
  Serial.begin(9600);
  
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
  
  analogWrite(pwm_a, 150);        
  //set both motors to run at (100/255 = 39)% duty cycle (slow)  
  analogWrite(pwm_b, 150);
  
}

void stopMotor() 
{
    //stopping motors
    analogWrite(pwm_a, 0);        
    analogWrite(pwm_b, 0);
    delay(1000);
}

void loop()
{
  int val = analogRead(sensorPin);
  Serial.println(val);
  
  if (val<300) {
    digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
    digitalWrite(dir_b, LOW);  //Set motor direction, 3 high, 4 low
  }
    else
  {
    //если нет препятствий
    analogWrite(pwm_a, 0);        
    analogWrite(pwm_b, 0);
    delay(1000);
    
    while ( val>=300){
        val = analogRead(sensorPin);
        delay(100);
        analogWrite(pwm_as0);        
    analogWrite(pwm_b, 150);
        digitalWrite(dir_a, HIGH);  //Set motor direction, 1 low, 2 high
        digitalWrite(dir_b, LOW);
        Serial.println("while enter");
  }
  
}
  
  delay(100);

}


