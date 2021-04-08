/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ======================================= =
*/
#include <i2c.h>

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
void write_register_MAX(uint8_t baseAddress, uint8_t data)
{ 
    I2C_MAX_MasterSendStart(MAX_ADDR,CY_SCB_I2C_WRITE_XFER,100);
    I2C_MAX_MasterWriteByte(baseAddress,100);        
    I2C_MAX_MasterWriteByte(data,100);         
    I2C_MAX_MasterSendStop(100);   
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

//Lecture du bmi160

uint8 read_register_bmi160(uint8 baseAddress)
{
    I2C_bmi160_MasterSendStart(bmi160_ADDR,CY_SCB_I2C_WRITE_XFER,100);
    I2C_bmi160_MasterWriteByte(baseAddress,100);  
    I2C_bmi160_MasterSendReStart(bmi160_ADDR,CY_SCB_I2C_READ_XFER,100);
    uint8_t registerValueBMI=0;
    I2C_bmi160_MasterReadByte(CY_SCB_I2C_MASTER_DATA_NAK,(uint8_t*)&registerValueBMI,100);
    I2C_bmi160_MasterSendStop(100);  
    return registerValueBMI;
}
void write_register_bmi160(uint8_t baseAddress, uint8_t data)
{ 
    I2C_bmi160_MasterSendStart(bmi160_ADDR,CY_SCB_I2C_WRITE_XFER,100);
    I2C_bmi160_MasterWriteByte(baseAddress,100);        
    I2C_bmi160_MasterWriteByte(data,100);         
    I2C_bmi160_MasterSendStop(100);   
}
void readMultipleBytes_bmi160(uint8_t baseAddress, uint8_t *buffer, uint8_t length)
{
    I2C_bmi160_MasterSendStart(bmi160_ADDR,CY_SCB_I2C_WRITE_XFER,100); 
    I2C_bmi160_MasterWriteByte(baseAddress,100);       
    I2C_bmi160_MasterSendReStart(bmi160_ADDR,CY_SCB_I2C_READ_XFER,100);
    uint8_t idx = 0;
    for(idx=0 ; idx < length-1 ; idx++)
    { 
        I2C_bmi160_MasterReadByte(CY_SCB_I2C_ACK,(uint8_t*)&buffer[idx],100);  
    }
    I2C_bmi160_MasterReadByte(CY_SCB_I2C_NAK,(uint8_t*)&buffer[idx],100);
    I2C_bmi160_MasterSendStop(100); 
}




/* [] END OF FILE */
