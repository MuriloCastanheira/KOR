/*
     Q0470
     AUTOR:   BrincandoComIdeias
     LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/
     COMPRE:  https://www.arducore.com.br/
     SKETCH:  PWM I2C
     DATA:    04/06/2019
*/

// INCLUSÃO DE BIBLIOTECAS
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// INSTANCIANDO OBJETOS
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// DECLARAÇÃO DE FUNÇÕES
void writeServos(int posicao, int tempo);
void beginServos();

void setup() {
  beginServos(); // INICIA OS SERVOS
  delay(300);
}

void transicaoSuave(int posicaoInicial[], int posicaoFinal[], int duracao) {
  // Número de passos para a transição
  int passos = 100;
  
  // Loop para alterar suavemente os valores dos servos
  for (int i = 0; i <= passos; i++) {
    for (int j = 0; j < 15; j++) {
      int anguloAtual = posicaoInicial[j] + (posicaoFinal[j] - posicaoInicial[j]) * i / passos;
      writeServos(j, anguloAtual);
    }
    delay(duracao / passos); // Ajuste a duração total da transição aqui
  }
}

void loop() {


  // Definindo as posições iniciais e finais
  int posicaoInicial1[] = {90, 110, 130, 90, 75, 20, 30, 90, 40, 120, 90, 0, 110, 150};
  int posicaoFinal2[] = {90, 80, 70, 90, 30, 0, 30, 25, 130, 40, 30, 30, 25, 130, 150};
  int posicaoFinal3[] = {90, 70, 60, 90, 20, -70, 30, 25, 0, 40, -20, 0, 90, 120, 150};
  
  int posicaoFinal4[] = {90, 70, 60, 90, 20, -70, 30, 25, 0, 90, -30, 10, 130, 110, 130};
  int posicaoFinal5[] = {90, 120, 160, 90, 90, 110, 30, 0, 0, 90, -30, 10, 70, 50, 130};

  // Realizando a transição suave entre as duas posições
  transicaoSuave(posicaoInicial1, posicaoFinal2, 500);

  // Aguardando um tempo antes de retornar à posição inicial
  delay(500);

  // Retornando à posição inicial
  transicaoSuave(posicaoFinal2, posicaoFinal3, 500);

  delay(500);

  transicaoSuave(posicaoFinal3, posicaoInicial1, 500);

  delay(500);




  transicaoSuave(posicaoInicial1, posicaoFinal2, 500);

  // Aguardando um tempo antes de retornar à posição inicial
  delay(500);

  // Retornando à posição inicial
  transicaoSuave(posicaoFinal2, posicaoFinal3, 500);

  delay(500);

  transicaoSuave(posicaoFinal3, posicaoInicial1, 500);

  delay(500);



   transicaoSuave(posicaoInicial1, posicaoFinal2, 500);

  // Aguardando um tempo antes de retornar à posição inicial
  delay(500);

  // Retornando à posição inicial
  transicaoSuave(posicaoFinal2, posicaoFinal3, 500);

  delay(500);

  transicaoSuave(posicaoFinal3, posicaoInicial1, 500);

  delay(500);


    // Retornando à posição inicial
  transicaoSuave(posicaoFinal3, posicaoFinal4, 500);

  delay(1000);

  transicaoSuave(posicaoFinal4, posicaoFinal5, 10);

  delay(50000);











}

// IMPLEMENTO DE FUNÇÕES
void writeServos(int nServo, int posicao) {
#define SERVOMIN  205 // VALOR PARA UM PULSO MAIOR QUE 1 mS
#define SERVOMAX  409 // VALOR PARA UM PULSO MENOR QUE 2 mS

  int pos = map ( posicao , 0 , 180 , SERVOMIN, SERVOMAX);
  pwm.setPWM(nServo , 0, pos);
}

void beginServos() {

#define Frequencia 50 // VALOR DA FREQUENCIA DO SERVO 

  pwm.begin(); // INICIA O OBJETO PWM
  pwm.setPWMFreq(Frequencia); // DEFINE A FREQUENCIA DE TRABALHO DO SERVO
}
