int
left_motor_forward=4,
left_motor_backward=8,
right_motor_forward=2,
right_motor_backward=12,
left_motor_pwm=10,
right_motor_pwm=6;
char c;
void setup()
{
  Serial.begin(9600);
  pinMode(left_motor_forward,OUTPUT);
  pinMode(left_motor_backward,OUTPUT);
  pinMode(right_motor_forward,OUTPUT);
  pinMode(right_motor_backward,OUTPUT);
}
void loop()
{
  while(Serial.available())
  {
    c=Serial.read();
    if(c=='f')
    forward();
    else if(c=='b')
    backward();
    else if(c=='l')
    left_turn();
    else if(c=='r')
    right_turn();
    else if(c=='s')
    Stop();
  }
}
void forward()
{
  Serial.println("the bot will move forward");
  digitalWrite(left_motor_forward,1);
  digitalWrite(right_motor_forward,1);
  digitalWrite(left_motor_backward,0);
  digitalWrite(right_motor_backward,0);
  analogWrite(left_motor_pwm,150);
  analogWrite(right_motor_pwm,150);
  delay(1000);
  Stop();
}
void backward()
{
  Serial.println("the bot will move backward");
  digitalWrite(left_motor_backward,1);
  digitalWrite(right_motor_backward,1);
  digitalWrite(left_motor_forward,0);
  digitalWrite(right_motor_forward,0);
  analogWrite(left_motor_pwm,150);
  analogWrite(right_motor_pwm,150);
  delay(1000);
  Stop();
}
void right_turn()  //hard right turn
{
  Serial.println("the bot will take a hard right turn");
  digitalWrite(left_motor_forward,1);
  digitalWrite(right_motor_forward,0);
  digitalWrite(left_motor_backward,0);
  digitalWrite(right_motor_backward,1);
  analogWrite(left_motor_pwm,150);   
  analogWrite(right_motor_pwm,100);
  delay(300);   //you may have to vary the delay for perfect right turn..
  Stop();
}
void left_turn()    //hard left turn
{
  Serial.println("the bot will take a hard left turn");
  digitalWrite(left_motor_forward,0);
  digitalWrite(right_motor_forward,1);
  digitalWrite(left_motor_backward,1);
  digitalWrite(right_motor_backward,0);
  analogWrite(left_motor_pwm,100);
  analogWrite(right_motor_pwm,150);
  delay(300);   //you may have to vary the delay for perfect right turn..
  Stop();
}
void Stop()
{
  Serial.println("the bot will stop");
  analogWrite(left_motor_pwm,0);
  analogWrite(right_motor_pwm,0);
}

  
    
  
