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
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "touch.h"
#include "global_variables.h"

uint8_t currenttouch = NO_TOUCH;


/*
typedef enum 
{
    BUTTON0_TOUCHED     = 0x00u,
    BUTTON1_TOUCHED     = 0x01u,  
    SLIDER_FLICK_LEFT   = 0x02u,
    SLIDER_FLICK_RIGHT  = 0x03u,
    NO_TOUCH            = 0x04u
    
}   touch_data_t; 



volatile uint16_t bouton0=0;
volatile uint16_t bouton1=0;
volatile uint16_t sliderPos=0;
*/
void capSense_task(void)
{
    
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
        
       
    /*
    for(;;)
    {   
       uint8_t currenttouch = NO_TOUCH;
       if (currentpage==PAGE_MENU){
            if(CapSense_IsWidgetActive (CapSense_ButtonL_WDGT_ID)){
                currenttouch = BUTTON_L;
                display_menu(currentTouch);
                xQueueSend(menuData,&currenttouch,portMAX_DELAY);
            }
            if(CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID)){
                currentTouch = BUTTON_R;
                display_menu(currentTouch);
                xQueueSend(menuData,&currenttouch,portMAX_DELAY);
            }
            if(Cy_GPIO_Read(Bouton_0_PORT, Bouton_0_NUM)){
                currentTouch = BUTTON_0;
                //appeler la fonction choisie par l'utilisateur
            }
        } 
     }  
    
    if (currentpage==PAGE_DEL){
            if(CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID)){
                currentTouch = BUTTON_L_TOUCHED;
                
            }
            if(CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID)){
                currentTouch = BUTTON_R_TOUCHED;
                
            }
            if(Cy_GPIO_Read(Bouton_0_PORT, Bouton_0_NUM)){
                currentpage = PAGE_MENU;
                
            }
        } 
     }  */
    
}