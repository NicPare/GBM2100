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
#include "menu_task.h"
#include "global_variables.h"
#include "screen_functions.h"
#include "GUI.h"
#include "pervasive_eink_hardware_driver.h"
#include <stdlib.h>
#include "cy_eink_library.h"
#include "LCDConf.h"
#include "hr_task.h"

uint8_t etatBouton;
int8_t selection = 1;

void updateMenu(int n){
    
    ClearScreen();
    
    GUI_SetPenSize(2);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    
    //Rectangle
    GUI_DrawRect(1,1,263,175);
    
    //Line
    GUI_SetPenSize(2);
    GUI_DrawLine(95,30,170,30);
    
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    
    //Write MENU
    GUI_SetFont(GUI_FONT_24B_1);
    GUI_SetTextAlign(GUI_TA_CENTER);
    GUI_DispStringAt("MENU",135 ,5);
    
    
    //Write options
    if(n == 1){
        GUI_SetFont(GUI_FONT_16B_1);
        GUI_DispStringAt("Show oxygenated signal",40 ,40);
        GUI_SetFont(GUI_FONT_16_1);
        GUI_DispStringAt("Show non-oxygenated signal",40 ,75);
        GUI_DispStringAt("Change intensity of LED",40 ,110);
        GUI_DispStringAt("Change the heart rate interval",40 ,145);
    }
    if(n == 2){
        GUI_SetFont(GUI_FONT_16B_1);
        GUI_DispStringAt("Show non-oxygenated signal",40 ,75);
        GUI_SetFont(GUI_FONT_16_1);
        GUI_DispStringAt("Show oxygenated signal",40 ,40);
        GUI_DispStringAt("Change intensity of LED",40 ,110);
        GUI_DispStringAt("Change the heart rate interval",40 ,145);
    }
    if(n == 3){
        GUI_SetFont(GUI_FONT_16B_1);
        GUI_DispStringAt("Change intensity of LED",40 ,110); 
        GUI_SetFont(GUI_FONT_16_1);
        GUI_DispStringAt("Show oxygenated signal",40 ,40);
        GUI_DispStringAt("Show non-oxygenated signal",40 ,75);
        GUI_DispStringAt("Change the heart rate interval",40 ,145);
    }
    if(n == 4){
        GUI_SetFont(GUI_FONT_16_1);
        GUI_DispStringAt("Show oxygenated signal",40 ,40);
        GUI_DispStringAt("Show non-oxygenated signal",40 ,75);
        GUI_DispStringAt("Change intensity of LED",40 ,110);
        GUI_SetFont(GUI_FONT_16B_1);
        GUI_DispStringAt("Change the heart rate interval",40 ,145);
    }
    
    
    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}


void vmenu_task (){
 
    for(;;){
        
        if(currentpage == PAGE_MENU){
            
            // Efface la valeur précédente de etatBouton si la file est vide
            etatBouton = 10;
            
            while( touchData!=NULL){
               
                xQueueReceive(touchData, &etatBouton, portMAX_DELAY);
       
                if(etatBouton == BUTTON_R){
                    selection++;
                    if(selection == 5){
                        selection = 1;
                    }
                }
    
                if(etatBouton==BUTTON_L){
                    
                    selection--;
                    if(selection == 0){
                        selection = 4;
                    }
                }
            }
            
            // Affichage menu ou selection est en gras
            updateMenu(selection);
            
            // délai #à écrire
            
            if(etatBouton == BUTTON_0){
                currentpage = selection;
            }
        }
    
    }
    
 
}