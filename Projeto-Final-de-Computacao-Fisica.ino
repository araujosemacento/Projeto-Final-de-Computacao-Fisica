/*
 * O repositório documentado com todo o código está disponível em
 * https://github.com/araujosemacento/Projeto-Final-de-Computacao-Fisica
 */
// ANCHOR - Bibliotecas
#include <Wire.h>              // Biblioteca para comunicação I2C
#include <LiquidCrystal_I2C.h> // Biblioteca para controle do LCD via I2C
#include <EEPROM.h>            // Biblioteca para armazenamento não-volátil

// ANCHOR - Configuração do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço 0x27, display 16x2

// ANCHOR - Definição de Pinos
const int SENSOR_PIN = A0; // Sensor de umidade
const int POT_PIN = A1;    // Potenciômetro para calibração
const int BUZZER_PIN = 8;  // Buzzer para alertas sonoros
const int LED_R = 6;       // LED RGB - Pino Vermelho
const int LED_G = 5;       // LED RGB - Pino Verde
const int LED_B = 3;       // LED RGB - Pino Azul

// ANCHOR - Constantes de Tempo
const unsigned long HORA = 3600000;            // 1 hora em milissegundos
const unsigned long QUINZE_MIN = 900000;       // 15 minutos em milissegundos
const int INTERVALO_LEITURA = 1000;            // 1 segundo entre leituras (debug)
const unsigned long ALARME_INTERVALO = 15000;  // 15 segundos entre alarmes
const unsigned long CALIBRACAO_TIMEOUT = 3000; // 3 segundos para timeout
const int SETORES = 3;                         // Divisão em 3 níveis de umidade

// ANCHOR - Variáveis Globais
int umidadeIdeal = 0;            // Nível de umidade desejado
unsigned long ultimaLeitura = 0; // Controle de tempo entre leituras
unsigned long ultimoAlarme = 0;  // Controle de tempo entre alarmes
int ultimoValorPot = 0;          // Último valor lido do potenciômetro
unsigned long inicioTimer = 0;   // Timer para calibração

// ANCHOR - Arrays de Mensagens
const char *MSG_FELIZ[][2] = {
    {"Tudo bem", "por aqui!"},
    {"Vivendo a", "vida!"},
    {"Estou cres-", "cendo!"},
    {";-) Que dia", "lindo!"}};

const char *MSG_MOLHADA[][2] = {
    {"Estou afo-", "gando!"},
    {"Socorro, di-", "luvio!"},
    {"Muita agua", "aqui!"},
    {"Vou virar", "sopa! >_<"}};

const char *MSG_SECA[][2] = {
    {"Preciso", "de agua!"},
    {"Sede...", "muita sede"},
    {"Cade a", "chuva? :("},
    {"SOS!", "Deserto aqui!"}};

// ANCHOR - Inicialização
void setup()
{
  // Inicialização
  Wire.begin();
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  realizarCalibracao();
}

// ANCHOR - Função de Calibração
// SECTION - Processo de calibração do sensor
void realizarCalibracao()
{
  // TODO: Implementar salvamento na EEPROM
  // REVIEW: Considerar adicionar cancelamento da calibração
  lcd.clear();
  lcd.print("Calibracao");
  lcd.setCursor(0, 1);
  lcd.print("Gire o botao");

  delay(2000);

  bool calibrado = false;
  while (!calibrado)
  {
    int valorPot = analogRead(POT_PIN);
    int setor = map(valorPot, 0, 1023, 0, SETORES);

    if (valorPot != ultimoValorPot)
    {
      inicioTimer = millis();
      ultimoValorPot = valorPot;

      lcd.clear();
      lcd.print("Umidade:");
      lcd.setCursor(0, 1);
      switch (setor)
      {
      case 0:
        lcd.print("Pouca");
        break;
      case 1:
        lcd.print("Media");
        break;
      case 2:
        lcd.print("Muita");
        break;
      }
    }

    if (millis() - inicioTimer >= CALIBRACAO_TIMEOUT)
    {
      lcd.clear();
      lcd.print("Confirma?");
      delay(1000);

      int confirmacao = map(analogRead(POT_PIN), 0, 1023, 0, SETORES);
      if (confirmacao == 0)
      {
        umidadeIdeal = setor;
        calibrado = true;
        lcd.clear();
        lcd.print("Calibrado!");
        delay(1000);
      }
      else if (confirmacao == 2)
      {
        lcd.clear();
        lcd.print("Recalibrando...");
        delay(1000);
        inicioTimer = millis();
      }
    }
  }
}

// ANCHOR - Verificação de Umidade
// SECTION - Lógica principal de monitoramento
void verificarUmidade()
{
  // NOTE: Os setores são divididos em 3 níveis (0-2)
  // WARNING: Valores do sensor são invertidos (0 = molhado, 1023 = seco)
  int umidadeAtual = analogRead(SENSOR_PIN);
  int setorAtual = map(umidadeAtual, 0, 1023, 0, SETORES);
  int msgIndex = random(4);

  Serial.print("Umidade: ");
  Serial.println(umidadeAtual);

  lcd.clear();

  if (setorAtual == umidadeIdeal)
  {
    lcd.print(MSG_FELIZ[msgIndex][0]);
    lcd.setCursor(0, 1);
    lcd.print(MSG_FELIZ[msgIndex][1]);
    setLED(0, 255, 0); // Verde
    tone(BUZZER_PIN, 2000, 100);
  }
  else if (setorAtual > umidadeIdeal)
  {
    lcd.print(MSG_MOLHADA[msgIndex][0]);
    lcd.setCursor(0, 1);
    lcd.print(MSG_MOLHADA[msgIndex][1]);
    setLED(0, 0, 255); // Azul
    if (millis() - ultimoAlarme >= ALARME_INTERVALO)
    {
      tone(BUZZER_PIN, 1500, 500);
      ultimoAlarme = millis();
    }
  }
  else
  {
    lcd.print(MSG_SECA[msgIndex][0]);
    lcd.setCursor(0, 1);
    lcd.print(MSG_SECA[msgIndex][1]);
    setLED(255, 0, 0); // Vermelho
    if (millis() - ultimoAlarme >= ALARME_INTERVALO)
    {
      tone(BUZZER_PIN, 1000, 500);
      ultimoAlarme = millis();
    }
  }
}

// ANCHOR - Controle do LED RGB
// SECTION - Função auxiliar para controle do LED RGB
void setLED(int r, int g, int b)
{
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

// ANCHOR - Loop Principal
void loop()
{
  // REVIEW: Considerar adicionar botão de recalibração
  // TODO: Implementar modo de economia de energia
  if (millis() - ultimaLeitura >= QUINZE_MIN)
  {
    verificarUmidade();
    ultimaLeitura = millis();
  }
}