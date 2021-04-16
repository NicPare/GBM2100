/***************************************************************************//**
* \file I2Cm.c
* \version 2.0
*
*  This file provides constants and parameter values for the I2C component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(I2Cm_CY_SCB_I2C_PDL_H)
#define I2Cm_CY_SCB_I2C_PDL_H

#include "cyfitter.h"
#include "scb/cy_scb_i2c.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*   Initial Parameter Constants
****************************************/

#define I2Cm_MODE               (0x2U)
#define I2Cm_MODE_SLAVE_MASK    (0x1U)
#define I2Cm_MODE_MASTER_MASK   (0x2U)

#define I2Cm_ENABLE_SLAVE       (0UL != (I2Cm_MODE & I2Cm_MODE_SLAVE_MASK))
#define I2Cm_ENABLE_MASTER      (0UL != (I2Cm_MODE & I2Cm_MODE_MASTER_MASK))
#define I2Cm_MANUAL_SCL_CONTROL (0U)


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
/* Component only APIs. */
void I2Cm_Start(void);

/* Basic functions. */
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_Init(cy_stc_scb_i2c_config_t const *config);
__STATIC_INLINE void I2Cm_DeInit (void);
__STATIC_INLINE void I2Cm_Enable (void);
__STATIC_INLINE void I2Cm_Disable(void);

/* Data rate configuration functions. */
__STATIC_INLINE uint32_t I2Cm_SetDataRate(uint32_t dataRateHz, uint32_t scbClockHz);
__STATIC_INLINE uint32_t I2Cm_GetDataRate(uint32_t scbClockHz);

/* Register callbacks. */
__STATIC_INLINE void I2Cm_RegisterEventCallback(cy_cb_scb_i2c_handle_events_t callback);
#if (I2Cm_ENABLE_SLAVE)
__STATIC_INLINE void I2Cm_RegisterAddrCallback (cy_cb_scb_i2c_handle_addr_t callback);
#endif /* (I2Cm_ENABLE_SLAVE) */

/* Configuration functions. */
#if (I2Cm_ENABLE_SLAVE)
__STATIC_INLINE void     I2Cm_SlaveSetAddress(uint8_t addr);
__STATIC_INLINE uint32_t I2Cm_SlaveGetAddress(void);
__STATIC_INLINE void     I2Cm_SlaveSetAddressMask(uint8_t addrMask);
__STATIC_INLINE uint32_t I2Cm_SlaveGetAddressMask(void);
#endif /* (I2Cm_ENABLE_SLAVE) */

#if (I2Cm_ENABLE_MASTER)
__STATIC_INLINE void I2Cm_MasterSetLowPhaseDutyCycle (uint32_t clockCycles);
__STATIC_INLINE void I2Cm_MasterSetHighPhaseDutyCycle(uint32_t clockCycles);
#endif /* (I2Cm_ENABLE_MASTER) */

/* Bus status. */
__STATIC_INLINE bool     I2Cm_IsBusBusy(void);

/* Slave functions. */
#if (I2Cm_ENABLE_SLAVE)
__STATIC_INLINE uint32_t I2Cm_SlaveGetStatus(void);

__STATIC_INLINE void     I2Cm_SlaveConfigReadBuf(uint8_t *buffer, uint32_t size);
__STATIC_INLINE void     I2Cm_SlaveAbortRead(void);
__STATIC_INLINE uint32_t I2Cm_SlaveGetReadTransferCount(void);
__STATIC_INLINE uint32_t I2Cm_SlaveClearReadStatus(void);

__STATIC_INLINE void     I2Cm_SlaveConfigWriteBuf(uint8_t *buffer, uint32_t size);
__STATIC_INLINE void     I2Cm_SlaveAbortWrite(void);
__STATIC_INLINE uint32_t I2Cm_SlaveGetWriteTransferCount(void);
__STATIC_INLINE uint32_t I2Cm_SlaveClearWriteStatus(void);
#endif /* (I2Cm_ENABLE_SLAVE) */

/* Master interrupt processing functions. */
#if (I2Cm_ENABLE_MASTER)
__STATIC_INLINE uint32_t I2Cm_MasterGetStatus(void);

__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterRead(cy_stc_scb_i2c_master_xfer_config_t *xferConfig);
__STATIC_INLINE void I2Cm_MasterAbortRead(void);
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterWrite(cy_stc_scb_i2c_master_xfer_config_t *xferConfig);
__STATIC_INLINE void I2Cm_MasterAbortWrite(void);
__STATIC_INLINE uint32_t I2Cm_MasterGetTransferCount(void);

/* Master manual processing functions. */
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterSendStart(uint32_t address, cy_en_scb_i2c_direction_t bitRnW, uint32_t timeoutMs);
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterSendReStart(uint32_t address, cy_en_scb_i2c_direction_t bitRnW, uint32_t timeoutMs);
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterSendStop(uint32_t timeoutMs);
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterReadByte(cy_en_scb_i2c_command_t ackNack, uint8_t *byte, uint32_t timeoutMs);
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterWriteByte(uint8_t byte, uint32_t timeoutMs);
#endif /* (I2Cm_ENABLE_MASTER) */

/* Interrupt handler. */
__STATIC_INLINE void I2Cm_Interrupt(void);
/** @} group_general */


/***************************************
*    Variables with External Linkage
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t I2Cm_initVar;
extern cy_stc_scb_i2c_config_t const I2Cm_config;
extern cy_stc_scb_i2c_context_t I2Cm_context;
/** @} group_globals */


/***************************************
*         Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The pointer to the base address of the SCB instance */
#define I2Cm_HW     ((CySCB_Type *) I2Cm_SCB__HW)

/** The desired data rate in Hz */
#define I2Cm_DATA_RATE_HZ      (100000U)

/** The frequency of the clock used by the Component in Hz */
#define I2Cm_CLK_FREQ_HZ       (1538461U)

/** The number of Component clocks used by the master to generate the SCL
* low phase. This number is calculated by GUI based on the selected data rate.
*/
#define I2Cm_LOW_PHASE_DUTY_CYCLE   (8U)

/** The number of Component clocks used by the master to generate the SCL
* high phase. This number is calculated by GUI based on the selected data rate.
*/
#define I2Cm_HIGH_PHASE_DUTY_CYCLE  (8U)
/** @} group_macros */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: I2Cm_Init
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_Init(cy_stc_scb_i2c_config_t const *config)
{
    return Cy_SCB_I2C_Init(I2Cm_HW, config, &I2Cm_context);
}


/*******************************************************************************
*  Function Name: I2Cm_DeInit
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_DeInit(void)
{
    Cy_SCB_I2C_DeInit(I2Cm_HW);
}


/*******************************************************************************
* Function Name: I2Cm_Enable
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_Enable(void)
{
    Cy_SCB_I2C_Enable(I2Cm_HW);
}


/*******************************************************************************
* Function Name: I2Cm_Disable
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_Disable(void)
{
    Cy_SCB_I2C_Disable(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_SetDataRate
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SetDataRate() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_SetDataRate(uint32_t dataRateHz, uint32_t scbClockHz)
{
    return Cy_SCB_I2C_SetDataRate(I2Cm_HW, dataRateHz, scbClockHz);
}


/*******************************************************************************
* Function Name: I2Cm_GetDataRate
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_GetDataRate() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_GetDataRate(uint32_t scbClockHz)
{
    return Cy_SCB_I2C_GetDataRate(I2Cm_HW, scbClockHz);
}


/*******************************************************************************
* Function Name: I2Cm_RegisterEventCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_RegisterEventCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_RegisterEventCallback(cy_cb_scb_i2c_handle_events_t callback)
{
    Cy_SCB_I2C_RegisterEventCallback(I2Cm_HW, callback, &I2Cm_context);
}


#if (I2Cm_ENABLE_SLAVE)
/*******************************************************************************
* Function Name: I2Cm_RegisterAddrCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_RegisterAddrCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_RegisterAddrCallback(cy_cb_scb_i2c_handle_addr_t callback)
{
    Cy_SCB_I2C_RegisterAddrCallback(I2Cm_HW, callback, &I2Cm_context);
}
#endif /* (I2Cm_ENABLE_SLAVE) */


/*******************************************************************************
* Function Name: I2Cm_IsBusBusy
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_IsBusBusy() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool I2Cm_IsBusBusy(void)
{
    return Cy_SCB_I2C_IsBusBusy(I2Cm_HW);
}


#if (I2Cm_ENABLE_SLAVE)
/*******************************************************************************
* Function Name: I2Cm_SlaveSetAddress
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetAddress() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_SlaveSetAddress(uint8_t addr)
{
    Cy_SCB_I2C_SlaveSetAddress(I2Cm_HW, addr);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveGetAddress
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetAddress() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_SlaveGetAddress(void)
{
    return Cy_SCB_I2C_SlaveGetAddress(I2Cm_HW);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveSetAddressMask
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveSetAddressMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_SlaveSetAddressMask(uint8_t addrMask)
{
    Cy_SCB_I2C_SlaveSetAddressMask(I2Cm_HW, addrMask);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveGetAddressMask
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetAddressMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_SlaveGetAddressMask(void)
{
    return Cy_SCB_I2C_SlaveGetAddressMask(I2Cm_HW);
}
#endif /* (I2Cm_ENABLE_SLAVE) */

#if (I2Cm_ENABLE_MASTER)
/*******************************************************************************
* Function Name: I2Cm_MasterSetLowPhaseDutyCycle
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSetLowPhaseDutyCycle() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_MasterSetLowPhaseDutyCycle(uint32_t clockCycles)
{
    Cy_SCB_I2C_MasterSetLowPhaseDutyCycle(I2Cm_HW, clockCycles);
}


/*******************************************************************************
* Function Name: I2Cm_MasterSetHighPhaseDutyCycle
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSetHighPhaseDutyCycle() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_MasterSetHighPhaseDutyCycle(uint32_t clockCycles)
{
    Cy_SCB_I2C_MasterSetHighPhaseDutyCycle(I2Cm_HW, clockCycles);
}
#endif /* (I2Cm_ENABLE_MASTER) */


#if (I2Cm_ENABLE_SLAVE)
/*******************************************************************************
* Function Name: I2Cm_SlaveGetStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_SlaveGetStatus(void)
{
    return Cy_SCB_I2C_SlaveGetStatus(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveConfigReadBuf
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveConfigReadBuf() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_SlaveConfigReadBuf(uint8_t *buffer, uint32_t size)
{
    Cy_SCB_I2C_SlaveConfigReadBuf(I2Cm_HW, buffer, size, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveAbortRead
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveAbortRead() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_SlaveAbortRead(void)
{
    Cy_SCB_I2C_SlaveAbortRead(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveGetReadTransferCount
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetReadTransferCount() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_SlaveGetReadTransferCount(void)
{
    return Cy_SCB_I2C_SlaveGetReadTransferCount(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveClearReadStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveClearReadStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_SlaveClearReadStatus(void)
{
    return Cy_SCB_I2C_SlaveClearReadStatus(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveConfigWriteBuf
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveConfigWriteBuf() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_SlaveConfigWriteBuf(uint8_t *buffer, uint32_t size)
{
    Cy_SCB_I2C_SlaveConfigWriteBuf(I2Cm_HW, buffer, size, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveAbortWrite
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveAbortWrite() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_SlaveAbortWrite(void)
{
    Cy_SCB_I2C_SlaveAbortWrite(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveGetWriteTransferCount
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetWriteTransferCount() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_SlaveGetWriteTransferCount(void)
{
    return Cy_SCB_I2C_SlaveGetWriteTransferCount(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_SlaveClearWriteStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveClearWriteStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_SlaveClearWriteStatus(void)
{
    return Cy_SCB_I2C_SlaveClearWriteStatus(I2Cm_HW, &I2Cm_context);
}
#endif /* (I2Cm_ENABLE_SLAVE) */


#if (I2Cm_ENABLE_MASTER)
/*******************************************************************************
* Function Name: I2Cm_MasterGetStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterGetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_MasterGetStatus(void)
{
    return Cy_SCB_I2C_MasterGetStatus(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterRead
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterRead() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterRead(cy_stc_scb_i2c_master_xfer_config_t *xferConfig)
{
    return Cy_SCB_I2C_MasterRead(I2Cm_HW, xferConfig, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterAbortRead
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterAbortRead() PDL driver function.
*
******************************************************************************/
__STATIC_INLINE void I2Cm_MasterAbortRead(void)
{
    Cy_SCB_I2C_MasterAbortRead(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterWrite
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterWrite() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterWrite(cy_stc_scb_i2c_master_xfer_config_t *xferConfig)
{
    return Cy_SCB_I2C_MasterWrite(I2Cm_HW, xferConfig, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterAbortWrite
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterAbortWrite() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_MasterAbortWrite(void)
{
    Cy_SCB_I2C_MasterAbortWrite(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterGetTransferCount
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterGetTransferCount() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t I2Cm_MasterGetTransferCount(void)
{
    return Cy_SCB_I2C_MasterGetTransferCount(I2Cm_HW, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterSendStart
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSendStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterSendStart(uint32_t address, cy_en_scb_i2c_direction_t bitRnW, uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterSendStart(I2Cm_HW, address, bitRnW, timeoutMs, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterSendReStart
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSendReStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterSendReStart(uint32_t address, cy_en_scb_i2c_direction_t bitRnW, uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterSendReStart(I2Cm_HW, address, bitRnW, timeoutMs, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterSendStop
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSendStop() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterSendStop(uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterSendStop(I2Cm_HW, timeoutMs, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterReadByte
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterReadByte() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterReadByte(cy_en_scb_i2c_command_t ackNack, uint8_t *byte, uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterReadByte(I2Cm_HW, ackNack, byte, timeoutMs, &I2Cm_context);
}


/*******************************************************************************
* Function Name: I2Cm_MasterWriteByte
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterWriteByte() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t I2Cm_MasterWriteByte(uint8_t byte, uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterWriteByte(I2Cm_HW, byte, timeoutMs, &I2Cm_context);
}
#endif /* (I2Cm_ENABLE_MASTER) */


/*******************************************************************************
* Function Name: I2Cm_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void I2Cm_Interrupt(void)
{
    Cy_SCB_I2C_Interrupt(I2Cm_HW, &I2Cm_context);
}

#if defined(__cplusplus)
}
#endif

#endif /* I2Cm_CY_SCB_I2C_PDL_H */


/* [] END OF FILE */
