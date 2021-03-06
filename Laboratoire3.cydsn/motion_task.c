/******************************************************************************
* File Name: motion_task.c
*
* Version: 1.0
*
* Description: This file contains the task that initializes the BMI160 Motion
*              Sensor and configured it to generate interrupt on any orientation 
*              change.
*
* Related Document: CE223468_PSoC6_Interfacing_BMI160(I2C)_FreeRTOS.pdf
*
* Hardware Dependency: CY8CKIT-062-BLE PSoC 6 BLE Pioneer Kit
*                      CY8CKIT-028-EPD E-INK Display Shield
*
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
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
*******************************************************************************/

/* Header files include */
#include "motion_task.h"



/** 
 * Orientation types:
 * Indicates which edge of the board is pointing towards the ceiling/sky 
 */
typedef enum
{
    ORIENTATION_TOP_EDGE        = 0,    /* Top edge of the board points towards the ceiling */
    ORIENTATION_BOTTOM_EDGE     = 1,    /* Bottom edge of the board points towards the ceiling */
    ORIENTATION_LEFT_EDGE       = 2,    /* Left edge of the board (USB connector side) points towards the ceiling */
    ORIENTATION_RIGHT_EDGE      = 3,    /* Right edge of the board points towards the ceiling */
    ORIENTATION_DISP_UP         = 4,    /* Display faces up (towards the sky/ceiling) */
    ORIENTATION_DISP_DOWN       = 5     /* Display faces down (towards the ground) */
} orientation_t;

/* Instance of BMI160 structure */
struct bmi160_dev sensor;

/* Motion task handle */
//TaskHandle_t xTaskHandleMotion;

/** 
 * These static functions are used by the Motion Task. These are not available 
 * outside this file. See the respective function definitions for more details. 
 */
static void Orientation_Interrupt(void);
static int8_t MotionSensor_Init(void);
static int8_t MotionSensor_ConfigOrientIntr(void);
static int8_t MotionSensor_UpdateOrientation(orientation_t*);

/*******************************************************************************
* Function Name: void Task_Motion(void *pvParameters)
********************************************************************************
* Summary:
*  Task that processes the Motion Sensor, and then commands other tasks 
*  to take an action.
*
* Parameters:
*  void *pvParameters : Task parameter defined during task creation (unused)                            
*
* Return:
*  None
*
*******************************************************************************/
void Task_Motion(void* pvParameters)
{
    LED_flag = false;
    
    (void)pvParameters;
    /* Variable used to store the return values of Motion Sensor APIs */
    static int8_t motionSensorApiResult;  

    /* Create binary semaphore */
    xSemaphoreI2C = xSemaphoreCreateBinary();

    
    /* Initialize BMI160 Motion Sensor */
    MotionSensor_Init();
    
    // Configure orientation interrupt 
    MotionSensor_ConfigOrientIntr();
        
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    
    vTaskSuspend(NULL);
}

/*******************************************************************************
* Function Name: static void Orientation_Interrupt(void)
********************************************************************************
*
* Summary:
*  Interrupt service routine for orientation interrupt
* 
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void Orientation_Interrupt(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /* Clear any pending interrupts */
    Cy_GPIO_ClearInterrupt(P13_0_PORT, P13_0_NUM );
    NVIC_ClearPendingIRQ(SysInt_OrientINT_cfg.intrSrc);
    Cy_GPIO_Write(P0_3_PORT, P0_3_NUM, 0);
    LED_flag = true;

}

/*******************************************************************************
* Function Name: static int8_t MotionSensor_UpdateOrientation(orientation_t 
*														*orientationResult)
********************************************************************************
*
* Summary:
*  Updates orientation status to one of the 6 types, see 'orientation_t'.
*  This functions detects which axis is most perpendicular to ground by
*  looking at the absolute value of acceleration in that axis. The sign
*  of the acceleration signifies whether the axis is facing the ground 
*  or the opposite. 
*
* Parameters:
*  orientation_t *: Address of the variable that stores orientation information
*
* Return:
*  Returns the error status, a non-zero value indicates an error. 
*
*******************************************************************************/
static int8_t MotionSensor_UpdateOrientation(orientation_t *orientationResult)
{
    /* Structure that stores accelerometer data */
    struct bmi160_sensor_data accel;
    /* Variable used to store the return values of BMI160 APIs */
    int8_t rslt = BMI160_OK;
    /* Local variable used to store accelerometer data */
    uint16_t absX, absY, absZ;
    
    /* Read x, y, z components of acceleration */
    rslt = bmi160_get_sensor_data(BMI160_ACCEL_SEL, &accel, NULL, &sensor);
    
    /* Get the absolute value of accelerations */
    absX = abs(accel.x);
    absY = abs(accel.y);
    absZ = abs(accel.z);
        
    /* Z axis (perpendicular to face of the display) is most aligned with gravity */
    if ((absZ > absX) && (absZ > absY))
    {
        if (accel.z < 0) 
        {
            /* Display faces down (towards the ground) */
            *orientationResult = ORIENTATION_DISP_DOWN;  
        }
        else 
        {
            /* Display faces up (towards the sky/ceiling) */
            *orientationResult = ORIENTATION_DISP_UP;
        }
    }
    /* Y axis (parallel with shorter edge of board) is most aligned with gravity */
    else if ((absY > absX) && (absY > absZ))
    {
        if (accel.y > 0)
        {
            /* Display has an inverted landscape orientation */
            *orientationResult = ORIENTATION_BOTTOM_EDGE;
        }
        else
        {
            /* Display has landscape orientation */
            *orientationResult = ORIENTATION_TOP_EDGE;
        }
    }
    else /* X axis (parallel with longer edge of board) is most aligned with gravity */
    {
        if (accel.x < 0) 
        {
            /* Display has an inverted portrait orientation */
            *orientationResult = ORIENTATION_RIGHT_EDGE;
        }
        else 
        {
            /* Display has portrait orientation */
            *orientationResult = ORIENTATION_LEFT_EDGE;
        }
    }
	return rslt;
}

/*******************************************************************************
* Function Name: static int8_t MotionSensor_ConfigOrientIntr(void)
********************************************************************************
*
* Summary:
*  Configures the motion sensor to detect change in orientation. This functions 
*  maps INT2 to provide a pulse on orientation change and configures the active 
*  level and pulse width.
* 
* Parameters:
*  None
*
* Return:
*  Returns the error status, a non-zero value indicates an error. 
*
*******************************************************************************/
static int8_t MotionSensor_ConfigOrientIntr(void)
{
    /* Structure for storing interrupt configuration */
    struct bmi160_int_settg int_config;
    /* Variable used to store the return values of BMI160 APIs */
    uint8_t rslt = BMI160_OK;
    
    /* Map the step interrupt to INT1 pin */
    int_config.int_channel = BMI160_INT_CHANNEL_2;

    /* Select the Interrupt type Step Detector interrupt */
    int_config.int_type = BMI160_ACC_ORIENT_INT;
    
    /* Interrupt pin configuration */
    /* Enabling interrupt pins to act as output pin */
    int_config.int_pin_settg.output_en = BMI160_ENABLE;
    /*Choosing push-pull mode for interrupt pin */
    int_config.int_pin_settg.output_mode = BMI160_DISABLE;
    /* Choosing active High output */
    int_config.int_pin_settg.output_type = BMI160_ENABLE;
    /* Choosing edge triggered output */
    int_config.int_pin_settg.edge_ctrl = BMI160_ENABLE;
    /* Disabling interrupt pin to act as input */
    int_config.int_pin_settg.input_en = BMI160_DISABLE;
    /* 2.5 millisecond latched output */
    int_config.int_pin_settg.latch_dur =BMI160_LATCH_DUR_2_5_MILLI_SEC;
    
    /* Interrupt type configuration */
    /* No exchange axis */
    int_config.int_type_cfg.acc_orient_int.axes_ex = 1;
    /* Set orientation blocking */
    int_config.int_type_cfg.acc_orient_int.orient_blocking = 0; 
    /* Set orientation hysteresis */
    int_config.int_type_cfg.acc_orient_int.orient_hyst = 2;
    /* Set orientation interrupt mode */ 
    int_config.int_type_cfg.acc_orient_int.orient_mode = 0;
    /* Set orientation interrupt theta */
    int_config.int_type_cfg.acc_orient_int.orient_theta = 0;
    /* Enable orientation */
    int_config.int_type_cfg.acc_orient_int.orient_en = 1;
    /* Enable orientation interrupt */
    int_config.int_type_cfg.acc_orient_int.orient_ud_en = 1;
    
    /* Set the Step Detector interrupt */
    rslt = bmi160_set_int_config(&int_config, &sensor);
    
    /* Initialize and enable Orientation Interrupt*/
    Cy_SysInt_Init(&SysInt_OrientINT_cfg, Orientation_Interrupt);
    NVIC_EnableIRQ(SysInt_OrientINT_cfg.intrSrc);
    
    return rslt;
}


/*******************************************************************************
* Function Name: static int8_t MotionSensor_Init(void)
********************************************************************************
*
* Summary: 
*  Initializes the motion sensor. This initializes the driver, resets the chip
*  and checks connection with the sensor.
*
* Parameters:
*  None
*
* Return:
*  Returns the error status, a non-zero value indicates an error. An error indicates 
*  failure in communicating with the motion sensor.
*
*******************************************************************************/

static int8_t MotionSensor_Init(void)
{
    /* Variable used to store the return values of BMI160 APIs */
    uint8_t rslt        = BMI160_OK;
    
    /* Start the I2C master interface for BMI160 motion sensor */
    I2Cm_Start();
    /* Register interrupt callback */
    I2Cm_RegisterEventCallback(I2C_Callback);
    
    /* Sensor configurations */
    sensor.id           = BMI160_I2C_ADDR;
    sensor.interface    = BMI160_I2C_INTF;
    sensor.read         = (bmi160_com_fptr_t)I2C_ReadBytes;
    sensor.write        = (bmi160_com_fptr_t)I2C_WriteBytes;
    sensor.delay_ms     = vTaskDelay;
    
    /* Initialize BNI160 sensor */
    rslt += bmi160_init(&sensor);
        
    if(rslt == BMI160_OK) /* BMI160 initialization successful */
    {
        /* Select the Output data rate, range of accelerometer sensor */
        sensor.accel_cfg.odr    = BMI160_ACCEL_ODR_50HZ;
        sensor.accel_cfg.range  = BMI160_ACCEL_RANGE_4G;
        sensor.accel_cfg.bw     = BMI160_ACCEL_BW_NORMAL_AVG4;

        /* Select the power mode of accelerometer sensor */
        sensor.accel_cfg.power  = BMI160_ACCEL_NORMAL_MODE;

        /* Select the Output data rate, range of Gyroscope sensor */
        sensor.gyro_cfg.odr     = BMI160_GYRO_ODR_3200HZ;
        sensor.gyro_cfg.range   = BMI160_GYRO_RANGE_2000_DPS;
        sensor.gyro_cfg.bw      = BMI160_GYRO_BW_NORMAL_MODE;

        /* Select the power mode of Gyroscope sensor */
        sensor.gyro_cfg.power   = BMI160_GYRO_NORMAL_MODE; 

        /* Set the sensor configuration */
        rslt = bmi160_set_sens_conf(&sensor);
    }
    return rslt;
}

/* [] END OF FILE */
