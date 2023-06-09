/*
 * proximity_sensor.c
 * Hardware Device: VCNL4010
 *
 *  Created on: May 2, 2022
 *      Author: Pascal
 *   Edited on: 09 June 2023
 *      Author: Boris Ivanov
 */

#include "level_3/proximity_sensor.h"

/**
 * @brief Initialise the VCNL4010 sensor.
 *
 * This function initialises the VCNL4010 sensor with the specified configuration.
 * It sets the LED current and communication enable values, and performs the necessary
 * I2C communications to configure the sensor.
 *
 * @param self: Pointer to the VCNL4010 sensor instance.
 */
void VCNL4010_Init(const VCNL4010 *const self)
{
    uint8_t led_ma = 0x0A;
    uint8_t com_en = 0x03;   // Communication enable value
    HAL_StatusTypeDef retFunc;

    retFunc = i2c_CheckDev(self->handle, self->dev_addr);   // Check if the sensor is available on the I2C bus

    if (retFunc == HAL_OK)
    {
        i2c_Transmit(self->handle, self->dev_addr, VCNL4010_LED_REG, 1, &led_ma, 1);   // Set the LED
        i2c_Transmit(self->handle, self->dev_addr, VCNL4010_COM_REG, 1, &com_en, 1);   // Set the communication enable
        HAL_Delay(1);   // Delay to allow the sensor to initialise
    }
    else
    {
        // Handle the case when the sensor is not available
    }
}


uint16_t VCNL4010_ReceiveProxy(const VCNL4010 *const self)
/**
 * @brief Receive the proxy value from the VCNL4010 sensor.
 *
 * This function reads the proxy value from the VCNL4010 sensor using the I2C communication.
 * The received value is returned as a 16-bit unsigned integer.
 *
 * @param1 self: Pointer to the VCNL4010 structure.
 *
 * @return The received proxy value.
 */
{
    uint8_t buf[2];                            // Buffer to store received data
    uint16_t val = 0;                          // Variable to store the received proxy value
    HAL_StatusTypeDef retFunc;                 // Return status of the I2C receive function

    retFunc = i2c_Receive(self->handle,        // I2C bus handle
                          self->dev_addr,      // Device address
                          VCNL4010_PROXY_REG,  // Register address
                          1,                   // Register address size
                          buf,                 // Buffer to store received data
                          sizeof(buf));        // Size of the buffer

    if (retFunc != HAL_OK)
    {
        val = 0;                               // If I2C receive function fails, set the value to 0
    }
    else
    {
        val = ((uint16_t) buf[0] << 8) | buf[1]; // Convert the received data to a 16-bit value
    }

    return val;                                // Return the received proxy value
}

VCNL4010 VCNL4010_Create(uint8_t dev_addr, I2C_HandleTypeDef *handle)
/**
 * @brief Create a VCNL4010 sensor instance.
 *
 * This function creates a VCNL4010 sensor instance with the specified device address and
 * I2C handle. It initializes the `VCNL4010` structure and returns the created instance.
 *
 * @param1 dev_addr: Device address of the VCNL4010 sensor.
 * @param2 handle: Pointer to the I2C handle used for communication.
 *
 * @return The created VCNL4010 sensor instance.
 */
{
    VCNL4010 create = {dev_addr, handle};     // Create a VCNL4010 instance with the given parameters
    return create;                           // Return the created VCNL4010 instance
}
