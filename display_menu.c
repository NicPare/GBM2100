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
#include "display_menu.h"
#include "global_variables.h"

uint8_t etatBouton;
int8_t selection = 0;

void updateMenu(param1){
   /* GUI_DrawRect(1,1,250,150);
    GUI_SetFont(GUI_FONT_16_1);
    GUI_SetTextAlign(GUI_TA_CENTER);
    char dutyCycle[3] = "";
    char moyenne[5] = "";
    sprintf(dutyCycle,"%d",param1);
    sprintf(moyenne,"%d",param2);
    GUI_DispStringAt("DutyCycle : ",45 ,155);
    GUI_DispStringAt(dutyCycle, 80, 155);
    GUI_DispStringAt("%      Moyenne : ",100 ,155);
    GUI_DispStringAt(moyenne, 200, 155);
    GUI_DispStringAt("mV",235 ,155);*/
    
    GUI_DrawRect(1,1,250,150);
    GUI_SetTextAlign(GUI_TA_CENTER);
    GUI_SetFont(GUI_FONT_16_1)
    GUI_SetFont(GUI_FONT_24_1);
}

void display_menu (void){
    
    for(;;){
        
        if(currentpage == PAGE_MENU){
            
            while( touchData!=NULL){
               
                xQueueReceive(touchData, &etatBouton, portMAX_DELAY);
       
                if(etatBouton==BUTTON_R){
                    selection++;
                    if(selection == 5){
                        selection = 0;
                    }
                }
    
                if(etatBouton==BUTTON_L){
                    
                    selection--;
                    if(selection == -1){
                        selection = 4;
                    }
                }
            }
            
            // Affichage menu ou selection est en gras
            updateMenu(selection);
            
            if(selection == BUTTON_0){
                currentpage = selection;
            }
        }
    
    }
    
 
}