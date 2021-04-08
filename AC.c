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
#include "AC.h"

uint32 AC(uint32 signal[]){
    uint32 AC = 0;
    float max_AC = 0;
    uint32_t  indexmax_AC = 0;
    float min_AC = 0;
    uint32_t  indexmin_AC = 0;
    int k = 0;
    float AC_1000[1000] = {};
    
        for(int i=0; i<1000; i++){
            AC_1000[i] =signal[k];
            k++;
            }
        arm_max_f32(&AC_1000[0], 1000, &max_AC, &indexmax_AC);
        arm_min_f32(&AC_1000[0], 1000, &min_AC, &indexmin_AC);
        AC = max_AC - min_AC;
        return AC;

}

/* [] END OF FILE */
