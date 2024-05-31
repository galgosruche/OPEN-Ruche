#include <MKRWAN.h>
//Luxmètre
#include <Wire.h>
//Capteur de poids
#include "HX711.h"
// Include the DHT22 library for interfacing with the sensor.
#include <DHT.h>
//One Wire temperature sensor
#include <OneWire.h>
//Temperature et humidité 
#include "DFRobot_SHT20.h"
// Plusieurs One Wire
#include <DallasTemperature.h>

// Paramètres du capteur HX711
#define DOUT  A2
#define CLK   A3

//Pin de la batterie
#define batteryPin A0 

HX711 scale;

#define ONE_WIRE_BUS 4

#define adresse_luxmetre 0x23 // Adresse I2C du capteur de lumière SEN0562
#define adresse_sen0227 0x40 // Adresse I2C du capteur de température et d'humidité SEN0227

LoRaModem modem;
float calibration_factor = 29711; // Ce paramètre doit être ajusté en fonction de votre capteur 28611

String appEui = "0102030405006000";
String appKey = "79679F8396218144071A2CBFBFFB6A6B";

// Create an instance of the DHT11 class.
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
DHT dht(2, DHT22);

bool connected;
int err_count;
short con; 
uint8_t buf[4] = {0};
uint16_t data_lux;
float Lux;

/**
 * Hardware Connections:
 * -VCC = 3.3V
 * -GND = GND
 * -SDA = A4 (use inline 330 ohm resistor if your board is 5V)
 * -SCL = A5 (use inline 330 ohm resistor if your board is 5V)
 */
DFRobot_SHT20 sht20(&Wire, adresse_sen0227);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Welcome to MKR WAN 1300/1310 ");
  modem.begin(EU868);
  delay(1000);
  connected = false;
  err_count = 0;
  con = 0;
  dht.begin();
  Wire.begin();
  // Init SHT20 Sensor
  sht20.initSHT20();
  delay(50);

  /**
   * Check the current status information of SHT20
   * Status information: End of battery, Heater enabled, Disable OTP reload
   * Check result: yes, no
   */
  sht20.checkSHT20();

  sensors.begin();
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); // Remettre le poids à zéro

  long zero_factor = scale.read_average(); // Obtenir le facteur de zéro utilisé pour le tare
}

void loop() {
  delay(2000);

  // Code LoRaWAN existant
  if (!connected) {
    Serial.print("Join test : ");
    Serial.println(++con);
    int ret = modem.joinOTAA(appEui, appKey);
    if (ret) {
      connected = true;
      modem.minPollInterval(60);
      Serial.println("Connected");
      modem.dataRate(5);   // switch to SF7
      delay(100);          // because ... more stable
      err_count = 0;
    }
  }

  if (connected) {
    int err = 0;

    byte i;
    byte data[9];
    byte addr[8];
    float t_1, t_2;

    //------------------------------------------------------------------DHT22-----------------------------------------------------------

    float t_0 = dht.readTemperature();
    delay(300);
    float h_i = dht.readHumidity();

    // -----------------------------------------------------------------Capteur poids-----------------------------------------------------------------------------
    if(Serial.available()) {
      char temp = Serial.read();
      if(temp == '+' ||  temp == 'a') {
        calibration_factor += 10;
        scale.set_scale(calibration_factor); // Ajuster à la nouvelle valeur de calibration
        Serial.print("Nouveau facteur de calibration: ");
        Serial.println(calibration_factor);
      } else if(temp == '-' || temp == 'z') {
        calibration_factor -= 10;
        scale.set_scale(calibration_factor); // Ajuster à la nouvelle valeur de calibration
        Serial.print("Nouveau facteur de calibration: ");
        Serial.println(calibration_factor);
      } else if(temp == 't') {
        scale.tare();  // Remettre le poids à zéro
        Serial.println("Tare complete");
      }
    }

    // Affiche le poids après tare ou ajustement du facteur de calibration
    scale.set_scale(calibration_factor);
    Serial.print("Lecture: ");
    float weight = scale.get_units(5); // Prend plusieurs mesures pour obtenir une moyenne, puis la convertit en unité de poids (ex. grammes)

    // -------------------------------------------------------------Capteur Luxmetre SEN0562 -------------------------------------------------------------------------
    //Read Lux
    readReg(0x10, buf, 2); //Register Address 0x10
    data_lux = buf[0] << 8 | buf[1];
    Lux = (((float)data_lux) / 1.2);

    delay(200);

    /**
    ---------------------------------------------------------------------CAPTEUR temperature humidité SEN0227---------------------------------------------------------------------
    * Read the measured data of air humidity
    * Return the measured air humidity data of float type, unit: %
    */
    float humd = sht20.readHumidity();


    delay(200);

    /**
    * Read the measured temp data
    * Return the measured temp data of float type, unit: C
    */
    float temp = sht20.readTemperature();

    delay(300);

    // --------------------------------------------------------One Wire ----------------------------------------------------------------------------------------------

    //Requetes successives de data
    sensors.requestTemperatures();

    //One Wire 1
    t_1 = sensors.getTempCByIndex(0);

    delay(200);

    //One Wire 2
    t_2 = sensors.getTempCByIndex(1);

    delay(200);

    //---------------------------------------------------------------------------------Battery -------------------------------------------------------------------------------------

    int valeur_mesuree = analogRead(batteryPin);          // Lire la valeur de la tension
    float voltage = valeur_mesuree * (3.3 / 1023.0);        // La valeur maximale de l'ADC est 1023
    float valeur_mesuree_adaptee = voltage - 2.72;          //Produit en croix en fonction de la croix
    float pourcentage = (valeur_mesuree_adaptee/0.58)*100;  //Pourcentage de batterie sur la plage 2.72 - 3.24

    //-----------------------------------------------------------------------------------PRINT--------------------------------------------------------------------------------------

    Serial.println("Temperature 0 DHT22 = " + String(t_0) + " °C");
    Serial.println("Humidite DHT22 = " + String(h_i) + " %");
    Serial.println("Temperature 1 OneWire1 = " + String(t_1) + " °C");
    Serial.println("Lux = " + String(Lux) + " lux");
    Serial.println("Température 2 SEN0227  : " + String(temp) + "°C");
    Serial.println("humidity SEN0227  : " + String(humd) + "%");
    Serial.println("Poids : " + String(weight) + " kg");
    Serial.print("Tension de la batterie : ");
    Serial.print(voltage);
    Serial.println(" volts");
    Serial.print("Pourcentage de la batterie : ");
    Serial.print(pourcentage);
    Serial.println(" %");

    /* ----------------------------------------------------------------------------Envoi paquet ----------------------------------------------------------------------------*/
    
    modem.beginPacket();
    modem.write((uint16_t)(h_i*100));                                  // h_i DHT22
    modem.write((uint16_t)(t_0*100));                                  // t_0 DHT22
    modem.write((uint16_t)(t_1*100));                                  // t_1 One wire 1
    modem.write((uint16_t)(t_2*100));                                  // t_2 One wire 2
    modem.write(data_lux);                                             // l SEN0652
    modem.write((uint16_t)(weight*100));                               // weight_kg HX711
    modem.write((uint16_t)(temp*100));                                 // t_ext SEN0227
    modem.write((uint16_t)(humd*100));                                 // h SEN0227
    modem.write((uint16_t)(pourcentage*100));                          //Batterie en pourcentage

    err = modem.endPacket();

    if (err <= 0) {
      Serial.print("Error : ");
      Serial.println(err);
      err_count++;
      if (err_count > 50) {
        connected = false;
      }
      for (int i = 0; i < 120; i++) {
        delay(1000);
      }
    } else {
      err_count = 0;
      delay(20000);
      Serial.println("Message envoyé");
    }
  }

  LowPower.sleep(3600000); // 1 heure de sommeil basse consommation
}

// Fonction de Comunication I2C pour luxmètre
uint8_t readReg(uint8_t reg, const void* pBuf, size_t size) {
  if (pBuf == NULL) {
    Serial.println("pBuf ERROR!! : null pointer");
  }
  uint8_t* _pBuf = (uint8_t*)pBuf;
  Wire.beginTransmission(adresse_luxmetre);
  Wire.write(&reg, 1);
  if (Wire.endTransmission() != 0) {
    return 0;
  }
  delay(20);
  Wire.requestFrom(adresse_luxmetre, (uint8_t)size);
  for (uint16_t i = 0; i < size; i++) {
    _pBuf[i] = Wire.read();
  }
  return size;
}
