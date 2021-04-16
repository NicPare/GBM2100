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
#include "headers.h"
#include "motion_task.h"


// variables menu

//QueueHandle_t touchData;

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    // Initialize emWin Graphics and start einkdisplay interface
    //GUI_Init();
    //Cy_EINK_Start(20);
    //Cy_EINK_POWER(1);
    
    /*GUI_SetPenSize(1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();*/

     
    //variables
    //currentpage = PAGE_MENU;
    
    //touch
  
    
    //xTaskCreate(touch,"touch",400,NULL,1,0);
    //vTaskStartScheduler();

 
    
    //menu
    //touchData = xQueueCreate(5, sizeof(int8_t));
    
    /*xTaskCreate(capSense_task,"capSense_task",400,NULL,1,0);
    
    while(CapSense_IsBusy());*/
    Cy_GPIO_Write(P0_3_PORT, P0_3_NUM, 0UL);
    I2C_MAX_Start();
    MAX_Reset();
    CyDelay(1000);
    read_register_MAX(0x00);
    MAX_Init();
    
    //Start everything that needs to be started
    
    /*CapSense_Start();
    CapSense_ScanAllWidgets();*/
    
    Motion_Check();
    //Create Tasks
    
   
    xTaskCreate(read_MAX30102_task, "Read MAX30102", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
   
    vTaskStartScheduler();
    
    CY_ASSERT(0);
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
