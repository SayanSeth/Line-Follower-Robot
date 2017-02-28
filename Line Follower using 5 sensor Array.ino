#define left_motor_forward 8
#define left_motor_backward 9
#define left_motor_pwm 10
#define right_motor_pwm 11
#define right_motor_forward 12
#define right_motor_backward 13

#define set_point 2000
#define max_speed 200 //set Max Speed Value
#define Kp 0 //set Kp Value
#define Ki 0 //set Ki Value
#define Kd 0 //set Kd Value

int proportional=0;
int integral=0;
int derivative=0;
int last_proportional=0;
int right_speed=0;
int left_speed=0;
int sensors_sum=0;
int sensors_average=0;
int sensors[5]={0,0,0,0,0};
int Position=0;
int error_value=0;
void setup()
{
  pinMode(right_motor_forward,OUTPUT);
  pinMode(right_motor_backward,OUTPUT);
}
void Stop()
{
  analogWrite(left_motor_pwm,0);
  analogWrite(right_motor_pwm,0);
  delay(500);
}
void pid_calc() 
{
   
  
  proportional=Position-set_point;
  integral = integral + proportional; 
  derivative = proportional - last_proportional; 
  last_proportional = proportional;    
  error_value = int(proportional * Kp + integral * Ki + derivative * Kd); 
}
void calc_turn() 
{  
                                              //Restricting the error value between +256. 
if (error_value< -256)     
  { 
error_value = -256; 
  }  
if (error_value> 256) 
  { 
error_value = 256; 
  }  
                                              // If error_value is less than zero calculate right turn speed values 
if (error_value< 0) 
  { 
right_speed = max_speed + error_value; 
left_speed = max_speed; 
  } 
  else 
  { 
right_speed = max_speed; 
left_speed = max_speed - error_value; 
  } 
}
void motor_drive (int right_speed,int left_speed)
{
  if (right_speed>255)
      right_speed=255;
  if (right_speed<0)
      right_speed=0;
  if (left_speed>255)
      left_speed=255;
  if (left_speed<0)
      left_speed=0;
   
  digitalWrite(left_motor_forward,1);
  digitalWrite(right_motor_forward,1);
  digitalWrite(left_motor_backward,0);
  digitalWrite(right_motor_backward,0);
  analogWrite(left_motor_pwm,left_speed);
  analogWrite(right_motor_pwm,right_speed);
  delay(100);
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

void loop() 
{
int  sensors_average = 0; 
  sensors_sum = 0;
 
  for (int i = 0; i <=4; i++) 
   {
    sensors[i] = analogRead(i); 
    sensors_average += sensors[i] * i * 1000   ;  
    sensors_sum += sensors[i];
    }
  if(sensors_sum==0)
  {
    Stop();    
  }
  if (sensors_sum >= 3500)
  {
   forward();
  }
               
  if(sensors_sum < 3500 && sensors_sum > 0)
      {
        Position = int(sensors_average / sensors_sum);
        pid_calc();
        calc_turn();
        motor_drive(right_speed,left_speed);
      }
  
  
 delay(500); 
}
