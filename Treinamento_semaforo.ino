#define  pin_r 4
#define pin_y 5
#define pin_g 6
#define pin_button 7
#define pin_rped 8
#define pin_gped 9

int sinal = 0;
int ped;
int botao_acionado = 0;

unsigned long tempo_at;
unsigned long tempo_prev = millis();
unsigned long intervalo;
unsigned long tempo_botao = millis();
unsigned long intervalo_botao;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_r, OUTPUT);
  pinMode(pin_y, OUTPUT);
  pinMode(pin_g, OUTPUT);
  pinMode(pin_rped, OUTPUT);
  pinMode(pin_gped,OUTPUT);
  pinMode(pin_button, INPUT_PULLUP);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  sinal++;
  tempo_at = millis();
  intervalo = tempo_at - tempo_prev;
  intervalo_botao = tempo_at - tempo_botao;
  ped = digitalRead(pin_button);
  if(ped == HIGH || (botao_acionado != 0 && intervalo_botao < 8000)){
    if(intervalo >= 0 && intervalo < 2000){
      digitalWrite(pin_y,LOW);
      digitalWrite(pin_r,HIGH);
      digitalWrite(pin_rped,LOW);
      digitalWrite(pin_gped,HIGH);
      }
    else if (intervalo >= 2000 && intervalo < 5000){
      digitalWrite(pin_r,LOW);
      digitalWrite(pin_g, HIGH);
      digitalWrite(pin_gped,LOW);
      digitalWrite(pin_rped,HIGH);
      if(intervalo >= 4000){
        delay(200);
        digitalWrite(pin_rped,LOW);
        delay(200);
        }
      }
    else if (intervalo >= 3000 && intervalo < 6000){
      digitalWrite(pin_g,LOW);
      digitalWrite(pin_y, HIGH);
      digitalWrite(pin_gped,LOW);
      digitalWrite(pin_rped,HIGH);
      }
    else{
      tempo_prev = millis();
      }
    }
  else{
    digitalWrite(pin_g,LOW);
    digitalWrite(pin_y,LOW);
    digitalWrite(pin_r,HIGH);
    digitalWrite(pin_gped,HIGH);
    digitalWrite(pin_rped,LOW);
    tempo_prev = millis();
    tempo_botao = millis();
    botao_acionado = 1;
    }
    
}
