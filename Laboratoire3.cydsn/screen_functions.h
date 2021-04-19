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
#include <stdlib.h>
#include "cy_eink_library.h"
#include "LCDConf.h"




void UpdateDisplay(cy_eink_update_t updateMethod, bool powerCycle);
void ClearScreen();
void WaitforSwitchPressAndRelease();
