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
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "MAX30102_functions.h"
#include "touch_task.h"


    float32_t signal_R[1000];
    float32_t signal_IF[1000];
    float32_t signal_AC_R[1000];
    float32_t signal_AC_IF[1000];

    float32 AC_R;
    float32 AC_IF;
    float32 DC_R;
    float32 DC_IF;
    float32 S;
    float32 R;
    

    float32 BPM;


void filtre_6(float32 signal[], float32 signal_filtre[]);

float32 AC(float32 signal[]);

float32 DC_sum(float32 signal[]);

void traitement_task(void* pvParameters);



/* [] END OF FILE */
