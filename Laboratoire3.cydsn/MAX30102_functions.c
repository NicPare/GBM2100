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
#include "project.h"
#include "MAX30102_functions.h"
#define MAX_ADDR (0x57)
#define MAX_FIFO_ADDR (0x07)
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>


//Définitions de paramètres

uint8 read_idx_MAX = 0;
uint8 write_idx_MAX = 0;
bool read_flag_MAX = false;
uint8_t buffer[6];

float32 red_data[1000];
float32 ir_data[1000];


bool MAX_init()

{
    if (!write_register_MAX(0x02, 0xc0)) // INTR setting
        return false;
    if (!write_register_MAX(0x03, 0x00))
        return false;
    if (!write_register_MAX(0x04, 0x00)) //FIFO_WR_PTR[4:0]
        return false;
    if (!write_register_MAX(0x05, 0x00)) //OVF_COUNTER[4:0]
        return false;
    if (!write_register_MAX(0x06, 0x00)) //FIFO_RD_PTR[4:0]
        return false;
    if (!write_register_MAX(0x08, 0x0f)) //sample avg = 1, fifo rollover=false, fifo almost full = 17
        return false;
    if (!write_register_MAX(0x09, 0x03)) //0x02 for Red only, 0x03 for SpO2 mode 0x07 multimode LED
        return false;
    if (!write_register_MAX(0x0A, 0x6B)) // SPO2_ADC range = 4096nA, SPO2 sample rate (200 Hz), LED pulseWidth (411uS)
        return false;
    if (!write_register_MAX(0X0C, 0x24)) //Choose value for ~ 7mA for LED1
        return false;
    if (!write_register_MAX(0X0D, 0x24)) // Choose value for ~ 7mA for LED2
        return false;
    if (!write_register_MAX(0x10, 0x7f)) // Choose value for ~ 25mA for Pilot LED
        return false;
    return true;

}

bool MAX_Reset(void)
{
    if (!write_register_MAX(0x09, 0x40))
        return false;
    else
        return true;
}


//Fonction de lecture du capteur


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
    uint8 idx = 0;
    for(idx=0 ; idx < length-1 ; idx++)
    { 
        I2C_MAX_MasterReadByte(CY_SCB_I2C_ACK,(uint8_t*)&buffer[idx],100);  
    }
    I2C_MAX_MasterReadByte(CY_SCB_I2C_NAK,(uint8_t*)&buffer[idx],100);
    I2C_MAX_MasterSendStop(100); 
}


void read_MAX30102_task()
{
 
    for(;;)
    {
        readMultipleBytes_MAX(MAX_FIFO_ADDR,  buffer, 6);
        red_data[read_idx_MAX] = (float32)(buffer[0] + (buffer[1]<<8) + (buffer[2]<<16));
        //red_data[read_idx_MAX]&=0x03FFFF;
        ir_data[read_idx_MAX] = (float32)(buffer[3] + (buffer[4]<<8) + (buffer[5]<<16));
        //ir_data[read_idx_MAX]&=0x03FFFF;
        read_idx_MAX++;
        if (!(read_idx_MAX % 1000))
        {
            read_flag_MAX = true;
            read_idx_MAX = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
       
    }
}

//Fonction de séparations des bytes rouges et infrarouges


/* [] END OF FILE */
