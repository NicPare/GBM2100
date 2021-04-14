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



#define MAX_ADDR (0x57)
#define MAX_FIFO_ADDR (0x07)
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>



//Fonctions
bool MAX_init();

bool MAX_Reset(void);

uint8 read_register_MAX(uint8 baseAddress);

bool write_register_MAX(uint8_t baseAddress, uint8_t data);

void readMultipleBytes_MAX(uint8_t baseAddress, uint8_t *buffer, uint8_t length);

void read_MAX30102_task();




/* [] END OF FILE */
