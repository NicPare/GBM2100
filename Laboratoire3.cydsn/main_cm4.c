/******************************************************************************
* File Name: main_cm4.c
*
* Version: 1.2
*
* Description: This file main application code for the CE223727 EmWin Graphics
*				library EInk Display 

********************************************************************************
*************MODIFIED by Christophe Cloutier-Tremblay.**************************
********************************************************************************
* 
*
* Hardware Dependency: CY8CKIT-028-EPD E-Ink Display Shield
*					   CY8CKIT-062-BLE PSoC6 BLE Pioneer Kit
*
******************************************************************************* 
* Copyright (2019), Cypress Semiconductor Corporation. All rights reserved. 
******************************************************************************* 
* This software, including source code, documentation and related materials 
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its 
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent 
* protection (United States and foreign), United States copyright laws and 
* international treaty provisions. Therefore, you may use this Software only 
* as provided in the license agreement accompanying the software package from 
* which you obtained this Software (“EULA”). 
* 
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive, 
* non-transferable license to copy, modify, and compile the Software source 
* code solely for use in connection with Cypress’s integrated circuit products. 
* Any reproduction, modification, translation, compilation, or representation 
* of this Software except as specified above is prohibited without the express 
* written permission of Cypress. 
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
********************************************************************************/

#include "project.h"

#include "touch_task.h"
#include "global_variables.h"
#include "LED_task.h"
#include "bmi160.h"
#include "bmi160_defs.h"
#include "i2cm_support.h"
#include "master.h"
#include "MAX30102_functions.h"
#include <arm_math.h>
#include <core_cm4.h>
#include <string.h>
#include "motion_task.h"

//*******************************************************************************/

/*******************************************************************************
* Function Name: void isr_bouton(void* pvParameters)
********************************************************************************
*
* Summary:  
* C’est une routine d’interruption déclenchée lorsque le bouton SW2 est appuyé. Il modifie la variable 
* booléenne maxormin si la page actuelle est la page HR, et modifie la variable booléenne alerte si la page 
* actuelle est la page du menu.
*
* Parameters:
* void* pvParameters
*
* Return:
*  None
*
*******************************************************************************/

void isr_bouton(void)
{  
   
 /* Clears the triggered pin interrupt */
    Cy_GPIO_ClearInterrupt(P0_4_PORT, P0_4_NUM);
    NVIC_ClearPendingIRQ(bouton_isr_cfg.intrSrc);

    if(currentpage == PAGE_HR){
        maxormin=!maxormin;
    }
    if(currentpage == PAGE_MENU){
        alerte = !alerte;  
        if(!alerte)
        {
            Cy_GPIO_Write(P0_3_PORT, P0_3_NUM, 1);
            NVIC_DisableIRQ(SysInt_OrientINT_cfg.intrSrc);
            LED_flag = false;
        }
        if(alerte)
        {
            NVIC_EnableIRQ(SysInt_OrientINT_cfg.intrSrc);
        }
    }
}


int main(void)
{

    __enable_irq(); 
    
    //Clear first motion interrupt
    Cy_GPIO_ClearInterrupt(P13_0_PORT, P13_0_NUM );
    NVIC_ClearPendingIRQ(SysInt_OrientINT_cfg.intrSrc);
    
    Cy_GPIO_Write(P0_3_PORT, P0_3_NUM, 1);
    
    

    
    //variables
    currentpage = PAGE_MENU;
    currenttouch = NO_TOUCH;
    hrmin = 30;
    hrmax = 130;
    LED = 32;
    maxormin = true;
    //CHANGEMENT
    alerte = true;
    //

    //Initiate bouton interrupt
    Cy_SysInt_Init(&bouton_isr_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(bouton_isr_cfg.intrSrc);
    NVIC_EnableIRQ(bouton_isr_cfg.intrSrc);
    
    //Create Tasks
    xTaskCreate(traitement_task, "traitement", 2000, NULL, 2, NULL);
    xTaskCreate(read_MAX30102_task, "Read MAX30102",500, NULL, 1, NULL);
    
    xTaskCreate(Task_Motion, "Motion Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vtouch_task,"touch task",configMINIMAL_STACK_SIZE,NULL,2,0);
    xTaskCreate(vINTERFACE_task,"INTERFACE task",2000,NULL,1,NULL);
    
    
    
    vTaskStartScheduler();
    
    //In case of scheduler problem
    
    CY_ASSERT(0);
  
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
