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


#define MAX_ADDR        (0x57)
#define MAX_FIFO_ADDR   (0x07)

#include "project.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

float32 red_data[1000];
float32 ir_data[1000];
bool read_flag_MAX;
int write_idx_MAX;

//Fonctions i2c
uint8 read_register_MAX(uint8 baseAddress);

bool write_register_MAX(uint8_t baseAddress, uint8_t data);

void readMultipleBytes_MAX(uint8_t baseAddress, uint8_t *buffer, uint8_t length);


//Fonctions MAX
int received_data();

bool MAX_Init();

void read_MAX30102_task(void* pvParameters);

void MAX_data();

void PPG_RDY_handler();

/* [] END OF FILE */
