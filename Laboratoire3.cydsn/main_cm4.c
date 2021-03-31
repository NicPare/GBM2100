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
#include "GUI.h"
#include "pervasive_eink_hardware_driver.h"
#include "cy_eink_library.h"
#include "LCDConf.h"
#include <stdlib.h>
#include <stdio.h>

//vecteur sinus de 150 élément entre -1 et 1
float vectorSinus[]={0.099833,0.29552,0.47943,0.64422,0.78333,0.89121,0.96356,0.99749,0.99166,0.9463,0.86321,0.74571,0.59847,0.42738,0.23925,0.041581,-0.15775,-0.35078,-0.52984,-0.68777,-0.81828,-0.91617,-0.97753,-0.99992,-0.98245,-0.92581,-0.83227,-0.70554,-0.55069,-0.37388,-0.18216,0.016814,0.21512,0.40485,0.57844,0.72897,0.85044,0.938,0.98817,0.99894,0.96989,0.90217,0.79849,0.66297,0.50102,0.3191,0.12445,-0.075151,-0.27176,-0.45754,-0.62507,-0.76769,-0.8797,-0.95664,-0.99544,-0.99455,-0.95402,-0.87545,-0.76198,-0.61814,-0.44965,-0.26323,-0.066322,0.13323,0.32747,0.50866,0.66957,0.80378,0.90595,0.97201,0.99931,0.98677,0.9349,0.84575,0.72288,0.5712,0.39674,0.20647,0.0079632,-0.19086,-0.38207,-0.55805,-0.71179,-0.83714,-0.92912,-0.98407,-0.99977,-0.97563,-0.91258,-0.81316,-0.68131,-0.52231,-0.34248,-0.149,0.050423,0.24783,0.43537,0.60554,0.75157,0.86764,0.94912,0.99277,0.99683,0.96115,0.88716,0.77779,0.63742,0.47164,0.28705,0.091022,-0.10864,-0.30396,-0.48717,-0.65096,-0.7888,-0.89519,-0.96589,-0.99808,-0.99049,-0.9434,-0.85871,-0.73978,-0.59136,-0.41936,-0.23065};

/* Image buffer cache */
uint8 imageBufferCache[CY_EINK_FRAME_SIZE] = {0};

/*******************************************************************************
* Function Name: void UpdateDisplay(void)
********************************************************************************
*
* Summary: This function updates the display with the data in the display 
*			buffer.  The function first transfers the content of the EmWin
*			display buffer to the primary EInk display buffer.  Then it calls
*			the Cy_EINK_ShowFrame function to update the display, and then
*			it copies the EmWin display buffer to the Eink display cache buffer
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  It takes about a second to refresh the display.  This is a blocking function
*  and only returns after the display refresh
*
*******************************************************************************/
void UpdateDisplay(cy_eink_update_t updateMethod, bool powerCycle)
{
    cy_eink_frame_t* pEmwinBuffer;

    /* Get the pointer to Emwin's display buffer */
    pEmwinBuffer = (cy_eink_frame_t*)LCD_GetDisplayBuffer();

    /* Update the EInk display */
    Cy_EINK_ShowFrame(imageBufferCache, pEmwinBuffer, updateMethod, powerCycle);

    /* Copy the EmWin display buffer to the imageBuffer cache*/
    memcpy(imageBufferCache, pEmwinBuffer, CY_EINK_FRAME_SIZE);
}


/*******************************************************************************
* Function Name: void ClearScreen(void)
********************************************************************************
*
* Summary: This function clears the screen
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ClearScreen(void)
{
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}
/*******************************************************************************
* Function Name: void WaitforSwitchPressAndRelease(void)
********************************************************************************
*
* Summary: This implements a simple "Wait for button press and release"
*			function.  It first waits for the button to be pressed and then
*			waits for the button to be released.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This is a blocking function and exits only on a button press and release
*
*******************************************************************************/
void WaitforSwitchPressAndRelease(void)
{
    /* Wait for SW2 to be pressed */
    while(Status_SW2_Read() != 0);
    
    /* Wait for SW2 to be released */
    while(Status_SW2_Read() == 0);
}

/*******************************************************************************
* Function Name: int main(void)
********************************************************************************
*
* Summary: À Remplir
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
/*Code 1.1*/
void drawGraph(float *vector150)
{
    int x_pixel[150];
    int y_pixel[150];
    
    for (int i = 0; i < 150; i++)
    {
        x_pixel[i] = 2*i*(250/150);
        y_pixel[i] = (int)((vector150[i]*75)+75);
        GUI_DrawPixel(x_pixel[i], y_pixel[i]);    
    }
    
    for (int i = 0; i < (149); i++)
    {
        GUI_DrawLine(x_pixel[i], y_pixel[i], x_pixel[i+1], y_pixel[i+1]);
    } 
}

/*Code 1.2*/
void updateParameters(int param1, int param2)
{
    char param[10];
   
    GUI_SetFont(GUI_FONT_16_1);
    GUI_DispStringAt("DutyCycle: ", 0, 150);
    GUI_DispStringAt(itoa(param1, param, 10), 69, 150);
    GUI_DispStringAt("%", 90, 150);
    
    GUI_DispStringAt("Moyenne: ", 130, 150);
    GUI_DispStringAt(itoa(param2, param, 10), 190, 150);
    GUI_DispStringAt("mV", 225, 150);
    
}

uint16 Buffer[4000];
bool buffer_flag = false;
uint16 buffer_write = 0, buffer_read = 0;


/*Code 3.2, 3.3*/
void adc_handler()
{
    
    Cy_GPIO_ClearInterrupt(P0_4_PORT, P0_4_NUM);
    NVIC_ClearPendingIRQ(adc_int_cfg.intrSrc);
    
    
    Buffer[buffer_write] = ADC_1_GetResult16(0UL);
    buffer_write ++;
    
    if(buffer_write%2000 == 0)
    {
       buffer_flag = true;
    
    }  

}

float duty;
float sum = 0;
float average;
int index_traitement = 1;
float buffer_convert[100];

/*Code 3.4*/
void traitementSignal()
{
    for (int i = 0; i < 2000; i++)
    {
       sum += 1000*((((Buffer[buffer_read])*2.48)/4096) + 0.41);
       buffer_read ++;
    
    }
    average = sum / (2000);
    duty = (((average/1000)-0.41)/2.48)*100;
    sum = 0;
}



int main(void)
{
    
    __enable_irq(); /* Enable global interrupts. */
    
    /* Initialize emWin Graphics */
    GUI_Init();

    Cy_EINK_Start(20);
    Cy_EINK_Power(1);
    
    GUI_SetPenSize(1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    
    ClearScreen();
    
    
    
       

    for(;;)
    {
    
    }
      
}

/* [] END OF FILE */
