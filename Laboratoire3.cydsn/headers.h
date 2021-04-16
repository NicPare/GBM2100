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

    
    
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include <stdio.h>
#include "task.h"
#include "semphr.h"

#include "GUI.h"
#include "pervasive_eink_hardware_driver.h"
#include <stdlib.h>
#include "cy_eink_library.h"
#include "LCDConf.h"
#include "queue.h"
//#include "touch.h"
//#include "global_variables.h"
#include "bmi160.h"
#include "bmi160_defs.h"
#include "i2cm_support.h"
#include "master.h"
#include "MAX30102_functions.h"
#include "project.h"
#include <arm_math.h>
#include <core_cm4.h>
#include <string.h>

/* [] END OF FILE */
