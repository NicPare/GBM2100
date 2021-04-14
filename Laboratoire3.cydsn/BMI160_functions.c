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

#include "projet_headers.h"

/* Time Out */
#define I2CM_TIMEOUT        10 /* 10 msec */



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
    status = (unsigned int)_MasterWrite(&config);
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
    }
    else if((events & CY_SCB_I2C_MASTER_WR_CMPLT_EVENT)|| 
            (events & CY_SCB_I2C_MASTER_RD_CMPLT_EVENT))
    {
        xSemaphoreGiveFromISR(xSemaphoreI2C, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}


/* [] END OF FILE */
