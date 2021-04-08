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
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "project.h"
#include "GUI.h"
#include "pervasive_eink_hardware_driver.h"
#include <stdlib.h>
#include "cy_eink_library.h"
#include "LCDConf.h"
#include "queue.h"
#include "touch.h"
#include "global_variables.h"


// variables menu

QueueHandle_t touchData;

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    // Initialize emWin Graphics and start einkdisplay interface
    GUI_Init();
    Cy_EINK_Start(20);
    Cy_EINK_POWER(1);
    
    GUI_SetPenSize(1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();

     
    //variables
    currentpage = PAGE_MENU;
    
    //touch
    CapSense_Start();
    CapSense_ScanAllWidgets();
    
    xTaskCreate(touch,"touch",400,NULL,1,0);
    vTaskStartScheduler();

 
    
    //menu
    touchData = xQueueCreate(5, sizeof(int8_t));
    
    xTaskCreate(capSense_task,"capSense_task",400,NULL,1,0);
    vTaskStartScheduler();
    while(CapSense_IsBusy());
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
