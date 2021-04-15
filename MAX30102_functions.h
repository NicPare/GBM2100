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
#include "bmi160.h"
#include "bmi160_defs.h"
#include "motion_task.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "i2cm_support.h"
#include "task.h"
#include <stdio.h>

//Fonctions i2c
uint8 read_register_MAX(uint8 baseAddress);

bool write_register_MAX(uint8_t baseAddress, uint8_t data);

void readMultipleBytes_MAX(uint8_t baseAddress, uint8_t *buffer, uint8_t length);


//Fonctions MAX
bool MAX_Init();

bool MAX_Reset();

void read_MAX30102();

/* [] END OF FILE */
