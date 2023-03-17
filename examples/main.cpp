

/**
 *
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
#include <driver/i2c.h>
#include "I2Cbus.hpp"
#include "esp_err.h"

#include "esp_log.h"

#include "MS5837.h"

/*********************
 *      DEFINES
 *********************/

// Sensors I2C bus
#define I2C_SDA         (gpio_num_t)21
#define I2C_SCL         (gpio_num_t)22
#define I2C_FREQ        100000
#define I2C_PORT        I2C_NUM_0

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

static const char *TAG = "MS5837 main";

void MS5837_harness(void *pvParameter)
{
    
    MS5837 MS5837;  // create a default object

    // Initialize I2C on port 0 using I2Cbus interface
    i2c0.begin(I2C_SDA, I2C_SCL, I2C_FREQ);

    ESP_LOGI(TAG, "i2c initialised");

    if (!MS5837.initialize()) {
        ESP_LOGW(TAG, "MS5837 initialisation failed");
    } else {
        ESP_LOGI(TAG, "MS5837 initialisation passed");
    }

    // Check the pressure sensor model
    // Note at least one device returned no ID, so mis-characterised as 02BA
    if (MS5837.getModel() != MS5837_30BA)
    {
        ESP_LOGI(TAG, "Current MS5837 model unexpected.  Setting to version 30BA");
        MS5837.setModel(MS5837_30BA);
    }

    ESP_LOGI(TAG, "Current sea level air pressure set to %4.2f",MS5837.getSeaLevelAirPressure());

    while(1) {
        MS5837.read();
        ESP_LOGI(TAG, "Pressure %5.4f , temp %2.4f ",MS5837.pressure(), MS5837.temperature());
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

extern "C" void app_main(void)
{
    xTaskCreatePinnedToCore(MS5837_harness, "harness", 4096*2, NULL, 1, NULL, 1);
}
