
void setupMotor1();
void setupMotor2();
void Forward(uint8_t driverN);
void Reverse(uint8_t driverN);
void StopAll();

int IN1_1 = A0; 
int IN2_1 = A1; 
int IN3_1 = A2;
int IN4_1 = A3;


int IN1_2 = A7; 
int IN2_2 = A6; 
int IN3_2 = A5;
int IN4_2 = A4;
void setupMotor1()
{
  pinMode(IN1_1, OUTPUT);
  pinMode(IN2_1, OUTPUT);
  pinMode(IN3_1, OUTPUT);
  pinMode(IN4_1, OUTPUT);
}
void setupMotor2()
{
  pinMode(IN1_2, OUTPUT);
  pinMode(IN2_2, OUTPUT);
  pinMode(IN3_2, OUTPUT);
  pinMode(IN4_2, OUTPUT);
}



void Forward(uint8_t driverN)
{
  if(driverN==1){
  digitalWrite(IN1_1, HIGH);
  digitalWrite(IN2_1, LOW);
  
  digitalWrite(IN3_1, HIGH);
  digitalWrite(IN4_1, LOW);  
  }

  else if(driverN==2){
  digitalWrite(IN1_2, HIGH);
  digitalWrite(IN2_2, LOW);
  
  digitalWrite(IN3_2, HIGH);
  digitalWrite(IN4_2, LOW);  
  }
}

void Reverse(uint8_t driverN)
{
  if(driverN==1){
  digitalWrite(IN1_1, LOW); 
  digitalWrite(IN2_1, HIGH);
  
  digitalWrite(IN3_1, LOW); 
  digitalWrite(IN4_1, HIGH);
  }

  else if(driverN==2){
  digitalWrite(IN1_2, LOW); 
  digitalWrite(IN2_2, HIGH);
  
  digitalWrite(IN3_2, LOW); 
  digitalWrite(IN4_2, HIGH);      
    }

}

void StopAll()
{
    digitalWrite(IN1_1, LOW);
    digitalWrite(IN2_1, LOW);
    
    digitalWrite(IN3_1, LOW);
    digitalWrite(IN4_1, LOW);
    
    digitalWrite(IN1_2, LOW);
    digitalWrite(IN2_2, LOW);
    
    digitalWrite(IN3_2, LOW);
    digitalWrite(IN4_2, LOW);
    
}
