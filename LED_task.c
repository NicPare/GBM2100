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
#include "GUI.h"
#include "pervasive_eink_hardware_driver.h"
#include "cy_eink_library.h"
#include "LCDConf.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "touch_task.h"
#include "menu_task.h"
#include "global_variables.h"
#include "signal_task.h"
#include "screen_functions.h"
#include "hr_task.h"
#include "LED_task.h"

void updateLED(){
   
    GUI_Clear();
    
    GUI_SetPenSize(2);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    
    //RectangleS
    GUI_DrawRect(1,1,263,175);
    GUI_DrawRect(95,70,160,120);

    
    GUI_SetFont(GUI_FONT_16_1);
    GUI_SetTextAlign(GUI_TA_CENTER);;
    
   
    GUI_SetFont(GUI_FONT_32B_1);
    char valeur_LED[4] = "";
    sprintf(valeur_LED,"%d",LED);

    GUI_DispStringAt(valeur_LED, 130, 80);
    
    GUI_SetFont(GUI_FONT_16B_1);
    GUI_DispStringAt("CHANGE LED VALUE", 60 ,15);
    
    UpdateDisplay(CY_EINK_FULL_2STAGE, true);
}

void vLED_task(){
    
    GUI_Init();
    Cy_EINK_Start(20);
    Cy_EINK_Power(1);
    
    for(;;){
        
        if(currentpage == PAGE_LED){
            
     
                if(currenttouch == BUTTON_R){
                    LED++;
                }
    
                if(currenttouch==BUTTON_L){
                    LED--;
                } 
            
            //if(currenttouch!=NO_TOUCH || first=true){
                updateLED();
            //}
            
        
            if(currenttouch == BUTTON_MENU){           
                currentpage = PAGE_MENU;                            
            }
        
        currenttouch = NO_TOUCH;
 
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }     
}