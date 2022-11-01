#define PWM_A   5
#define DIR_1_A 7
#define DIR_2_A 8
#define PWM_B   3
#define DIR_1_B 4
#define DIR_2_B 6

void setup() {
  pinMode(PWM_A,OUTPUT);
  pinMode(PWM_B,OUTPUT);
  pinMode(DIR_1_A,OUTPUT);
  pinMode(DIR_2_A,OUTPUT);
  pinMode(DIR_1_B,OUTPUT);
  pinMode(DIR_2_B,OUTPUT);

  for (unsigned long int t = millis(); t+1000>millis();) 
    test_step();
  off();
}

void loop() {
  
}

void test_step() {
  digitalWrite(PWM_A,1);
  digitalWrite(PWM_B,1);
  for (int i = 0; i<4; i++) {
    digitalWrite(DIR_1_A,i==1||i==2);
    digitalWrite(DIR_2_A,i==0||i==3);
    digitalWrite(DIR_1_B,i>1);
    digitalWrite(DIR_2_B,i<2);
    delay(3);
  }
}

void off() {
  digitalWrite(PWM_A,0);
  digitalWrite(PWM_B,0);
  digitalWrite(DIR_1_A,0);
  digitalWrite(DIR_2_A,0);
  digitalWrite(DIR_1_B,0);
  digitalWrite(DIR_2_B,0);
}
