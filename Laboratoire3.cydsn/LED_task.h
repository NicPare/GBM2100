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
#include "global_variables.h"
#include "MAX30102_functions.h"
#include "screen_functions.h"
#include "touch_task.h"
#include "master.h"
#include "motion_task.h"

void updateLED();
void updateMenu(int n);
void updateHR();
void updateSignal(float32 *vecteur, uint32_t fc, uint32_t spo2, float32 AC, float32 DC);
void vINTERFACE_task(void* pvParameters);


/* [] END OF FILE */
