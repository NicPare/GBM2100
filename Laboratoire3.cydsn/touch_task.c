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


#include "touch_task.h"


uint8_t currenttouch;


/*******************************************************************************
* Function Name: void vtouch_task(void* pvParameters)
********************************************************************************
*
* Summary:  
* C’est une tâche qui lit le CapSense et modifie la variable représentant l’état du bouton selon la lecture
*
* Parameters:
* void* pvParameters
*
* Return:
*  None
*
*******************************************************************************/

void vtouch_task(void* pvParameters){
    (void)pvParameters;


    cy_status capSenseApiResult;

    capSenseApiResult = CapSense_Start();
    CapSense_ScanAllWidgets();
    for(;;)
    {

        if(CapSense_IsBusy() == CapSense_NOT_BUSY)
        {

            
            // Variable that stores CapSense API results
            CapSense_ProcessAllWidgets();
        
            if(CapSense_IsWidgetActive(CapSense_BUTTONL_WDGT_ID))
            {      
                currenttouch = BUTTON_R;   
            }
        
            if(CapSense_IsWidgetActive(CapSense_BUTTONR_WDGT_ID))
            {
                currenttouch = BUTTON_L;
            }
        
            if(CapSense_IsWidgetActive(CapSense_LINEARSLIDER0_WDGT_ID))
            {
                currenttouch = BUTTON_MENU;
            }
       
            CapSense_UpdateAllBaselines();
            CapSense_ScanAllWidgets();
        
   
            vTaskDelay(pdMS_TO_TICKS(100));
    
        
        }
    }

 }
