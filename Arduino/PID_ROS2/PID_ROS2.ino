#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

////////////// Servo Control //////////////////////////////
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  205 // VALOR PARA UM PULSO MAIOR QUE 1 mS
#define SERVOMAX  409 // VALOR PARA UM PULSO MENOR QUE 2 mS

#define SIG1 A0
#define SIG2 A1

#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define S4 5
#define S5 6

//////////// Poteciometre Reader ////////////////////////
int mix[4] = {S3, S2, S1, S0};

int valores_analogicos[20];

int valor;

byte ci[16][4] = {
  {0, 0, 0, 0}, // 0
  {0, 0, 0, 1}, // 1
  {0, 0, 1, 0}, // 2
  {0, 0, 1, 1}, // 3
  {0, 1, 0, 0}, // 4
  {0, 1, 0, 1}, // 5
  {0, 1, 1, 0}, // 6
  {0, 1, 1, 1}, // 7
  {1, 0, 0, 0}, // 8
  {1, 0, 0, 1}, // 9
  {1, 0, 1, 0}, // 10
  {1, 0, 1, 1}, // 11
  {1, 1, 0, 0}, // 12
  {1, 1, 0, 1}, // 13
  {1, 1, 1, 0}, // 14
  {1, 1, 1, 1}  // 15 
};


///////////////// Motor correspondente a cada junta  ////////////////// 
int motor[] = {
   2, // 0 potenciometro
   2, // 1
   1, // 2
   0, // 3
   5 ,// 4
   5, // 5
   4, // 6
   3, // 7
   8, // 8
   8, // 9
   7, // 10
   6, // 11
   11,// 12
   11,// 13
   10,// 14
   9, // 15 
   14,// 16
   14,// 17
   13,// 18
   12// 19 
};

/////////////////// PID Val ////////////////////

int potValue;       // Valor lido do potenciômetro
int output[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Final[] = {300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300};
int lastError[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  ///////////|      indicador       |   Médio              |    Anelar             |      Mindinho         |      Polegar
float KP[] = {1, 1, 0.65, 0.65, 0.5, 0.51, 0.1, 0.65, 0.5, 1, 0.1, 0.65,    0.80, 0.80, 0.05, 0.80, 0.25, 0.8, 0.1, 0.85};     // Constante proporcional
float KI[] = {0.3, 0.3, 0.3, 0.3,    0.3, 0.3, 0.01, 0.3,   0.3, 0.3, 0.001, 0.03, 0.3, 0.3, 0.3, 0.01, 0.1, 0.3, 0.001, 0.3};   // Constante integrativa
float KD[] = {0.5, 0.5, 0.5, 0.5,    0.5, 0.5, 0.1, 0.2,    0.5, 0.5, 0.01, 0.5,   0.5, 0.5, 0.5, 0.1, 0.1, 0.5, 0.01, 0.5};    // Constante derivativa










void setup() {
  pwm.begin();

  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT);
  pinMode(S5, OUTPUT);

  pwm.setPWMFreq(50);
  delay(300);
}

void loop() {
  //multiplex();
  // Indicador
    position_control(3,90);  // Conector
    position_control(2,90);  // Falange 1
    position_control(1,90);  // Falange 2
   // position_control(0,90);  // Falange 3

  // Médio
    position_control(7,90); // Conector
    position_control(6,75);  // Falange 1
    position_control(5,90);  // Falange 2
    position_control(4,110);  // Falange 3

  // Anelar
    position_control(11,90);  // Conector
    position_control(10,75);  // Falange 1
 // position_control(9,0);  // Falange 2
  //position_control(8,0);  // Falange 3


  // Mindinho
    position_control(15,90);  // Conector
    position_control(14,20);  // Falange 1
  // position_control(13,90);  // Falange 2
 // position_control(12,30);  // Falange 3

  // Polegar
     position_control(19,157); // Conector
   // position_control(18,10);  // Falange 1
   // position_control(16,25);  // Falange 3
  
  Serial.println(lastError[3]);
  delay(210);
}

















void multiplex() {
  for (int x = 0; x <= 15; x++) {
    digitalWrite(S0, ci[x][3]);
    digitalWrite(S1, ci[x][2]);
    digitalWrite(S2, ci[x][1]);
    digitalWrite(S3, ci[x][0]);
    valores_analogicos[x] = analogRead(SIG1);
  }

  for (int x = 0; x <= 3; x++) {
    digitalWrite(S4, ci[x][3]);
    digitalWrite(S5, ci[x][2]);
    valores_analogicos[16 + x] = analogRead(SIG2);
  }
}


void position_control(int joint, int setpoint){
  multiplex();
  
  int joint_value = valores_analogicos[joint]; // Lê a posição atual do motor
  int error = (180 - map(joint_value, 1, 1023, 0, 180)) - setpoint; // Calcula o erro


  int P_term = KP[joint] * error;          // Termo proporcional
  int I_term = KI[joint] * (error + lastError[joint]); // Termo integrativo
  int D_term = KD[joint] * (error - lastError[joint]); // Termo derivativo

  output[joint] = (P_term + I_term + D_term); // Soma os termos para obter a saída do PID

  if (joint == 0 or joint == 1 or joint == 4 or joint == 5 or joint == 8 or joint == 9 or joint == 12 or joint == 13 or joint == 16 or joint == 17){
    Final[joint] = Final[joint] - output[joint];
  }
    
  else{
    Final[joint] = Final[joint] + output[joint];
  }
  
  if (Final[joint] > 600 or Final[joint] < 0){
    Final[joint] = 300;
  }

  pwm.setPWM(motor[joint], 0, Final[joint]); // Define a posição do motor

  lastError[joint] = error;
  }
