/***************************************************************************//**
* \file     PWM_CLOCK.h
* \version  1.0
*
* \brief
* Provides the source code to the API for the PWM_CLOCK Component.
*
********************************************************************************
* \copyright
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PWM_CLOCK_NAME_PWM_CLOCK_H)
#define CY_PWM_CLOCK_NAME_PWM_CLOCK_H

/* For _DIV_TYPE and _DIV_NUM #defines */
#include "cyfitter.h"

/* makes uint32_t defined */
#include <stdint.h>

#include "sysclk/cy_sysclk.h"

/***************************************
* Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The peripheral clock divider number */
#define PWM_CLOCK_DIV_NUM ((uint32_t)PWM_CLOCK__DIV_NUM)
/** The peripheral clock divider type */
#define PWM_CLOCK_DIV_TYPE ((cy_en_divider_types_t)PWM_CLOCK__DIV_TYPE)
/** @} group_macros */

/***************************************
* Function Prototypes
***************************************/

/**
* \addtogroup group_general
* @{
*/

/*******************************************************************************
* Function Name: PWM_CLOCK_Enable
****************************************************************************//**
*
* Enables the programmable clock divider assigned to this Component.
*
* \param None
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void PWM_CLOCK_Enable(void)
{
    (void)Cy_SysClk_PeriphEnableDivider(PWM_CLOCK_DIV_TYPE, PWM_CLOCK_DIV_NUM);
}

/*******************************************************************************
* Function Name: PWM_CLOCK_Disable
****************************************************************************//**
*
* Disables the programmable clock divider assigned to this Component.
*
* \param None
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void PWM_CLOCK_Disable(void)
{
    (void)Cy_SysClk_PeriphDisableDivider(PWM_CLOCK_DIV_TYPE, PWM_CLOCK_DIV_NUM);
}

/*******************************************************************************
* Function Name: PWM_CLOCK_SetDivider
****************************************************************************//**
*
* Sets the value of a programmable clock divider assigned to this Component.
* This is only used for integer dividers. Use PWM_CLOCK_SetFracDivider()
* for setting factional dividers.
*
* \param dividerValue
* The divider value. The source of the divider is peri_clk which is a divided
* version of hf_clk[0]. The divider value causes integer division of
* (divider value + 1), or division by 1 to 256 (8-bit divider) or
* 1 to 65536 (16-bit divider).
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void PWM_CLOCK_SetDivider(uint32_t dividerValue)
{
    (void)Cy_SysClk_PeriphSetDivider(PWM_CLOCK_DIV_TYPE, PWM_CLOCK_DIV_NUM, dividerValue);
}

/*******************************************************************************
* Function Name: PWM_CLOCK_GetDivider
****************************************************************************//**
*
* Returns the integer divider value for the programmable clock divider assigned
* to this Component. This is only used for integer dividers.
* Use PWM_CLOCK_GetFracDivider() with a fractional divider.
*
* \param None
*
* \return
* The divider value. The source of the divider is peri_clk which is a divided
* version of hf_clk[0]. The integer division done is by (divider value + 1),
* or division by 1 to 256 (8-bit divider) or 1 to 65536 (16-bit divider).
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_CLOCK_GetDivider(void)
{
    return Cy_SysClk_PeriphGetDivider(PWM_CLOCK_DIV_TYPE, PWM_CLOCK_DIV_NUM);
}

/*******************************************************************************
* Function Name: PWM_CLOCK_SetFracDivider
****************************************************************************//**
*
* Sets the values of a programmable clock divider assigned to this Component.
* This is only used for fractional dividers. Use PWM_CLOCK_SetDivider()
* for setting integer dividers.
*
* \param dividerIntValue
* The integer divider value. The source of the divider is peri_clk which is a
* divided version of hf_clk[0]. The divider value causes integer division of
* (divider value + 1), or division by 1 to 65536 (16-bit divider) or
* 1 to 16777216 (24-bit divider).
*
* \param dividerFracValue
* This is the fraction piece of the divider. The fractional divider can be
* 0 - 31; it divides the clock by 1/32 for each count. To divide the clock by
* 11/32nds, set this value to 11.
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void PWM_CLOCK_SetFracDivider(uint32_t dividerIntValue, uint32_t dividerFracValue)
{
    (void)Cy_SysClk_PeriphSetFracDivider(PWM_CLOCK_DIV_TYPE, PWM_CLOCK_DIV_NUM, dividerIntValue, dividerFracValue);
}

/*******************************************************************************
* Function Name: PWM_CLOCK_GetFracDivider
****************************************************************************//**
*
* Returns the divider values for the programmable clock divider assigned to this
* Component. This is only used for fractional dividers.
* Use PWM_CLOCK_GetDivider() with an integer divider.
*
* \param *dividerIntValue
* pointer to return integer divider value
*
* \param *dividerFracValue
* pointer to return fractional divider value
*
* \return None. Loads pointed-to variables.
*
*******************************************************************************/
__STATIC_INLINE void PWM_CLOCK_GetFracDivider(uint32_t *dividerIntValue, uint32_t *dividerFracValue)
{
    Cy_SysClk_PeriphGetFracDivider(PWM_CLOCK_DIV_TYPE, PWM_CLOCK_DIV_NUM, dividerIntValue, dividerFracValue);
}

/** @} general */

#endif /* CY_CLOCK_PWM_CLOCK_H */

/* [] END OF FILE */
