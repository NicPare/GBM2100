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


/*******************************************************************************
* Function Name: bool MAX_Init(void)
********************************************************************************
*
* Summary:  
* Elle initialise la communication du capteur MAX30102 en écrivant les paramètres dans les registres appropriés. 
* Si la communication est fonctionnelle, la fonction retourne une valeur 	 
* booléenne positive.
*
* Parameters:
*  None
*
* Return:
*  bool (true / false)
*
*******************************************************************************/

bool MAX_Init(void)
{

    if (!write_register_MAX(0x09, 0x40))
        return false;
    vTaskDelay(pdMS_TO_TICKS(100));
    if (!write_register_MAX(0x09, 0x03))
        return false;
    if (!write_register_MAX(0x0A, 0x27))
        return false;
    if (!write_register_MAX(0x02, 0x40))
        return false;
    if (!write_register_MAX(0x03, 0x00))
        return false;
    if (!write_register_MAX(0x0C, 0x1F))
        return false;
    if (!write_register_MAX(0x0D, 0x1F))
        return false;
    
    Cy_SysInt_Init(&PPG_RDY_isr_cfg, PPG_RDY_handler);
    NVIC_ClearPendingIRQ(PPG_RDY_isr_cfg.intrSrc);
    NVIC_EnableIRQ(PPG_RDY_isr_cfg.intrSrc);
    
    
    return true;
}



/*******************************************************************************
* Function Name: int received_data(void) ********************************************************************************
*
* Summary:  
* La fonction lit la valeur du registre 0x00, pour s’assurer que la lecture des données est prête à être réalisée.
*
* Parameters:
* None
*
* Return:
*  (read_register_MAX(0x00) & 0x040) : Valeur du registre 0x00 avec un bitmask isolant le 7e bit.
*
*******************************************************************************/

int received_data()
{
    return (read_register_MAX(0x00) & 0x040);
}



/*******************************************************************************
* Function Name: uint8 read_register_MAX(uint8 baseAddress) 
********************************************************************************
*
* Summary:  
* La fonction lit un registre particulier et retourne la valeur de la byte d’information que contient ce 	 
* registre.
*
* Parameters:
* uint8 baseAddress : Adresse du registre où la fonction lit les données.
*
* Return:
*  uint8 registerValueMAX : Byte d’information contenu dans le registre baseAddress.
*
*******************************************************************************/

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



/*******************************************************************************
* Function Name: bool write_register_MAX(uint8 baseAddress, uint8_t data) ********************************************************************************
*
* Summary:  
* La fonction écrit une byte de donnée dans un registre particulier.
*
* Parameters:
* uint8 baseAddress : Adresse du registre où la fonction écrit les données.
* uint8_t data : Byte d’information à écrire dans le registre.
*
* Return:
*  true
*
*******************************************************************************/

bool write_register_MAX(uint8_t baseAddress, uint8_t data)
{ 
    I2C_MAX_MasterSendStart(MAX_ADDR,CY_SCB_I2C_WRITE_XFER,100);
    I2C_MAX_MasterWriteByte(baseAddress,100);        
    I2C_MAX_MasterWriteByte(data,100);         
    I2C_MAX_MasterSendStop(100);  
    
    return true;
}



/*******************************************************************************
* Function Name: void readMultipleBytes_MAX(uint8_t baseAddress, uint8_t *buffer, uint8_t length)
********************************************************************************
*
* Summary:  
* Cette tâche effectue la lecture de plusieurs bytes d’information par communication I2C en les stockant 
* dans un buffer d’une taille de bytes déterminée.
*
* Parameters:
*  uint8_t baseAddress : Adresse du registre où la fonction lit les données.
* uint8_t *buffer : Pointeur vers le buffer circulaire où les données sont stockées.
* uint8_t length : Longueur (en bytes) du buffer.
*
* Return:
*  None
*
*******************************************************************************/

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




/*******************************************************************************
* Function Name: void read_MAX30102_task(void* pvParameters)
********************************************************************************
*
* Summary:  
* Cette tâche initialise la lecture des données du capteur MAX30102 en démarrant le module I2C 
* et en appelant la fonction MAX_Init pour activer l'interrupt.
*
* Parameters:
* None
*
* Return:
* None
*
*******************************************************************************/

void read_MAX30102_task(void* pvParameters)
{
    (void)pvParameters;
    I2C_MAX_Start();
    
    
    //UART_Start();
    MAX_Init();
    
    read_flag_MAX = false;
    write_idx_MAX = 0;
    received_data();
    
    NVIC_EnableIRQ(PPG_RDY_isr_cfg.intrSrc);
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}



/*******************************************************************************
* Function Name: void MAX_data(void)
********************************************************************************
*
* Summary:  
* Copie de la routine de lecture effectuée dans l'interruption PPG_RDY.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void MAX_data()
{

    uint8 buffer[6];
    
    int temp;
    readMultipleBytes_MAX(MAX_FIFO_ADDR, buffer, 6);

    temp = buffer[0];
    temp = (temp << 8) + buffer[1];
    temp = (temp << 8) + buffer[2];
    red_data[write_idx_MAX] = (float32)temp;
    
    temp = buffer[3];
    temp = (temp << 8) + buffer[4];
    temp = (temp << 8) + buffer[5];
    ir_data[write_idx_MAX] = (float32)temp;    
    
    write_idx_MAX++;
    
    Cy_GPIO_ClearInterrupt(PPG_pin_0_PORT,PPG_pin_0_NUM);
    NVIC_ClearPendingIRQ(PPG_RDY_isr_cfg.intrSrc);
}



/*******************************************************************************
* Function Name: void PPG_RDY_handler(void)
********************************************************************************
*
* Summary:  
* Cette fonction réagit à l'interruption PPG_RDY et, à partir de la fonction readMultipleBytes_Max(), 
* insère les données de lumière rouge et de lumière infrarouge dans un buffer de six bytes. 
* Une variable temporaire prend ensuite la valeur de chacun des bytes du buffer.
* La fonction vérifie ensuite si l’indice d’écriture atteint la fin de sa période. Une fois  
* que le nombre d’échantillonnage est atteint, un flag est levé pour signaler la fin de l’écriture dans les 	 
* registres et l’indice compteur est remis à zéro. 
*
* Parameters:
* None
*
* Return:
* None
*
*******************************************************************************/

void PPG_RDY_handler(void)
{

    
    uint8 buffer[6];

    int temp;
    readMultipleBytes_MAX(MAX_FIFO_ADDR, buffer, 6);

    temp = buffer[0];
    temp = (temp << 8) + buffer[1];
    temp = (temp << 8) + buffer[2];
    red_data[write_idx_MAX] = (float32)temp;
    
    //Routine de test d'acquisition
    /*char displayStr[50];
    sprintf(displayStr,"%i,",temp);
    UART_PutString(displayStr);*/

    
    temp = buffer[3];
    temp = (temp << 8) + buffer[4];
    temp = (temp << 8) + buffer[5];
    ir_data[write_idx_MAX] = (float32)temp;    
    
    write_idx_MAX++;
    


    
    if (!(write_idx_MAX % 1000))
            {
                //UART_PutString("-----------------------------------------------\n\r");
                read_flag_MAX = true;
                write_idx_MAX = 0;
                NVIC_DisableIRQ(PPG_RDY_isr_cfg.intrSrc);

                   
            }  
    
  
    Cy_GPIO_ClearInterrupt(PPG_pin_0_PORT,PPG_pin_0_NUM);
    NVIC_ClearPendingIRQ(PPG_RDY_isr_cfg.intrSrc);
}

    


//END OF FILE
