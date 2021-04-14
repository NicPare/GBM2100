/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/* Include Guard */
#ifndef I2CM_SUPPORT_H
#define I2CM_SUPPORT_H

/* Header file included */
#include "project.h"
#include "FreeRTOS.h"
#include "semphr.h"

/* Semaphore handle for I2C */
extern SemaphoreHandle_t xSemaphoreI2C;   
    
/* Function Prototype */
unsigned int I2C_ReadBytes(uint8_t Address, uint8_t RegisterAddr, 
                            uint8_t *RegisterValue, uint8_t RegisterLen);
unsigned int I2C_WriteBytes(uint8_t Address, uint8_t RegisterAddr,
                            uint8_t *RegisterValue, uint8_t RegisterLen);
void I2C_Callback(uint32_t events);

#endif /* I2CM_SUPPORT_H */



/* [] END OF FILE */
