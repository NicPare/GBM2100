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
#include "signal_task.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t currenttouch;


void isr_bouton(void)
{  
   
 /* Clears the triggered pin interrupt */
    Cy_GPIO_ClearInterrupt(P0_4_PORT, P0_4_NUM);
    NVIC_ClearPendingIRQ(bouton_isr_cfg.intrSrc);
    button_menu=true;
}



void vtouch_task(){
    //
    /*
    bool previoustouch = false;
    Cy_SysInt_Init(&bouton_isr_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(bouton_isr_cfg.intrSrc);
    NVIC_EnableIRQ(bouton_isr_cfg.intrSrc);
    //
    */
    cy_status capSenseApiResult;


    capSenseApiResult = CapSense_Start();
    CapSense_ScanAllWidgets();
    for(;;)
    {
      if(CapSense_IsBusy() == CapSense_NOT_BUSY)
        {
        //
       
        //
            
        /* Variable that stores CapSense API results */
        CapSense_ProcessAllWidgets();
        
        if(CapSense_IsWidgetActive(CapSense_BUTTONL_WDGT_ID)){
   
                    
                    currenttouch = BUTTON_R;
               
        }
        
        if(CapSense_IsWidgetActive(CapSense_BUTTONR_WDGT_ID)){
        
               // {
                    currenttouch = BUTTON_L;
               // }
        }
        
        if(CapSense_IsWidgetActive(CapSense_LINEARSLIDER0_WDGT_ID)){
            currenttouch = BUTTON_MENU;
        }
       
  // 
        
        CapSense_UpdateAllBaselines();
        CapSense_ScanAllWidgets();
        


        
        
   
        //CyDelay(500);
    
        
    }
        
        vTaskDelay(pdMS_TO_TICKS(100));
    
    }

 }
