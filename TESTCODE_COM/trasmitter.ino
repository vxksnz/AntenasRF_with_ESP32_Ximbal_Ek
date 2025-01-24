#define RXD1 18
#define TXD1 17

int V1, V2, V3;

void sendCmd(String cmd) {
  Serial1.println(cmd);
  unsigned long timeout = millis() + 2000;
  while (!Serial1.available() && millis() < timeout) {
    delay(10);
  }
}

void checkResponse(String expected, String errorMsg, bool showResponse = false) {
  String response = "";
  while (Serial1.available()) {
    response += char(Serial1.read());
    delay(10);
  }

  if (response.indexOf(expected) != -1) {
    Serial.println("OK");
  } else {
    Serial.println(errorMsg);
    if (showResponse) {
      Serial.println("Respuesta recibida: " + response);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
  Serial.println("Configurando parámetros antena LoRa");
  delay(1000);

  sendCmd("AT+ADDRESS=1");
  checkResponse("+OK", "ERROR_1");

  sendCmd("AT+NETWORKID=5");
  checkResponse("+OK", "ERROR_2");

  sendCmd("AT+BAND=462606250");
  checkResponse("+OK", "ERROR_3");

  sendCmd("AT+PARAMETER?");
  checkResponse("+OK", "ERROR_4", true);

  sendCmd("AT+MODE=0");
  checkResponse("+OK", "ERROR_5");
}

void loop() {
  V1 = random(-100, 100);
  V2 = random(0, 4000);
  V3 = random(1, 9);

  String data = String(V1) + "," + String(V2) + "," + String(V3);
  Serial.println("Enviando: " + data);
  sendCmd("AT+SEND=2," + String(data.length()) + "," + data);
  checkResponse("+OK", "ERROR_SEND");

  delay(5000);
}
