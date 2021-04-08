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
#include "spo2.h"
uint32 SPO2(){
    uint32 DC_R = 0;
    uint32 DC_IF = 0;
    uint32 AC_R = 0;
    uint32 AC_IF = 0;
    int k = 1000;
    float max_ACR = 0;
    uint32_t  indexmax_ACR = 0;
    float max_ACIF = 0;
    uint32_t  indexmax_ACIF = 0;
     float min_ACR = 0;
    uint32_t  indexmin_ACR = 0;
    float min_ACIF = 0;
    uint32_t  indexmin_ACIF = 0;
    
    for (int j=6; j<26; j++){
        
       float ACR_250[250] = {};
       float ACIF_250[250] = {};
        
        for(int i=0; i<250; i++){
            
            DC_R = (DC_R + XXX[k])/250   ;
            DC_IF = (DC_IF + XXX[k])/250   ;
            ACR_250[i] =XXX[k];
            ACIF_250[i] = XXX[k];
            k++;
            }
        arm_max_f32(&ACR_250[0], 250, &max_ACR, &indexmax_ACR);
        arm_max_f32(&ACIF_250[0], 250, &max_ACIF, &indexmax_ACIF);
        arm_min_f32(&ACR_250[0], 250, &min_ACR, &indexmin_ACR);
        arm_min_f32(&ACIF_250[0], 250, &min_ACIF, &indexmin_ACIF);
        AC_R = max_ACR - min_ACR;
        AC_IF = max_ACIF - min_ACIF;
        
    }
    
    uint32 R = (AC_R/DC_R)/(AC_IF/DC_IF);
 
}
/* [] END OF FILE */
