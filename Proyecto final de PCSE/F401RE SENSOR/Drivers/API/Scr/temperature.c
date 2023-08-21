#include <dht22.h> // Include DHT22 header
#include <temperature.h>


float convertToCelsius(uint8_t tc1, uint8_t tc2) {
    if (tc1 > 127) {
        return (float)tc2 / 10 * (-1);
    } else {
        return (float)((tc1 << 8) | tc2) / 10;
    }
}

float convertToFahrenheit(float celsius) {
    return celsius * 9 / 5 + 32;
}

float calculateHumidity(uint8_t rh1, uint8_t rh2) {
    return (float)((rh1 << 8) | rh2) / 10;
}

uint8_t calculateChecksum(uint8_t rh1, uint8_t rh2, uint8_t tc1, uint8_t tc2) {
    return rh1 + rh2 + tc1 + tc2;
}



