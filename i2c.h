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
#define ACC_X1_ADDR     (0x12)
#define ACC_X2_ADDR     (0x13)
#define ACC_Y1_ADDR     (0x14)
#define ACC_Y2_ADDR     (0x15)
#define ACC_Z1_ADDR     (0x16)
#define ACC_Z2_ADDR     (0x17)
#define bmi160_ADDR     (0x68)
#define MAX_ADDR        (0x57)
#define MAX_FIFO_ADDR   (0x07)
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "bmi160.h"

uint8 read_register_MAX(uint8 baseAddress);

void write_register_MAX(uint8_t baseAddress, uint8_t data);

void readMultipleBytes_MAX(uint8_t baseAddress, uint8_t *buffer, uint8_t length);

uint8 read_register_bmi160(uint8 baseAddress);

void write_register_bmi160(uint8_t baseAddress, uint8_t data);

void readMultipleBytes_bmi160(uint8_t baseAddress, uint8_t *buffer, uint8_t length);



/* [] END OF FILE */
