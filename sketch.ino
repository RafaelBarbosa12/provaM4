#include <WiFi.h>
#include <HTTPClient.h>

#define led_azul 9 // Pino utilizado para controle do led azul
#define led_verde 41 // Pino utilizado para controle do led verda
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led azul

const int pino_botao = 18;  // número da porta do botão
int estado_botao = 0;  // verifica o estado do botão

const int pino_ldr = 4;  // número da porta do ldr
int claridade=600;

int estadoLDR=analogRead(pino_ldr);

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_azul,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);

  // Inicialização das entradas
  pinMode(pino_botao, INPUT); // Inicializa o botão como entrada

  digitalWrite(led_azul, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  // Verifica estado do botão
  estado_botao = digitalRead(pino_botao);
  if (estado_botao == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String caminhoServidor = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(caminhoServidor.c_str());

    int codigoRespostaHttp = http.GET(); // Código do Resultado da Requisição HTTP

    if (codigoRespostaHttp>0) {
      Serial.print("codigo de resposta http: ");
      Serial.println(codigoRespostaHttp);
      String payload = http.getString();
      Serial.println(payload);
      }
    else {
      Serial.print("Erro de código: ");
      Serial.println(codigoRespostaHttp);
      }
      http.end();
    }

  else {
    Serial.println("WiFi Desconectado");
  }
}

void loop() {

  if(estadoLDR<=claridade){
    Serial.print("Está escuro, ligue o led");
    Serial.println(estadoLDR);
    digitalWrite(led_amarelo, HIGH); // Acende o amarelo
    delay(1000);                    // 1 segundo
    digitalWrite(led_amarelo, LOW);  // Apaga o amarelo

  }else{
    Serial.print("está claro, desligue o led");
    Serial.println(estadoLDR);
    digitalWrite(led_verde, HIGH); // Acende o verde
    delay(3000);                   // 3 segundos
    digitalWrite(led_verde, LOW);  // Apaga o verde

    digitalWrite(led_amarelo, HIGH); // Acende o amarelo
    delay(2000);                    // 2 segundos
    digitalWrite(led_amarelo, LOW);  // Apaga o amarelo

    digitalWrite(led_vermelho, HIGH); // Acende o vermelho
    delay(5000);                 // 5 segundos
    digitalWrite(led_vermelho, LOW);  // Apaga o vermelho
    if (digitalRead(estado_botao) == HIGH) {
      if (digitalRead(estado_botao) == HIGH) {
        delay(1000);    
        digitalWrite(led_verde, HIGH); // Liga o LED
  } 
    }

  }
}