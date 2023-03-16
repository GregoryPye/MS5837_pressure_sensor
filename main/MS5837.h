/**
 * @file MS5837.h
 *
 */

#ifndef MS5837_H
#define MS5837_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

#define MS5837_ADDR               0x76  
#define MS5837_RESET              0x1E
#define MS5837_ADC_READ           0x00
#define MS5837_PROM_READ          0xA0

// Pressure Conversion
#define MS5837_CONVERT_D1_256     0x40
#define MS5837_CONVERT_D1_512     0x42
#define MS5837_CONVERT_D1_1024    0x44
#define MS5837_CONVERT_D1_2048    0x46
#define MS5837_CONVERT_D1_4096    0x48
#define MS5837_CONVERT_D1_8192    0x4A

// Temperature Conversion
#define MS5837_CONVERT_D2_256     0x50
#define MS5837_CONVERT_D2_512     0x52
#define MS5837_CONVERT_D2_1024    0x54
#define MS5837_CONVERT_D2_2048    0x56
#define MS5837_CONVERT_D2_4096    0x58
#define MS5837_CONVERT_D2_8192    0x5A

#define MS5837_SEAWATER_DENSITY   1029.0
#define MS5837_FRESHWATER_DENSITY 997.0

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

class MS5837 {
public:

    //Constructor
	MS5837();

    /*
    * @brief Initialize MS5837 and set basic configurations
    * @details
    *  Init configuration:
    *  - Seawater density
    *
    * @note
    *  - A soft reset is performed first, which takes ~10ms.
    */
	bool initialize();

private:
	uint16_t C[8]; // Stores calibration data

    float fluidDensity;

    uint8_t crc4(uint16_t n_prom[]);
};

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // MS5837_H 
