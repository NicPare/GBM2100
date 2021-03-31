/*******************************************************************************
* File Name: CY_EINK_Timer.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the CY_EINK_Timer
*  component
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CY_EINK_Timer.h"

/** Indicates whether or not the CY_EINK_Timer has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  CY_EINK_Timer_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the CY_EINK_Timer_Start() routine.
*/
uint8_t CY_EINK_Timer_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated CY_EINK_Timer_Init() function.
*/ 
cy_stc_tcpwm_counter_config_t const CY_EINK_Timer_config =
{
        .period = 10000UL,
        .clockPrescaler = 1UL,
        .runMode = 1UL,
        .countDirection = 0UL,
        .compareOrCapture = 0UL,
        .compare0 = 5000UL,
        .compare1 = 16384UL,
        .enableCompareSwap = false,
        .interruptSources = 0UL,
        .captureInputMode = 3UL,
        .captureInput = CY_TCPWM_INPUT_CREATOR,
        .reloadInputMode = 3UL,
        .reloadInput = CY_TCPWM_INPUT_CREATOR,
        .startInputMode = 3UL,
        .startInput = CY_TCPWM_INPUT_CREATOR,
        .stopInputMode = 3UL,
        .stopInput = CY_TCPWM_INPUT_CREATOR,
        .countInputMode = 3UL,
        .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: CY_EINK_Timer_Start
****************************************************************************//**
*
*  Calls the CY_EINK_Timer_Init() when called the first time and enables 
*  the CY_EINK_Timer. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref CY_EINK_Timer_initVar
*
*******************************************************************************/
void CY_EINK_Timer_Start(void)
{
    if (0U == CY_EINK_Timer_initVar)
    {
        (void)Cy_TCPWM_Counter_Init(CY_EINK_Timer_HW, CY_EINK_Timer_CNT_NUM, &CY_EINK_Timer_config); 

        CY_EINK_Timer_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(CY_EINK_Timer_HW, CY_EINK_Timer_CNT_MASK);
    
    #if (CY_EINK_Timer_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(CY_EINK_Timer_HW, CY_EINK_Timer_CNT_MASK);
    #endif /* (CY_EINK_Timer_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
