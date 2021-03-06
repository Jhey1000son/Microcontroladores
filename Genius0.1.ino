//Vamos comear definindo as notas para os sons
#define NOTE_D4  200
#define NOTE_G4  500
#define NOTE_A4  1000
#define NOTE_A5  2000
#define NOTE_E   330
#define NOTE_C   260
#define NOTE_G   390
#define NOTE_G1   195
 
int tons[4] = { NOTE_A5, NOTE_A4, NOTE_G4, NOTE_D4 };
int sequencia[100] = {};
int rodada_atual = 0;
int passo_atual_na_sequencia = 0;

 int audio = 10;
int pinoAudio = 10;
int pinosLeds[4] = { 2, 4, 6, 8 };
int pinosBotoes[4] = { 3, 5, 7, 9 };
int botao_pressionado = 0;
int perdeu_o_jogo = false;
 
void setup() {
  for (int i = 0; i <= 3; i++) {
    pinMode(pinosLeds[i], OUTPUT);
  }
 
  // Definindo o modo dos pinos dos Botes como entrada.
  for (int i = 0; i <= 3; i++) {
    pinMode(pinosBotoes[i], INPUT_PULLUP);
  }
 
  pinMode(pinoAudio, OUTPUT);
  
  randomSeed(analogRead(0));
  Serial.begin(230400);
}
 
void loop() {

  if (perdeu_o_jogo) {
    int sequencia[100] = {};
    rodada_atual = 0;
    passo_atual_na_sequencia = 0;
    perdeu_o_jogo = false;
  }
 
  if (rodada_atual == 0) {
    tocarSomDeInicio();
    delay(500);
  }
 
  proximaRodada();
  reproduzirSequencia();
  aguardarJogador();
  
  delay(1000);
}
 
void proximaRodada() {
  int numero_sorteado = random(0, 4);
  sequencia[rodada_atual++] = numero_sorteado;
}
 
void reproduzirSequencia() {
  for (int i = 0; i < rodada_atual; i++) {
    tone(pinoAudio, tons[sequencia[i]]);
    digitalWrite(pinosLeds[sequencia[i]], HIGH);
    delay(500);
    noTone(pinoAudio);
    digitalWrite(pinosLeds[sequencia[i]], LOW);
    delay(100);
  }
  noTone(pinoAudio);
}
 
void aguardarJogador() {
  for (int i = 0; i < rodada_atual; i++) {
    aguardarJogada();
    verificarJogada();
 
    if (perdeu_o_jogo) {
      break;
    }
 
    passo_atual_na_sequencia++;
  }
 
  passo_atual_na_sequencia = 0;
}
 
void aguardarJogada() {
  boolean jogada_efetuada = false;
  while (!jogada_efetuada) {
    for (int i = 0; i <= 3; i++) {
      if (!digitalRead(pinosBotoes[i]) == HIGH) {

        botao_pressionado = i;

        tone(pinoAudio, tons[i]);
        digitalWrite(pinosLeds[i], HIGH);
        delay(300);
        digitalWrite(pinosLeds[i], LOW);
        noTone(pinoAudio);
 
        jogada_efetuada = true;
      }
    }
    delay(10);
  }
}
 
void verificarJogada() {
  if (sequencia[passo_atual_na_sequencia] != botao_pressionado) {
    // GAME OVER.
    for (int i = 0; i <= 3; i++) {
      tone(pinoAudio, tons[i]);
      digitalWrite(pinosLeds[i], HIGH);
      delay(200);
      digitalWrite(pinosLeds[i], LOW);
      noTone(pinoAudio);
    }
 
    tone(pinoAudio, tons[3]);
    for (int i = 0; i <= 3; i++) {
      digitalWrite(pinosLeds[0], HIGH);
      digitalWrite(pinosLeds[1], HIGH);
      digitalWrite(pinosLeds[2], HIGH);
      digitalWrite(pinosLeds[3], HIGH);
      delay(100);
      digitalWrite(pinosLeds[0], LOW);
      digitalWrite(pinosLeds[1], LOW);
      digitalWrite(pinosLeds[2], LOW);
      digitalWrite(pinosLeds[3], LOW);
      delay(100);
    }
    noTone(pinoAudio);
 
    perdeu_o_jogo = true;
  }
}
 
void tocarSomDeInicio() {
  tone(audio, NOTE_E);
  digitalWrite(pinosLeds[0], HIGH);
  delay(200);
  digitalWrite(pinosLeds[0], LOW);
  noTone(audio);
  delay(50);
  tone(audio, NOTE_E);
  digitalWrite(pinosLeds[0], HIGH);
  delay(200);
  digitalWrite(pinosLeds[0], LOW);
  noTone(audio);
  delay(50);
  tone(audio, NOTE_E);
  digitalWrite(pinosLeds[0], HIGH);
  delay(300);
  digitalWrite(pinosLeds[0], LOW);
  noTone(audio);
  delay(50);
  tone(audio, NOTE_C);
  digitalWrite(pinosLeds[2], HIGH);
  delay(100);
  digitalWrite(pinosLeds[2], LOW);
  noTone(audio);
  delay(50);
  tone(audio, NOTE_E);
  digitalWrite(pinosLeds[0], HIGH);
  delay(300);
  digitalWrite(pinosLeds[0], LOW);
  noTone(audio);
  tone(audio, NOTE_G);
  digitalWrite(pinosLeds[3], HIGH);
  delay(400);
  digitalWrite(pinosLeds[3], LOW);
  delay(50);
  noTone(audio);
  tone(audio, NOTE_G1);
  digitalWrite(pinosLeds[1], HIGH);
  delay(800);
  noTone(audio);
  delay(1000);
  digitalWrite(pinosLeds[0], HIGH);
  digitalWrite(pinosLeds[1], HIGH);
  digitalWrite(pinosLeds[2], HIGH);
  digitalWrite(pinosLeds[3], HIGH);
  delay(500);
  digitalWrite(pinosLeds[0], LOW);
  digitalWrite(pinosLeds[1], LOW);
  digitalWrite(pinosLeds[2], LOW);
  digitalWrite(pinosLeds[3], LOW);
  delay(500);
  
}
