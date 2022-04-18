/*
 * 4 Probe Greenhouse Temp Monitor for thinger.io (ESP8266)
 * Board: Lolin(WEMOS) D1 Mini (clone)
 * Sensor: DS18B20
 * 
 * Temperature probe positions:
 *   Sensor1 - Outside
 *   Sensor2 - Water Tank
 *   Sensor3 - Upper
 *   Sensor4 - Lower
 *   
 *   Note temp sensor device addresses can be determined with OneWire library example (or the following code):

#include <OneWire.h>

OneWire ds(4);  //data wire connected to GPIO 4

void setup(void) {
  Serial.begin(115200);
}

void loop(void) {
  byte i;
  byte addr[8];
  
  if (!ds.search(addr)) {
    Serial.println(" No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
  Serial.print(" ROM =");
  for (i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }
}
 */
 
#include <ThingerESP8266.h>
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//thinger.io config
#define USERNAME "username"
#define DEVICE_ID "deviceid"
#define DEVICE_CREDENTIAL "credential"
#define EMAIL_ENDPOINT "endpointid"

//WiFi Config
#define SSID "ssidname"
#define SSID_PASSWORD "password"

// Data wire is plugged into port D2 on the ESP8266
#define ONE_WIRE_BUS D4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//double
float tempSensor1, tempSensor2, tempSensor3, tempSensor4; 
float T1, T2, T3, T4;

uint8_t sensor1[8] = { 0x28, 0xC1, 0x19, 0x49, 0xF6, 0x2B, 0x3C, 0xE9 };
uint8_t sensor2[8] = { 0x28, 0x1, 0xEA, 0x49, 0xF6, 0x35, 0x3C, 0xAE };
uint8_t sensor3[8] = { 0x28, 0xEE, 0x3B, 0x49, 0xF6, 0x68, 0x3C, 0xCE };
uint8_t sensor4[8] = { 0x28, 0xF3, 0x4D, 0x49, 0xF6, 0x33, 0x3C, 0x7A };

// Setup for thinger.io
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(115200);
  thing.add_wifi(SSID, SSID_PASSWORD);
  Serial.println("");
  Serial.println("REBOOT");
  //delay(100);

  //Initialize sensors
  sensors.begin();              
}

void loop() {

  Serial.println();
  Serial.print("Reading temperature from sensors: ");
  
  sensors.requestTemperatures();
  
  tempSensor1 = sensors.getTempC(sensor1); // Gets the values of the temperature
  tempSensor2 = sensors.getTempC(sensor2); // Gets the values of the temperature
  tempSensor3 = sensors.getTempC(sensor3); // Gets the values of the temperature
  tempSensor4 = sensors.getTempC(sensor4); // Gets the values of the temperature

  T1 = (9.0/5.0)*tempSensor1+32.0;
  T2 = (9.0/5.0)*tempSensor2+32.0;
  T3 = (9.0/5.0)*tempSensor3+32.0;
  T4 = (9.0/5.0)*tempSensor4+32.0;
  
  thing["data"] >> [](pson& out){
    //out["Outside"] = roundf(T1*100.0)/100.0;
    out["Outside"] = T1;
    out["Water"] = T2;
    out["Upper"] = T3;
    out["Lower"] = T4;
  };
  
  Serial.print("Sending [ Outside: ");
  Serial.print(T1);
  Serial.print(" F, ");
  Serial.print("Water: ");
  Serial.print(T2);
  Serial.print(" F, ");
  Serial.print("Upper: ");
  Serial.print(T3);
  Serial.print(" F, ");
  Serial.print("Lower: ");
  Serial.print(T4);
  Serial.print(" F] to thinger.io...");
  Serial.print('\n');
  Serial.print("=====");

  thing.handle();
  thing.stream(thing["data"]);

  delay(60000);  // Pause for 1 min.
//  delay(15000);  // Pause for 15 sec.
}
