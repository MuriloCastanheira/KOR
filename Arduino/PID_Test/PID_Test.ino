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

//////////// Ponteciometre Reader ////////////////////////
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

/////////////////// PID Val ////////////////////

int setpoint;       // Valor desejado do potenciômetro
int potValue;       // Valor lido do potenciômetro
int output;         // Saída do PID
int lastError = 0;  // Último erro
int Final = 300;
  
float KP = 0.2;     // Constante proporcional
float KI = 0.001;   // Constante integrativa
float KD = 0.01;    // Constante derivativa


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
  multiplex();

  setpoint =  30; // Mapeia o valor do potenciômetro para

  int motorPosition = valores_analogicos[1]; // Lê a posição atual do motor
  int error = (180 - map(motorPosition, 2, 1023, 0, 180)) - setpoint; // Calcula o erro


  int P_term = KP * error;          // Termo proporcional
  int I_term = KI * (error + lastError); // Termo integrativo
  int D_term = KD * (error - lastError); // Termo derivativo

  output = (P_term + I_term + D_term); // Soma os termos para obter a saída do PID

  Final = Final - output;

  
  if (Final > 500 or Final < 100){
    Final = 300;
  }

  
  pwm.setPWM(2, 0, Final); // Define a posição do motor

  lastError = error; // Atualiza o último erro

  // Imprime informações para depuração
  Serial.print("Potenciômetro: ");
  Serial.print(potValue);
  Serial.print(" | Setpoint: ");
  Serial.print(setpoint);
  Serial.print(" | Saída: ");
  Serial.print(P_term + I_term + D_term);
  Serial.print(" | Output: ");
  Serial.print(output);
  Serial.print(" | Final: ");
  Serial.print(Final);
  Serial.print(" | Error: ");
  Serial.print(error);
  Serial.print(" | Posição Real: ");
  Serial.print(180 - map(valores_analogicos[1], 0, 1023, 0, 180));
  Serial.println();

  delay(10);
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
