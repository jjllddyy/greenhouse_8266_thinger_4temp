# greenhouse_8266_thinger_4temp
4 Probe DS18B20 temp monitor for thinger.io

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
 *   Data is sent to thinger.io and stored in bucket configured with device resource defined in code.
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
 
