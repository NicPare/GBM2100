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
    if (!write_register_MAX(0x09, 0x40))
        return false;
    if (!write_register_MAX(0x09, 0x03))
        return false;
    if (!write_register_MAX(0x0A, 0x67))
        return false;
    if (!write_register_MAX(0x02, 0xE0))
        return false;
    if (!write_register_MAX(0x0C, 0x30))
        return false;
    if (!write_register_MAX(0x0D, 0x30))
        return false;
    
    Cy_SysInt_Init(&PPG_RDY_isr_cfg, PPG_RDY_handler);
    NVIC_ClearPendingIRQ(PPG_RDY_isr_cfg.intrSrc);
    NVIC_EnableIRQ(PPG_RDY_isr_cfg.intrSrc);
    
    
    return true;
}



int received_data()
{
    return (read_register_MAX(0x00) & 0x040);
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




//uint32 red_data[1000];
//uint32 ir_data[1000];

//Fonction de lecture du capteur
float32 LED1, LED2;


void read_MAX30102_task(void* pvParameters)
{
    (void)pvParameters;
    I2C_MAX_Start();

    
    MAX_Init();
    
    read_flag_MAX = false;
    write_idx_MAX = 0;
    received_data();
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void MAX_data()
{

            uint8 buffer[6];
    
            int temp;
            readMultipleBytes_MAX(MAX_FIFO_ADDR, buffer, 6);
        
            temp = buffer[0];
            temp = (temp << 8) + buffer[1];
            temp = (temp << 8) + buffer[2];
            ir_data[write_idx_MAX] = (float32)temp;
            
            
            temp = buffer[3];
            temp = (temp << 8) + buffer[4];
            temp = (temp << 8) + buffer[5];
            red_data[write_idx_MAX] = (float32)temp;    
            
            write_idx_MAX++;


}



void PPG_RDY_handler(void)
{
    //Cy_GPIO_ClearInterrupt(P13_7_PORT, P13_7_NUM);
    //NVIC_ClearPendingIRQ(PPG_RDY_isr_cfg.intrSrc);
    //received_data();
    MAX_data();
    
 
    if (!(write_idx_MAX % 1000))
            {
                read_flag_MAX = true;
                write_idx_MAX = 0;
                NVIC_DisableIRQ(PPG_RDY_isr_cfg.intrSrc);
            }  
    

}

    


//END OF FILE
