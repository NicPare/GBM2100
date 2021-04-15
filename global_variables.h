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
#include "signal_task.h"

extern const uint8_t PAGE_MENU;
extern const uint8_t PAGE_SIGNAL_IR;
extern const uint8_t PAGE_SIGNAL_R;
extern const uint8_t PAGE_HR;
extern const uint8_t PAGE_LED;

uint8_t currentpage;
uint8_t currenttouch;
uint32_t hrmax;
uint32_t hrmin;
uint32_t LED;
uint8_t button_menu;
bool first;
uint32_t signalR[];

QueueHandle_t touchData;

#define NO_TOUCH 0
#define BUTTON_L 1
#define BUTTON_R 2
#define BUTTON_0 3
#define BUTTON_MENU 4


//signal
uint32_t signalR[5];
uint32_t signalIR[5];
uint32_t heart_rate;
uint32_t SPO2;