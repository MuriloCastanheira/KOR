#define SIG1 A0
#define SIG2 A1

#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define S4 5
#define S5 6


int mix[4] = {S3,S2,S1,S0};

int valores_analogicos[20];

int valor;

byte ci[16][4] = {
  {0,0,0,0}, // 0
  {0,0,0,1}, // 1
  {0,0,1,0}, // 2
  {0,0,1,1}, // 3
  {0,1,0,0}, // 4
  {0,1,0,1}, // 5
  {0,1,1,0}, // 6
  {0,1,1,1}, // 7
  {1,0,0,0}, // 8
  {1,0,0,1}, // 9
  {1,0,1,0}, // 10
  {1,0,1,1}, // 11
  {1,1,0,0}, // 12
  {1,1,0,1}, // 13
  {1,1,1,0}, // 14
  {1,1,1,1}  // 15 
};

void setup() {
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT);
  pinMode(S5, OUTPUT);
}

void loop() {
  
  multiplex();

  Serial.print("Indicado - Falange 3 = ");
  Serial.println(180 - (map(valores_analogicos[0], 0, 1023, 0, 180)));

  Serial.print("Indicado - Falange 2 = ");
  Serial.println(180 - (map(valores_analogicos[1], 0, 1023, 0, 180)));

  Serial.print("Indicado - Falange 1 = ");
  Serial.println(171 - (map(valores_analogicos[2], 0, 1023, 0, 180)));

  Serial.print("Indicado - Falange 0 = ");
  Serial.println(180 - (map(valores_analogicos[3], 0, 1023, 0, 180)));
  
  Serial.println("");
//////////////////////////////////////////////////////////////////////////

  Serial.print("Medio - Falange 3 = ");
  Serial.println(180 - (map(valores_analogicos[4], 0, 1023, 0, 180)));

  Serial.print("Medio - Falange 2 = ");
  Serial.println(180 - (map(valores_analogicos[5], 0, 1023, 0, 180)));

  Serial.print("Medio - Falange 1 = ");
  Serial.println(180 - (map(valores_analogicos[6], 0, 1023, 0, 180)));

  Serial.print("Medio - Falange 0 = ");
  Serial.println(180 - (map(valores_analogicos[7], 0, 1023, 0, 180)));

  Serial.println("");
//////////////////////////////////////////////////////////////////////////

  Serial.print("Anelar - Falange 3 = ");
  Serial.println(180 - (map(valores_analogicos[8], 0, 1023, 0, 180)));

  Serial.print("Anelar - Falange 2 = ");
  Serial.println(180 - (map(valores_analogicos[9], 0, 1023, 0, 180)));

  Serial.print("Anelar - Falange 1 = ");
  Serial.println(180 - (map(valores_analogicos[10], 0, 1023, 0, 180)));

  Serial.print("Anelar - Falange 0 = ");
  Serial.println(180 - (map(valores_analogicos[11], 0, 1023, 0, 180)));
  
  Serial.println("");

 //////////////////////////////////////////////////////////////////////////

  Serial.print("Mindinho - Falange 3 = ");
  Serial.println(180 - (map(valores_analogicos[12], 0, 1023, 0, 180)));

  Serial.print("Mindinho - Falange 2 = ");
  Serial.println(180 - (map(valores_analogicos[13], 0, 1023, 0, 180)));

  Serial.print("Mindinho - Falange 1 = ");
  Serial.println(180 - (map(valores_analogicos[14], 0, 1023, 0, 180)));

  Serial.print("Mindinho - Falange 0 = ");
  Serial.println(180 - (map(valores_analogicos[15], 0, 1023, 0, 180)));
  
  Serial.println("");

 //////////////////////////////////////////////////////////////////////////

  Serial.print("Polegar - Falange 3 = ");
  Serial.println(180 - (map(valores_analogicos[16], 0, 1023, 0, 180)));

  Serial.print("Polegar - Falange 2 = ");
  Serial.println(180 - (map(valores_analogicos[17], 0, 1023, 0, 180)));

  Serial.print("Polegar - Falange 1 = ");
  Serial.println(180 - (map(valores_analogicos[18], 0, 1023, 0, 180)));

  Serial.print("Polegar - Falange 0 = ");
  Serial.println(180 - (map(valores_analogicos[19], 0, 1023, 0, 180)));
  
  Serial.println("");



  delay(500);
}


void multiplex(){
   for (int x=0; x <= 15; x++){

    digitalWrite(S0, ci[x][3]);
    digitalWrite(S1, ci[x][2]);
    digitalWrite(S2, ci[x][1]);
    digitalWrite(S3, ci[x][0]);
    
    valores_analogicos[x] = analogRead(SIG1);
   }


  for (int x=0; x <= 3; x++){
    digitalWrite(S4, ci[x][3]);
    digitalWrite(S5, ci[x][2]);

    
    valores_analogicos[16 + x] = analogRead(SIG2);
  }

    

   
}
