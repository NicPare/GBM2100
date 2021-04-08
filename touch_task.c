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
#include "queue.h"
#include "touch_task.h"
#include "global_variables.h"

uint8_t currenttouch = NO_TOUCH;



void vtouch_task(){

    for(;;)
    {
      
        /* Variable that stores CapSense API results */
        cy_status capSenseApiResult;
    
        CapSense_ProcessAllWidgets();
        
        
        if(CapSense_IsWidgetActive(CapSense_BUTTONL_WDGT_ID)){
           currenttouch = BUTTON_L;
           xQueueSend(touchData,&currenttouch,portMAX_DELAY);
        }
        
        if(CapSense_IsWidgetActive(CapSense_BUTTONR_WDGT_ID)){
           currenttouch = BUTTON_R;
           xQueueSend(touchData,&currenttouch,portMAX_DELAY);
        }
        
        //if BUTTON0 appuyé...
        
        CapSense_UpdateAllBaselines();
        CapSense_ScanAllWidgets();
        vTaskDelay(pdMS_TO_TICKS(100));
        
    }
    
}
   