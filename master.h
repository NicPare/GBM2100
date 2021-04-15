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
#include <arm_math.h>
#include <core_cm4.h>
#include <stdlib.h>

void filtre_2_75s(float32 signal[], float32 signal_filtre[]);

void filtre_PB_AC(float32 signal[], float32 signal_filtre[]);

float32 AC(float32 signal[]);

float32 DC_sum(float32 signal[]);

void SPO2_task(void* pvParameters);

void heart_rate_task(void* pvParameters);



/* [] END OF FILE */
