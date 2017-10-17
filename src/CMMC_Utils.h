#ifndef CMMC_Utils_H
#define CMMC_Utils_H

#include <Arduino.h>
#include "ESP8266WiFi.h"
#include <functional>

#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif

class CMMC_Utils
{
public:
    // constructure
    CMMC_Utils() {}
    ~CMMC_Utils() {}

    void printMacAddress(uint8_t* macaddr) {
      Serial.print("{");
      for (int i = 0; i < 6; i++) {
        Serial.print("0x");
        Serial.print(macaddr[i], HEX);
        if (i < 5) Serial.print(',');
      }
      Serial.println("};");
    }

    void dump(const u8* data, size_t size) {
      for (size_t i = 0; i < size - 1; i++) {
        Serial.printf("%02x ", data[i]);
      }
      Serial.printf("%02x", data[size - 1]);
      Serial.println();
    }

    void convertMacStringToUint8(const char* mac_str, uint8_t* target) {
      String macStr = String(mac_str);
      for (size_t i = 0; i < 12; i += 2) {
        String mac = macStr.substring(i, i + 2);
        byte b = strtoul(mac.c_str(), 0, 16);
        target[i / 2] = b;
      }
    }

     void macByteToString(const u8* data, char *target) {
       bzero(target, 13);
       sprintf(target, "%02x%02x%02x%02x%02x%02x", data[0], data[1], data[2], data[3], data[4], data[5]);
     }

     uint8_t* getESPNowControllerMacAddress() {
       wifi_get_macaddr(STATION_IF, _controller_macaddr);
       return this->_controller_macaddr;
     }

   private:
       uint8_t _controller_macaddr[6];
};

#endif //CMMC_Utils_H
