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
#include "MAX30102_functions.h"

//Fonctions i2c
bool MAX_Init(void)
{
    if (!write_register_MAX(0x02, 0xc0))
        return false;
    if (!write_register_MAX(0x03, 0x00))
        return false;
    if (!write_register_MAX(0x04, 0x00))
        return false;
    if (!write_register_MAX(0x05, 0x00))
        return false;
    if (!write_register_MAX(0x06, 0x00))
        return false;
    if (!write_register_MAX(0x08, 0x0f))
        return false;
    if (!write_register_MAX(0x09, 0x03))
        return false;
    if (!write_register_MAX(0x0A, 0x6B))
        return false;
    if (!write_register_MAX(0x0C, 0x24))
        return false;
    if (!write_register_MAX(0x0D, 0x24))
        return false;
    if (!write_register_MAX(0x10, 0x7f))
        return false;
    return true;
}

bool MAX_Reset(void)
{
    if(!write_register_MAX(0x09, 0x40))
        return false;
    else
        return true;
}

uint8 read_register_MAX(uint8 baseAddress)
{
    I2C_MAX_MasterSendStart(MAX_ADDR,CY_SCB_I2C_WRITE_XFER,100);
    I2C_MAX_MasterWriteByte(baseAddress,100);  
    I2C_MAX_MasterSendReStart(MAX_ADDR,CY_SCB_I2C_READ_XFER,100);
    uint8_t registerValueMAX =0;
    I2C_MAX_MasterReadByte(CY_SCB_I2C_MASTER_DATA_NAK,(uint8_t*)&registerValueMAX,100);
    I2C_MAX_MasterSendStop(100);  
    return registerValueMAX;
}
bool write_register_MAX(uint8_t baseAddress, uint8_t data)
{ 
    I2C_MAX_MasterSendStart(MAX_ADDR,CY_SCB_I2C_WRITE_XFER,100);
    I2C_MAX_MasterWriteByte(baseAddress,100);        
    I2C_MAX_MasterWriteByte(data,100);         
    I2C_MAX_MasterSendStop(100);
    return true;
}
void readMultipleBytes_MAX(uint8_t baseAddress, uint8_t *buffer, uint8_t length)
{
    I2C_MAX_MasterSendStart(MAX_ADDR,CY_SCB_I2C_WRITE_XFER,100); 
    I2C_MAX_MasterWriteByte(baseAddress,100);       
    I2C_MAX_MasterSendReStart(MAX_ADDR,CY_SCB_I2C_READ_XFER,100);
    uint8_t idx = 0;
    for(idx=0 ; idx < length-1 ; idx++)
    { 
        I2C_MAX_MasterReadByte(CY_SCB_I2C_ACK,(uint8_t*)&buffer[idx],100);  
    }
    I2C_MAX_MasterReadByte(CY_SCB_I2C_NAK,(uint8_t*)&buffer[idx],100);
    I2C_MAX_MasterSendStop(100); 
}

//Définitions de paramètres

int read_idx_MAX = 0;
int write_idx_MAX = 0;
bool read_flag_MAX = false;
uint8_t buffer[6];

uint32 red_data[1000];
uint32 ir_data[1000];

//Fonction de lecture du capteur


void read_MAX30102_task(void* pvParameters)
{
    (void)pvParameters;
    for(;;)
    {
        readMultipleBytes_MAX(MAX_FIFO_ADDR, buffer, 6);
        red_data[write_idx_MAX] = (buffer[2] + (buffer[1]<<8) + (buffer[0]<<16));
        ir_data[write_idx_MAX] = (buffer[5] + (buffer[4]<<8) + (buffer[3]<<16));
        write_idx_MAX++;
        if (!(write_idx_MAX % 1000))
        {
            read_flag_MAX = true;
            write_idx_MAX = 0;
        }
        //vTaskDelay(pdMS_TO_TICKS(2));
    }
}

/* [] END OF FILE */
