/* ========================================
 *
 
 *
 * ========================================
*/



#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include "GUI.h"
#include <stdlib.h>
#include "LCDConf.h"
#include "queue.h"
#include "cy_eink_library.h"
#include "pervasive_eink_hardware_driver.h"
#include "FreeRTOSConfig.h"


// TOUCH AND PAGE
extern const uint8_t PAGE_MENU;
extern const uint8_t PAGE_SIGNAL_IR;
extern const uint8_t PAGE_SIGNAL_R;
extern const uint8_t PAGE_HR;
extern const uint8_t PAGE_LED;

uint8_t currentpage;
uint8_t currenttouch;


#define NO_TOUCH 0
#define BUTTON_L 1
#define BUTTON_R 2
#define BUTTON_0 3
#define BUTTON_MENU 4


//SIGNAL

// déclarer ir_data
// déclarer r_data
uint32_t heart_rate;
uint32_t SPO2;

//LED
uint32_t LED;

//HR
bool maxormin;
uint32_t hrmax;
uint32_t hrmin;

/* [] END OF FILE */
