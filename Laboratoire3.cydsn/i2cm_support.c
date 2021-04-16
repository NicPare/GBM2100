/*******************************************************************************
* File Name: i2cm_support.c
*
* Version 1.0
*
* Description: This file contains the functions for I2C read and write 
               operations for interfacing with the BMI160 motion sensor.
* 
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/

/* Header files include */ 
#include "i2cm_support.h"

#define I2C_BUFFER_SIZE (10u)

/* Semaphore handle */
SemaphoreHandle_t xSemaphoreI2C;

/*******************************************************************************
* Function Name: I2C_WriteBytes()
********************************************************************************
* Summary:
*  Function that writes data to an I2C slave device 
*
* Parameters:
*  unsigned char Address        - I2C slave address
*  unsigned char RegisterAddr   - register address to select gyro, accelerometer
*                                 data
*  unsigned char *RegisterValue - pointer to data to be written to I2C slave
*  unsigned char  RegisterLen   - length of sensor data in bytes
* Return:
*  unsigned long status - status of I2C write operation
*
*******************************************************************************/
unsigned int I2C_WriteBytes(uint8_t Address, uint8_t RegisterAddr, uint8_t *RegisterValue, uint8_t RegisterLen)
{
    /* Variable used for status of I2C operation */
    unsigned int status;
    
    /* Temporary buffer used for I2C transfer */ 
    static uint8_t tempBuff[I2C_BUFFER_SIZE];
    tempBuff[0] = RegisterAddr;
    memcpy(tempBuff+1, RegisterValue, RegisterLen);

    /* Local variables for storing I2C Master transfer configuration structure */
    cy_stc_scb_i2c_master_xfer_config_t config = 
    {  
        .slaveAddress = (uint32)Address,
        .buffer =  tempBuff,
        .bufferSize = RegisterLen+1,
        .xferPending = false
    };
    
    /* Start I2C write and take the semaphore */
    status = (unsigned int)I2Cm_MasterWrite(&config);
    xSemaphoreTake(xSemaphoreI2C, portMAX_DELAY);
        
    return status;
}

/*******************************************************************************
* Function Name: I2C_ReadBytes()
********************************************************************************
* Summary:
*  Function that reads data from an I2C slave device 
*
* Parameters:
*  unsigned char Address        - I2C slave address
*  unsigned char RegisterAddr   - register address to select gyro, accelerometer
*                                 data
*  unsigned char *RegisterValue - pointer to sensor data
*  unsigned char  RegisterLen   - length of sensor data in bytes
* Return:
*  unsigned long status - status of I2C write operation
*
*******************************************************************************/ 
unsigned int I2C_ReadBytes(uint8_t Address, uint8_t RegisterAddr, uint8_t *RegisterValue, uint8_t RegisterLen)
{
    /* Variable used for status of I2C operation */
    static unsigned int status;
    
    /* Local variables for storing I2C Master transfer configuration structure */
    cy_stc_scb_i2c_master_xfer_config_t config;
    
    config.slaveAddress = (uint32)Address;
    config.buffer       = &RegisterAddr;
    config.bufferSize   = 1;
    config.xferPending  = true;
    
    /* Start I2C write and take the semaphore */
    status = (unsigned int)I2Cm_MasterWrite(&config);
    xSemaphoreTake(xSemaphoreI2C, portMAX_DELAY);
    
    if(status == CY_SCB_I2C_SUCCESS)
    {
        config.slaveAddress = (uint32)Address;
        config.buffer =  RegisterValue;
        config.bufferSize = RegisterLen;
        config.xferPending = false;
        
        /* Start I2C read and take the semaphore */
        status = (unsigned int)I2Cm_MasterRead(&config);
        xSemaphoreTake(xSemaphoreI2C, portMAX_DELAY);
    }
    return status;
}

/*******************************************************************************
* Function Name: void I2C_Callback(uint32_t events)
********************************************************************************
*
* Summary:
*  Call back event function to handle interrupts from I2C
*
* Parameters:
*  uint32_t events: 
*   CY_SCB_I2C_MASTER_WR_IN_FIFO_EVENT - unused
*   CY_SCB_I2C_MASTER_WR_CMPLT_EVENT - I2C maser write completed
*   CY_SCB_I2C_MASTER_RD_CMPLT_EVENT - I2C master read completed
*   CY_SCB_I2C_MASTER_ERR_EVENT - I2C hardware error detected
*
* Return:
*  None
*
*******************************************************************************/
void I2C_Callback(uint32_t events)
{
    BaseType_t xHigherPriorityTaskWoken;
    /**
     * Unblock the task by releasing the semaphore only if no hardware error is 
     * detected and I2C master read or write is completed
     */
    if(events & CY_SCB_I2C_MASTER_ERR_EVENT)
    {
        CY_ASSERT(0u); /* Halt CPU */
    }
    else if((events & CY_SCB_I2C_MASTER_WR_CMPLT_EVENT)|| 
            (events & CY_SCB_I2C_MASTER_RD_CMPLT_EVENT))
    {
        xSemaphoreGiveFromISR(xSemaphoreI2C, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

/* [] END OF FILE */