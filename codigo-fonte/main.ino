#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>

#define pinoRele 8
#define pinoSensor A0

int umidade;

int turn = 0;
int array_pins[3] = {11, 12, 13};
 
void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(pinoRele, OUTPUT);
  digitalWrite(pinoRele, HIGH);
}

void loop() {
  Serial.println("Iniciando Leitura ...");
  umidade = analogRead(pinoSensor);
  Serial.print("Umidade: ");
  Serial.println(umidade);
  if(turn == 16){
    turn = 0;
  }
  ascende_3(turn);
  turn++;
  if(umidade >= 360){
    liga_rele();
  }
  Serial.println("Aguardando...");
  aguardo();
  Serial.println("-----------------");
}

// Funcao de ligar o rele
void liga_rele(){
  Serial.println("Ligando Bomba");
  digitalWrite(pinoRele, LOW);
  liga_pisca();
  Serial.println("Desligando Bomba");
  digitalWrite(pinoRele, HIGH);
}
void pisca_av(){
  digitalWrite(4,HIGH);
  delay(70);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  delay(70);
  digitalWrite(5,LOW);
}
void liga_pisca(){
  for(int i=0; i<20; i++){
    pisca_av();
  }
}
void ascende_3(int rodada){
  if (rodada%2 == 0)
  {
    for(int i = 0; i < 3; i++){
      digitalWrite(array_pins[i],HIGH);
      //pisca_av();
      delay(180);
      digitalWrite(array_pins[i],LOW);
    }
  }
  else
  {
    for(int i = 2; i > -1; i--){
      digitalWrite(array_pins[i],HIGH);
      //pisca_av();
      delay(180);
      digitalWrite(array_pins[i],LOW);
    
    }
  }
}
void aguardo(){
  for(int i=0; i<25; i++){
    ascende_3(i);
  }
}
