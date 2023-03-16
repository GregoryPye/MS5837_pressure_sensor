/**
 * @file MS5837.cpp
 */

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "I2Cbus.hpp"

#include "esp_log.h"

#include "MS5837.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

static const char *TAG = "MS5837 lib";

MS5837::MS5837() 
{

}

bool MS5837::initialize() 
{
	fluidDensity = MS5837_SEAWATER_DENSITY;

    ESP_ERROR_CHECK(i2c0.writeByte(MS5837_ADDR,MS5837_RESET,0));

	// Wait for reset to complete
    vTaskDelay(pdMS_TO_TICKS(10));

    // Read calibration values and CRC
    uint8_t data[2];
	for ( uint8_t i = 0 ; i < 7 ; i++ ) {
        // ESP_ERROR_CHECK(i2c0.writeByte(MS5837_ADDR,MS5837_PROM_READ+i*2,0));
        // ESP_ERROR_CHECK(i2c0.readByte(MS5837_ADDR,MS5837_PROM_READ+i*2,0));
        
        ESP_ERROR_CHECK(i2c0.readBytes(MS5837_ADDR,MS5837_PROM_READ+i*2, 2, data));

		// Wire.requestFrom(MS5837_ADDR,2);
		// C[i] = (Wire.read() << 8) | Wire.read();
        C[i] = (data[0] << 8) | data[1];
	}

	// Check CRC
	uint8_t crcRead = C[0] >> 12;
	uint8_t crcCalculated = crc4(C);

	if ( crcCalculated == crcRead ) {
		return true; // Initialization success
	}

    ESP_LOGW(TAG, "MS5837 config CRC check failed");
	return false; // CRC fail
}

uint8_t MS5837::crc4(uint16_t n_prom[]) // n_prom defined as 8x unsigned int (n_prom[8])
{
    uint16_t n_rem=0; // crc remainder
    n_prom[0]=((n_prom[0]) & 0x0FFF); // CRC byte is replaced by 0
    n_prom[7]=0; // Subsidiary value, set to 0
    for (uint8_t i = 0; i < 16; i++) // operation is performed on bytes
    { // choose LSB or MSB
        if (i%2==1) {
            n_rem ^= (uint16_t) ((n_prom[i>>1]) & 0x00FF);
        }
        else {
            n_rem ^= (uint16_t) (n_prom[i>>1]>>8);
        }
        for (uint8_t n_bit = 8; n_bit > 0; n_bit--)
        {
            if (n_rem & (0x8000)) {
                n_rem = (n_rem << 1) ^ 0x3000;
            }
            else {
                n_rem = (n_rem << 1);
            }
        }
    }
    n_rem= ((n_rem >> 12) & 0x000F); // final 4-bit remainder is CRC code
    return (n_rem ^ 0x00);
}
