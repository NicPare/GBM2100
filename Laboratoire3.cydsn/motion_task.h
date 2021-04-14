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
#include "projet_headers.h"


#ifndef MOTION_SENSOR_TASK_H
#define MOTION_SENSOR_TASK_H


/* Task handle */
extern TaskHandle_t xTaskHandleMotion;

/* Task_Motion takes care of the Motion Sensor module in this code example */    
void Task_Motion(void* pvParameters);

#endif








/* [] END OF FILE */
