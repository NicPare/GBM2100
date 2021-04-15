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

void bmi_init()
{
    
}
//Fonctions i2c

void write_register_bmi160(uint8_t baseAddress, uint8_t data)
{ 
    I2C_bmi160_MasterSendStart(bmi160_ADDR,CY_SCB_I2C_WRITE_XFER,100);
    I2C_bmi160_MasterWriteByte(baseAddress,100);        
    I2C_bmi160_MasterWriteByte(data,100);         
    I2C_bmi160_MasterSendStop(100);   
}
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


//Définition de paramètres

int read_idx_bmi = 0;
int write_idx_bmi = 0;
bool read_flag_bmi = false;

uint16_t buffer_x[250];
uint16_t buffer_y[250];
uint16_t buffer_z[250];

//Fonction de lecture du bmi160

void read_bmi160()
{
    for(;;)
    {
        buffer_x[write_idx_bmi] = (read_register_bmi160(ACC_X2_ADDR) << 8) + read_register_bmi160(ACC_X1_ADDR);
        buffer_y[write_idx_bmi] = (read_register_bmi160(ACC_Y2_ADDR) << 8) + read_register_bmi160(ACC_Y1_ADDR);
        buffer_z[write_idx_bmi] = (read_register_bmi160(ACC_Z2_ADDR) << 8) + read_register_bmi160(ACC_Z1_ADDR);
        
        write_idx_bmi++;
        if (!(write_idx_bmi % 250))
        {
            read_flag_bmi = true;
            write_idx_bmi = 0;
        }
    }
}

/* [] END OF FILE */
