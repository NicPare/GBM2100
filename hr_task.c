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



void updateHR(){
   
   
    GUI_Clear();
    
    GUI_SetPenSize(2);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    
    //RectangleS
    GUI_DrawRect(1,1,263,175);
    GUI_DrawRect(30,70,90,120);
    GUI_DrawRect(150,70,225,120);

    
    GUI_SetFont(GUI_FONT_16_1);
    GUI_SetTextAlign(GUI_TA_CENTER);;
    
   
    GUI_SetFont(GUI_FONT_32B_1);
    char frequence_max[4] = "";
    char frequence_min[4] = "";
    sprintf(frequence_max,"%d",hrmax);
    sprintf(frequence_min,"%d",hrmin);

    GUI_DispStringAt(frequence_min, 60, 80);
    GUI_DispStringAt(frequence_max, 165, 80);
    
    GUI_SetFont(GUI_FONT_16B_1);
    GUI_DispStringAt("Min Heart Rate",10 ,130);
    GUI_DispStringAt("Max Heart Rate", 135 ,130);
    GUI_DispStringAt("CHANGE HEART RATE INTERVAL",30 ,15);
    
    UpdateDisplay(CY_EINK_FULL_2STAGE, true);
    
}

void vHR_task(){
    
    GUI_Init();
    Cy_EINK_Start(20);
    Cy_EINK_Power(1);
    bool maxormin = true;
    
    for(;;){
        
  
        if(currentpage == PAGE_HR){
            
     
                if(currenttouch == BUTTON_R){
                    if(maxormin == true){
                        hrmin++;
                    }
                    if(maxormin == false){
                        hrmax++;
                    }
                }
    
                if(currenttouch==BUTTON_L){
                    
                    if(maxormin == true){
                        hrmin--;
                    }
                    if(maxormin == false){
                        hrmax--;
                    }
                } 
            
            //if(currenttouch!=NO_TOUCH || first==true){
                updateHR();
            //}
            
            if(currenttouch == BUTTON_0){
                 // if button_0 pressed, we switch variables (hr min or max)
                maxormin= !maxormin;
            } 
        
            if(currenttouch == BUTTON_MENU){           
                currentpage = PAGE_MENU;                            
            }
        
        currenttouch = NO_TOUCH;
        first = false;
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }     
}
