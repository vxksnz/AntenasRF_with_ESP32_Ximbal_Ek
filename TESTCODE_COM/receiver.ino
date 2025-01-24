#define RXD2 16
#define TXD2 17

int varInMsg = 7; 
int commasInMsg = varInMsg - 1; 
int keyPos[10];  


String msg;
String txId;
String dataLen;
String V1;
String V2;
String V3;
String rssi;
String snr;


void sendCmd(String cmd);
void checkResponse(String expected, String errorMsg, bool showResponse = false);
void processMessage(String message);

void setup() {
  Serial.begin(115200); 
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);  
  Serial.println("Configurando parámetros antena LoRa");
  delay(1000);

  sendCmd("AT+ADDRESS=2");  
  checkResponse("+OK", "ERROR_1");

  sendCmd("AT+NETWORKID=5");  
  checkResponse("+OK", "ERROR_2");

  sendCmd("AT+BAND=462606250"); 
  checkResponse("+OK", "ERROR_3");

  sendCmd("AT+PARAMETER?"); 
  checkResponse("+OK", "ERROR_4", true);

  sendCmd("AT+MODE=0");  
  checkResponse("+OK", "ERROR_5");

  Serial.println("Receptor configurado y listo para recibir mensajes");
}

void loop() {
  while (Serial2.available()) {
    msg = Serial2.readString();  
    msg.trim(); 

    if (msg.length() > 0) {
      processMessage(msg);
    }
  }
}

// Definición de la función sendCmd
void sendCmd(String cmd) {
  Serial2.println(cmd); 
  unsigned long timeout = millis() + 2000;
  while (!Serial2.available() && millis() < timeout) {
    delay(10);  
  }
}


void checkResponse(String expected, String errorMsg, bool showResponse) {
  String response = "";
  while (Serial2.available()) {
    response += char(Serial2.read());
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


void processMessage(String message) {
  for (int i = 1; i <= commasInMsg; i++) {
    keyPos[i] = message.indexOf(',', keyPos[i - 1] + 1);
  }

  txId = message.substring(5, keyPos[1]);
  dataLen = message.substring(keyPos[1] + 1, keyPos[2]);
  V1 = message.substring(keyPos[2] + 1, keyPos[3]);
  V2 = message.substring(keyPos[3] + 1, keyPos[4]);
  V3 = message.substring(keyPos[4] + 1, keyPos[5]);
  rssi = message.substring(keyPos[5] + 1, keyPos[6]);
  snr = message.substring(keyPos[6] + 1);

  Serial.println("Mensaje recibido: " + message);
  Serial.println("TxId: " + txId);
  Serial.println(" Length: " + dataLen);
  Serial.println(" V1: " + value1);
  Serial.println(" V2: " + value2);
  Serial.println(" V3: " + value3);
  Serial.println(" RSSI: " + rssi);
  Serial.println(" SNR: " + snr);

}
