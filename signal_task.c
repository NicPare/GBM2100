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

void updateSignal(uint32_t *vecteur, uint32_t fc, uint32_t spo2){
   
    int j=0;

    int tableauX[125];
    for(int i=0; i<125;i++){
        tableauX[i]=2*i;
    }
      for(int i=0; i<124;i++){
        int Y0 = (int)(150-((vecteur[j]-90000)*150)/(105000-90000));
        int Y1 = (int)(150-((vecteur[j+4]-90000)*150)/(105000-90000));
        int X0 = tableauX[i]+7;
        int X1 = tableauX[i+1]+7;
        GUI_DrawLine(X0, Y0, X1, Y1);
        j=j+4;
        
    }
    
    GUI_DrawRect(7,7,257,120);
    GUI_SetFont(GUI_FONT_16B_1);
    GUI_SetTextAlign(GUI_TA_CENTER);
    char frequence[4] = "";
    char taux_oxy[5] = "";
    sprintf(frequence,"%d",fc);
    sprintf(taux_oxy,"%d",spo2);
    GUI_DispStringAt("Heart Rate",65 ,130);
    GUI_DispStringAt("SPO2", 190 ,130);
    GUI_SetFont(GUI_FONT_16_1);
    GUI_DrawLine(30, 150, 95, 150);
    GUI_DrawLine(180, 150, 230, 150);
    GUI_DispStringAt(frequence, 60, 155);
    GUI_DispStringAt(taux_oxy, 200, 155);
    GUI_DispStringAt("%",220 ,155);
}