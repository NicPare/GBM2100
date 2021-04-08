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
#include "maximum.h"

 uint32 max[50]={};
 uint32 indice[50]={};

uint32 maximum(uint32 signal[],uint32 max[], uint32 indice[]){
    int j= 0;
    for (int i=0; i<1000; i++){
        if(signal[i]> signal[i-1] && signal[i]> signal[i+1]){
            max[j] = signal[i];
            indice[j] = i;
            j++;
        }
    }
}

/* [] END OF FILE */
