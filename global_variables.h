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


extern uint8_t currentpage;
extern QueueHandle_t touchData;

#define NO_TOUCH 0
#define BUTTON_L 1
#define BUTTON_R 2
#define BUTTON_0 3

const uint8_t PAGE_MENU = 0;
const uint8_t PAGE_SIGNAL_IR = 1;
const uint8_t PAGE_SIGNAL_R = 2;
const uint8_t PAGE_FC = 3;
const uint8_t PAGE_DEL = 4;