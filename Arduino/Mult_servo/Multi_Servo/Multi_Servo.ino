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


//Position 1  
    //Indicador
    writeServos(0, 90);
    writeServos(1, 110);
    writeServos(2, 90);


    //Médio
    writeServos(3, 90);
    writeServos(4, 75);
    writeServos(5, 20);

    //ANELAR
    writeServos(6, 30);
    writeServos(7, 70);
    writeServos(8, 150);

    //MINDINHO
    writeServos(9, 90);
    writeServos(10, 90);
    writeServos(11, 60);


    //POLEGAR
    writeServos(12, 60);
    writeServos(13, 110);
    writeServos(14, 150);
    delay(500);

//Position 2

    //Indicador
    writeServos(0, 90);
    writeServos(1, 80);
    writeServos(2, 70);
    
    //Médio
    writeServos(3, 90);
    writeServos(4, 30);
    writeServos(5, 0);
    
    //ANELAR
    writeServos(7, 25);
    writeServos(8, 130);

    //MINDINHO
    writeServos(10, 30);
    writeServos(11, 30);

    //POLEGAR
    writeServos(12, 85);
    writeServos(13, 110);
    writeServos(14, 60);
    
    delay(500);

//Position 3

    //Indicador
    writeServos(0, 90);
    writeServos(1, 70);
    writeServos(2, 60);

    //Médio
    writeServos(3, 90);
    writeServos(4, 20);
    writeServos(5, -70);
    
    //ANELAR
    writeServos(7, 25);
    writeServos(8, 0);

    //MINDINHO
    writeServos(10, -20);
    writeServos(11, 0);

    //POLEGAR
    writeServos(12, 100);
    writeServos(13, 110);
    writeServos(14, 130);
    delay(500);
  


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
