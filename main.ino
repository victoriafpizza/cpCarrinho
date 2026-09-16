// ============================================================
// PROGRAMA 1 - ESP32 INSTALADO NO CARRINHO
// ============================================================
// Este ESP32 cria uma rede Wi-Fi própria, atua como servidor
// MQTT e recebe os valores X e Y enviados pelo ESP32 do joystick.
// A partir desses valores, calcula a velocidade dos motores
// esquerdo e direito e controla as duas pontes H.
// ============================================================


// Biblioteca responsável pelas funções de Wi-Fi do ESP32.
#include <WiFi.h>

// Biblioteca utilizada para criar um Broker/Servidor MQTT
// diretamente no ESP32 do carrinho.
#include <PicoMQTT.h>

// Biblioteca utilizada para interpretar as mensagens JSON
// recebidas pelo MQTT.
#include <ArduinoJson.h>

// ==========================================

// Mapeamento dos Pinos

// ==========================================


// ------------------------------------------------------------
// Motor Dianteiro Direito (DD)
// ------------------------------------------------------------
// Pino PWM utilizado para controlar a velocidade do
// motor dianteiro direito.
const int PinoPWMDD = 25;

// Pinos digitais ligados à ponte H.
// Eles determinam o sentido de rotação do motor.
const int pinoIN1_1 = 26;

const int pinoIN1_2 = 27;


// ------------------------------------------------------------
// Motor Dianteiro Esquerdo (DE)
// ------------------------------------------------------------
// PWM responsável pela velocidade do motor dianteiro esquerdo.
const int PinoPWMDE = 13;

// Entradas da ponte H responsáveis pela direção desse motor.
const int pinoIN2_1 = 12;

const int pinoIN2_2 = 14;


// ------------------------------------------------------------
// Motor Traseiro Direito (TD)
// ------------------------------------------------------------
// PWM responsável pela velocidade do motor traseiro direito.
const int PinoPWMTD = 15;

// Pinos de direção ligados à ponte H.
const int pinoIN3_1 = 2;

const int pinoIN3_2 = 4;


// ------------------------------------------------------------
// Motor Traseiro Esquerdo (TE)
// ------------------------------------------------------------
// PWM responsável pela velocidade do motor traseiro esquerdo.
const int PinoPWMTE = 18;

// Pinos utilizados para definir o sentido do motor.
const int pinoIN4_1 = 19;

const int pinoIN4_2 = 21;


// ==========================================

// Configurações do PWM (ESP32)

// ==========================================

// Define a frequência utilizada pelo sinal PWM.
// O PWM é responsável principalmente pelo controle
// da potência/velocidade enviada aos motores.
const int freq = 5000;       // Frequência de 5 kHz

// Define uma resolução de 8 bits.
// Isso permite valores entre 0 e 255 para a potência.
const int resolucao = 8;     // Resolução de 8 bits (Valores de 0 a 255)


// ==========================================

// Configurações de Rede (Access Point)

// ==========================================

// Nome da rede Wi-Fi que será criada pelo ESP32 do carrinho.
const char* ap_ssid = "ESP32_Rede_MQTT";

// Senha da rede Wi-Fi criada pelo carrinho.
const char* ap_password = "senha12345";


// Cria o objeto responsável pelo servidor MQTT.
// Neste projeto, o próprio ESP32 do carrinho funciona
// como Broker MQTT.
PicoMQTT::Server mqtt_server;


// ==========================================

// Função Auxiliar de Controle dos Motores

// ==========================================


// Esta função recebe:
// velocidade -> velocidade e sentido desejados;
// in1/in2    -> pinos que controlam o sentido da ponte H;
// pwm1/pwm2  -> pinos PWM utilizados para controlar potência.
//
// Valores positivos fazem o motor girar em um sentido.
// Valores negativos fazem o motor girar no sentido contrário.
// Valor zero faz o motor parar.
void controlarLado(int velocidade, int in1, int in2, int pwm1, int pwm2) {

  // Limita o valor da velocidade ao intervalo permitido
  // pelo PWM de 8 bits: -255 até +255.
  velocidade = constrain(velocidade, -255, 255);


  // Se a velocidade for positiva, configura a ponte H
  // para movimentar o motor em um sentido.
  if (velocidade > 0) {

    digitalWrite(in1, HIGH);

    digitalWrite(in2, LOW);


  // Se a velocidade for negativa, inverte os sinais
  // da ponte H e consequentemente o sentido do motor.
  } else if (velocidade < 0) {

    digitalWrite(in1, LOW);

    digitalWrite(in2, HIGH);


  // Se a velocidade for zero, desliga as duas entradas,
  // provocando a parada do motor.
  } else {

    digitalWrite(in1, LOW);

    digitalWrite(in2, LOW);0

  }


  // abs() remove o sinal negativo.
  // Para o PWM interessa apenas a intensidade da potência.
  int potencia = abs(velocidade);


  // Envia a potência calculada para os canais PWM.
  // Quanto maior o valor, maior a potência aplicada.
  ledcWrite(pwm1, potencia);

  ledcWrite(pwm2, potencia);

}


// ============================================================
// SETUP DO ESP32 DO CARRINHO
// ============================================================
// A função setup() é executada apenas uma vez quando
// o ESP32 é ligado ou reiniciado.
// ============================================================

void setup() {


  // Inicializa a comunicação Serial em 115200 baud.
  // É utilizada para acompanhar mensagens e diagnósticos
  // pelo Monitor Serial.
  Serial.begin(115200);


  // Configura os pinos das pontes H como SAÍDA

  // Todos esses pinos enviam sinais do ESP32 para as
  // duas pontes H.
  pinMode(pinoIN1_1, OUTPUT);

  pinMode(pinoIN1_2, OUTPUT);

  pinMode(pinoIN2_1, OUTPUT);

  pinMode(pinoIN2_2, OUTPUT);

  pinMode(pinoIN3_1, OUTPUT);

  pinMode(pinoIN3_2, OUTPUT);

  pinMode(pinoIN4_1, OUTPUT);

  pinMode(pinoIN4_2, OUTPUT);


  // Configura o PWM nos pinos de controle de velocidade

  // Liga os quatro pinos PWM ao sistema PWM do ESP32,
  // utilizando frequência de 5 kHz e resolução de 8 bits.
  ledcAttach(PinoPWMDD, freq, resolucao);

  ledcAttach(PinoPWMDE, freq, resolucao);

  ledcAttach(PinoPWMTD, freq, resolucao);

  ledcAttach(PinoPWMTE, freq, resolucao);


  // Inicia o Access Point Wi-Fi

  // O ESP32 do carrinho cria sua própria rede Wi-Fi.
  // O ESP32 do controle deverá se conectar a essa rede.
  WiFi.softAP(ap_ssid, ap_password);


  // Mostra no Monitor Serial que a rede foi criada.
  Serial.print("\nRede Wi-Fi criada! IP do Broker: ");


  // Exibe o endereço IP do próprio Access Point.
  // Normalmente esse endereço será 192.168.4.1.
  Serial.println(WiFi.softAPIP());


  // Inscreve no tópico do joystick ("#" escuta qualquer tópico se preferir, ou o tópico específico "carrinho/joystick")

  // O servidor MQTT passa a "escutar" mensagens publicadas
  // no tópico carrinho/joystick.
  //
  // Quando uma mensagem chega, a função lambda abaixo
  // é executada automaticamente.
  mqtt_server.subscribe("carrinho/joystick", [](const char * topic, const char * payload) {


    // Cria um documento JSON onde serão armazenados
    // os dados recebidos do joystick.
    JsonDocument doc;


    // Converte o texto recebido pelo MQTT em uma
    // estrutura JSON utilizável pelo programa.
    DeserializationError error = deserializeJson(doc, payload);


    // Verifica se ocorreu algum erro durante
    // a conversão do JSON.
    if (error) {


      // Se houver erro, mostra a mensagem no Monitor Serial.
      Serial.print("Erro no JSON: ");

      Serial.println(error.c_str());


      // Interrompe o processamento desta mensagem,
      // evitando utilizar dados inválidos.
      return;

    }


    // Obtém o valor do eixo X enviado pelo joystick.
    // Caso não exista valor "x", utiliza 0.
    int x = doc["x"] | 0;


    // Obtém o valor do eixo Y enviado pelo joystick.
    // Caso não exista valor "y", utiliza 0.
    int y = doc["y"] | 0;


    // Lógica de Direção Diferencial

    // Soma X e Y para determinar a velocidade
    // do conjunto de motores do lado esquerdo.
    int velEsquerda = y + x;


    // Subtrai X de Y para determinar a velocidade
    // do conjunto de motores do lado direito.
    int velDireita  = y - x;


    // Essa técnica permite transformar os dois eixos
    // do joystick em movimentos como:
    //
    // frente;
    // ré;
    // curva para esquerda;
    // curva para direita;
    // combinações entre direção e velocidade.


    // Motores Lado Esquerdo

    // Controla o motor dianteiro esquerdo utilizando
    // a velocidade calculada para o lado esquerdo.
    controlarLado(velEsquerda, pinoIN2_1, pinoIN2_2, PinoPWMDE, PinoPWMTE);


    // Controla o motor traseiro esquerdo com
    // a mesma velocidade do lado esquerdo.
    controlarLado(velEsquerda, pinoIN4_1, pinoIN4_2, PinoPWMDE, PinoPWMTE);


    // Motores Lado Direito

    // Controla o motor dianteiro direito.
    controlarLado(velDireita, pinoIN1_1, pinoIN1_2, PinoPWMDD, PinoPWMTD);


    // Controla o motor traseiro direito.
    controlarLado(velDireita, pinoIN3_1, pinoIN3_2, PinoPWMDD, PinoPWMTD);

  });


  // Inicia o servidor MQTT sem parâmetros

  // A partir deste momento, o ESP32 passa a funcionar
  // como Broker MQTT e pode receber mensagens.
  mqtt_server.begin();


  // Apenas informa pelo Monitor Serial que
  // o servidor está funcionando.
  Serial.println("Broker MQTT pronto para receber comandos!");

}


// ============================================================
// LOOP DO ESP32 DO CARRINHO
// ============================================================
// loop() é executado continuamente enquanto o ESP32 estiver
// ligado.
// ============================================================

void loop() {


  // Mantém o servidor MQTT funcionando e processa
  // novas conexões e mensagens recebidas.
  mqtt_server.loop();

}




// ============================================================
// PROGRAMA 2 - ESP32 DO CONTROLE / JOYSTICK SHIELD
// ============================================================
// Este é o código responsável pelo segundo ESP32.
//
// Ele lê os movimentos do joystick conectado à shield,
// transforma os valores em uma escala de -255 até 255,
// conecta-se à rede Wi-Fi criada pelo carrinho e envia
// os valores X e Y através de MQTT.
// ============================================================


// Biblioteca responsável pela conexão Wi-Fi.
#include <WiFi.h>


// Biblioteca responsável pelo funcionamento do ESP32
// como cliente MQTT.
#include <PubSubClient.h>


// Biblioteca utilizada para criar a mensagem JSON
// contendo os valores X e Y.
#include <ArduinoJson.h>


// Definição dos pinos analógicos do Joystick

// GPIO 34 recebe o valor analógico do eixo horizontal X.
const int pinX = 34; // Eixo X


// GPIO 35 recebe o valor analógico do eixo vertical Y.
const int pinY = 35; // Eixo Y


// Credenciais da rede Wi-Fi gerada pelo carrinho

// Nome da rede Wi-Fi criada pelo primeiro ESP32.
const char* ssid = "ESP32_Rede_MQTT";


// Senha utilizada para conectar à rede do carrinho.
const char* password = "senha12345";


// IP do servidor MQTT (Broker no carrinho)

// Endereço padrão do ESP32 quando trabalha
// no modo Access Point.
const char* mqtt_server = "192.168.4.1"; // IP padrão do Access Point do ESP32


// Porta padrão utilizada pelo protocolo MQTT.
const int mqtt_port = 1883;


// Cria um cliente de rede Wi-Fi utilizado
// posteriormente pela biblioteca MQTT.
WiFiClient espClient;


// Cria o cliente MQTT utilizando a conexão Wi-Fi acima.
PubSubClient client(espClient);


// ============================================================
// FUNÇÃO DE CONEXÃO WI-FI
// ============================================================
// Responsável por conectar o ESP32 do joystick
// à rede criada pelo ESP32 do carrinho.
// ============================================================

void setupWiFi() {


  // Pequeno atraso antes de iniciar a conexão.
  delay(10);


  // Mostra no Monitor Serial a rede que
  // o ESP32 tentará acessar.
  Serial.print("Conectando à rede Wi-Fi: ");

  Serial.println(ssid);


  // Inicia a tentativa de conexão à rede
  // utilizando SSID e senha definidos anteriormente.
  WiFi.begin(ssid, password);


  // Enquanto a conexão não for estabelecida,
  // o código permanece neste loop.
  while (WiFi.status() != WL_CONNECTED) {


    // Aguarda meio segundo entre verificações.
    delay(500);


    // Imprime pontos no Monitor Serial indicando
    // que ainda está tentando conectar.
    Serial.print(".");

  }


  // Quando sai do while, significa que a conexão
  // Wi-Fi foi concluída.
  Serial.println("\nWi-Fi conectado!");


  // Mostra o endereço IP recebido pelo ESP32 controle.
  Serial.print("Endereço IP obtido: ");

  Serial.println(WiFi.localIP());

}


// ============================================================
// FUNÇÃO DE RECONEXÃO MQTT
// ============================================================
// Garante que o controle continue conectado ao Broker MQTT.
// Caso a conexão seja perdida, tenta novamente automaticamente.
// ============================================================

void reconnectMQTT() {


  // Permanece tentando enquanto o cliente MQTT
  // não estiver conectado.
  while (!client.connected()) {


    // Informação exibida para diagnóstico.
    Serial.print("Tentando conexão MQTT...");


    // Tenta conectar usando um ID de cliente único

    // ESP32_Joystick_Client identifica este dispositivo
    // dentro da comunicação MQTT.
    if (client.connect("ESP32_Joystick_Client")) {


      // Executado caso a conexão tenha funcionado.
      Serial.println("Conectado ao Broker MQTT do carrinho!");


    } else {


      // Caso a conexão falhe, exibe uma mensagem.
      Serial.print("Falha na conexão. Código de erro=");


      // client.state() retorna o código do erro MQTT.
      Serial.print(client.state());


      // Informa que será realizada nova tentativa.
      Serial.println(". Tentando novamente em 2 segundos...");


      // Aguarda dois segundos antes da próxima tentativa.
      delay(2000);

    }

  }

}


// ============================================================
// SETUP DO ESP32 DO JOYSTICK
// ============================================================

void setup() {


  // Inicializa o Monitor Serial.
  Serial.begin(115200);


  // Configuração dos pinos do Joystick como entradas

  // Como o joystick gera sinais analógicos,
  // esses GPIOs são utilizados como entrada.
  pinMode(pinX, INPUT);

  pinMode(pinY, INPUT);


  // Conecta ao Wi-Fi e configura o cliente MQTT

  // Chama a função responsável pela conexão com
  // a rede criada pelo carrinho.
  setupWiFi();


  // Informa ao cliente MQTT qual é o endereço
  // e a porta do Broker.
  client.setServer(mqtt_server, mqtt_port);

}


// ============================================================
// LOOP DO ESP32 DO JOYSTICK
// ============================================================

void loop() {


  // Verifica se a comunicação MQTT está ativa.
  if (!client.connected()) {


    // Caso tenha sido perdida, tenta reconectar.
    reconnectMQTT();

  }


  // Mantém a comunicação MQTT funcionando.
  client.loop();


  // Lê os valores analógicos brutos (0 a 4095 no ESP32)

  // O conversor ADC do ESP32 retorna valores
  // entre aproximadamente 0 e 4095.
  int valorBrutoX = analogRead(pinX);

  int valorBrutoY = analogRead(pinY);


  // Mapeia o intervalo de 0..4095 para -255..255

  // Nota: A inversão dos limites no mapa permite ajustar o sentido do movimento se necessário

  // Converte a leitura do joystick para a mesma escala
  // utilizada pelo controle PWM dos motores.
  int mapX = map(valorBrutoX, 0, 4095, -255, 255);

  int mapY = map(valorBrutoY, 0, 4095, -255, 255);


  // Aplica uma zona morta central para evitar ruidos do potenciômetro parado

  // Um joystick físico dificilmente retorna exatamente zero
  // quando está no centro.
  //
  // Por isso, qualquer valor pequeno entre aproximadamente
  // -19 e +19 é considerado zero.
  //
  // Isso evita que o carrinho se mova sozinho por pequenos
  // ruídos elétricos ou imprecisão do joystick.
  if (abs(mapX) < 20) mapX = 0;

  if (abs(mapY) < 20) mapY = 0;


  // Monta a estrutura JSON com as chaves "x" e "y" esperadas pelo carrinho

  // Cria um pequeno documento JSON com espaço suficiente
  // para armazenar os dois valores.
  StaticJsonDocument<128> doc;


  // Insere a posição horizontal do joystick.
  doc["x"] = mapX;


  // Insere a posição vertical do joystick.
  doc["y"] = mapY;


  // Cria um vetor de caracteres onde a mensagem
  // JSON final será armazenada.
  char buffer[128];


  // Transforma o documento JSON em texto para
  // que possa ser enviado através do MQTT.
  serializeJson(doc, buffer);


  // Publica a mensagem no tópico MQTT padrão recebido pelo carrinho

  // Envia o JSON para exatamente o mesmo tópico
  // que o ESP32 do carrinho está monitorando.
  client.publish("carrinho/joystick", buffer);


  // Exibe no Monitor Serial a mensagem que foi enviada.
  Serial.print("Enviado payload JSON: ");

  Serial.println(buffer);


  // Intervalo de transmissão (50ms para boa responsividade nos comandos)

  // Aguarda 50 milissegundos antes de realizar
  // uma nova leitura e transmissão.
  //
  // Isso corresponde a aproximadamente 20 atualizações
  // de comando por segundo.
  delay(50);

)