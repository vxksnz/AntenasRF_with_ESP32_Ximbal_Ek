# AntenasRF_with_ESP32_Ximbal_Ek


## LoRa Communication Test Code

This is a test code for the LoRa module (REYAX RYLR498), on an ESP32 platform, for communication between the rocket and the ground station. DISCLAIMER: This is just a series of test codes, it is not a final code.

---

## Transmitter Code 

The transmitter is responsible for sending data to the receiver using the LoRa module. It generates random data and sends it in a specific format. ***The rocket in this case***

### Setup
1. Connect the LoRa module to the ESP32:
   - **RXD1**: GPIO 18 (connected to the TX pin of the LoRa module)
   - **TXD1**: GPIO 17 (connected to the RX pin of the LoRa module)
2. Monitor the output via Serial Monitor at 115200 baud rate.

### Key Configuration Commands
- `AT+ADDRESS=1`: Sets the LoRa address to `1`.
- `AT+NETWORKID=5`: Sets the network ID to `5`.
- `AT+BAND=462606250`: Sets the frequency band. -*Free frequency in Mexico*-
- `AT+MODE=0`: Configures the module as a transceiver.

### Output Format
The transmitted message is a string containing:
```
v1,v2,v3
```
Where `v1`, `v2`, and `v3` are random numbers for testing.

---

## Receiver Code

The receiver listens to the messages sent by the transmitter and processes them, this would be used to communicate the rocket with the ground station. It extracts values ​​from the message and prints them on the Serial Monitor.

### Setup
1. Connect the LoRa module to the ESP32:
   - **RXD2**: GPIO 16 (connected to the TX pin of the LoRa module)
   - **TXD2**: GPIO 17 (connected to the RX pin of the LoRa module)
2. Monitor the output via Serial Monitor at 115200 baud rate.

### Key Configuration Commands
- `AT+ADDRESS=2`: Sets the LoRa address to `2`.
- `AT+NETWORKID=5`: Sets the network ID to `5`.
- `AT+BAND=462606250`: Sets the frequency band. -*Free frequency in Mexico*-
- `AT+MODE=0`: Configures the module as a transceiver.

### Expected Output
When a message is received, the following details are printed to the Serial Monitor:
- `Id`: Transmitter ID.
- `Length`: Message length.
- `V1`: First variable.
- `V2`: Second variable.
- `V3`: Third variable.
- `RSSI`: Received Signal Strength Indicator.
- `SNR`: Signal-to-Noise Ratio.

---

**NOTA: ESTO LO REDACTE YO PERO ME DIO HUEVA TRADUCIRLO POR COMPLETO JAJA, GRACIAS DEEPL**
