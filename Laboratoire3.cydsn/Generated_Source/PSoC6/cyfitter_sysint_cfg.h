/*******************************************************************************
* File Name: cyfitter_sysint_cfg.h
* 
* PSoC Creator  4.4
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef INCLUDED_CYFITTER_SYSINT_CFG_H
#define INCLUDED_CYFITTER_SYSINT_CFG_H

#include "sysint/cy_sysint.h"

/* ARM CM4 */
#if (((__CORTEX_M == 4) && (CY_CORE_ID == 0)))
    #define bouton_isr__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t bouton_isr_cfg;

    #define PPG_RDY_isr__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t PPG_RDY_isr_cfg;

    #define I2C_MAX_SCB_IRQ__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t I2C_MAX_SCB_IRQ_cfg;

    #define I2Cm_SCB_IRQ__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t I2Cm_SCB_IRQ_cfg;

    #define UART_SCB_IRQ__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t UART_SCB_IRQ_cfg;

    #define CY_EINK_SPIM_SCB_IRQ__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t CY_EINK_SPIM_SCB_IRQ_cfg;

    #define CapSense_ISR__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t CapSense_ISR_cfg;

    #define SysInt_OrientINT__INTC_ASSIGNED 1u
    extern const cy_stc_sysint_t SysInt_OrientINT_cfg;

#endif /* ((__CORTEX_M == 4) && (CY_CORE_ID == 0)) */


#endif /* INCLUDED_CYFITTER_SYSINT_CFG_H */
