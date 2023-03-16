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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

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
	// Reset the MS5837, per datasheet
	// Wire.beginTransmission(MS5837_ADDR);
	// Wire.write(MS5837_RESET);
	// Wire.endTransmission();

	// Wait for reset to complete
    vTaskDelay(pdMS_TO_TICKS(10));

	fluidDensity = MS5837_SEAWATER_DENSITY;

    return 0;
}
