#include <Keypad.h>
#include <EEPROM.h>

#define pin_r 1
#define pin_g 2
#define pin_buzzer 3
#define sensor_echo 4
#define sensor_trig 5
#define buzzer 3

char aux = '0';

const byte colunas = 4;
const byte linhas = 4;

char chaves[linhas][colunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
  };

byte linhas_pinos[linhas] = {6,7,8,9};
byte colunas_pinos[colunas] = {10,11,12,13};

long duracao;
int distancia_inicial;
int distancia;

int dist_init(int distancia_inicial,long duracao);

int comando = 1;
int senha = 0;

Keypad teclado = Keypad(makeKeymap(chaves),linhas_pinos,colunas_pinos,linhas,colunas);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_r, OUTPUT);
  pinMode(pin_g, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
  pinMode(sensor_echo, INPUT);
  pinMode(sensor_trig, OUTPUT);

  distancia_inicial = dist_init(distancia_inicial,duracao);

  for(int i = 0; i < 4; i++){
    EEPROM.write(i,aux);
    }

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin_r, LOW);
  digitalWrite(pin_g, LOW);
  
  digitalWrite(sensor_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_trig, LOW);

  duracao = pulseIn(sensor_echo, HIGH);
  distancia = duracao*0.034/2;
  
  if(teclado.getKey() == '*' || comando == 0){
    senhaNova();
    digitalWrite(pin_r, HIGH);
    digitalWrite(pin_g, HIGH);
    delay(200);
    }
  else if(comando == 0){
    int correto = 0;
    
    for(int i = 0; i < 4; i++){
      char tecla = teclado.getKey();
      if(tecla != EEPROM.read(i)){
        digitalWrite(pin_r, HIGH);
        delay(200);
        break;
        }
      else{
        correto++;
        }
      }
   if(correto == 4){
    senha = 1;
    digitalWrite(pin_g, HIGH);
        delay(200);
    }
    }

  if(distancia <= distancia_inicial){
    if(senha){
      senha = 0;
      delay(5000);
      }
    else{
      digitalWrite(pin_r, HIGH);
      tone(buzzer,1500);
      delay(1000);
      noTone(buzzer);
      }
    }

  
  

}

int dist_init(int distancia_inicial,long duracao) {

  digitalWrite(sensor_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_trig, LOW);

  duracao = pulseIn(sensor_echo, HIGH);
  distancia_inicial = duracao*0.034/2;
  return distancia_inicial;
  
  }

void senhaNova(){
  for(int i = 0; i < 4; i++){
    char tecla = teclado.getKey();
    EEPROM.write(i,tecla);
    }
  }