#define left_motor_forward 8
#define left_motor_backward 9
#define left_motor_pwm 10
#define right_motor_pwm 11
#define right_motor_forward 12
#define right_motor_backward 7
#define input_left 2
#define input_right 3
#define set_point 2000
#define max_speed 100 //Set Max Motor Speed
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
int sensors[8]={0,0,0,0,0,0,0,0};   
int Position=0;
int error_value=0;
void setup()
{
  Serial.begin(9600);
  pinMode(left_motor_forward,OUTPUT);
  pinMode(left_motor_backward,OUTPUT);
  pinMode(right_motor_forward,OUTPUT);
  pinMode(right_motor_backward,OUTPUT);
  pinMode(input_left,INPUT);
  pinMode(input_right,INPUT);
}
void Stop()
{
  analogWrite(left_motor_pwm,0);
  analogWrite(right_motor_pwm,0);
  
  delay(100);
}

void backward()
{
  Serial.println("the bot will move backward");
  digitalWrite(left_motor_backward,1);
  digitalWrite(right_motor_backward,1);
  digitalWrite(left_motor_forward,0);
  digitalWrite(right_motor_forward,0);
  analogWrite(left_motor_pwm,75);
  analogWrite(right_motor_pwm,75);
  delay(150);
  Stop();
}
void pid_calc() 
{
   
  
  proportional=Position-set_point;
  integral = integral + proportional; 
  derivative = proportional - last_proportional; 
  last_proportional = proportional;    
  error_value = int((proportional * Kp) + (integral * Ki) + (derivative * Kd));
  Serial.println("Error Value=");
  
  Serial.println(error_value);
  
if (error_value< -256)     
  { 
error_value = -256; 
  }  
if (error_value> 256) 
  { 
error_value = 256; 
  }  

if (error_value< 0) 
  { 
left_speed= max_speed + error_value; 
right_speed = max_speed; 
  } 
  else 
  { 
left_speed = max_speed; 
right_speed = max_speed - error_value; 
  }


  if (right_speed>255)
      right_speed=255;
  if (right_speed<0)
      right_speed=0;
  if (left_speed>255)
      left_speed=255;
  if (left_speed<0)
      left_speed=0;
  Serial.println("Left Speed=");
  Serial.println(left_speed);
  Serial.println("Right Speed=");
  Serial.println(right_speed);
  
  digitalWrite(left_motor_forward,1);
  digitalWrite(right_motor_forward,1);
  digitalWrite(left_motor_backward,0);
  digitalWrite(right_motor_backward,0);
  analogWrite(left_motor_pwm,left_speed);
  analogWrite(right_motor_pwm,right_speed);
  delay(200);
}



void loop() 
{
int i;
sensors_average = 0; 
sensors_sum = 0;
 
  for (i = 0; i <=5; i++) 
   {
    sensors[i] = analogRead(i);
   }
    sensors[6]=digitalRead(input_left);
    sensors[7]=digitalRead(input_right);
   for(i=0;i<=5;i++)
   { 
    if(sensors[i]<100)
      sensors[i]=0;
      
    else
      sensors[i]=1;
   }
   for(int i=0;i<=7;i++)
    {
    sensors_average += sensors[i] * i * 1000   ;  
    sensors_sum += sensors[i];
    }
    Serial.println("Analog Value=");
    for(int i=0;i<=7;i++)
    {
      Serial.println(sensors[i]);
      
    }
    if(sensors_sum==0)
    {
      Stop();
      backward();
      
    }
    else
      {
        Position=int(sensors_average/sensors_sum);
        Serial.println("Position=");
        Serial.println(Position);
        pid_calc();
        Stop();
      }
}
