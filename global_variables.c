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

/* [] END OF FILE */

#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "project.h"
#include "GUI.h"
#include <stdlib.h>
#include "LCDConf.h"
#include "queue.h"
#include "touch_task.h"
#include "global_variables.h"

const uint8_t PAGE_MENU = 0;
const uint8_t PAGE_SIGNAL_R = 1;
const uint8_t PAGE_SIGNAL_IR = 2;
const uint8_t PAGE_LED = 3;
const uint8_t PAGE_HR = 4;
uint32_t signalR[5]= {1,4,1,4,1};