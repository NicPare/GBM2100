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
#include "DC.h"

 uint32 DC(uint32 signal[]){
    uint32 DC = 0;

        for(int i=0; i<1000; i++){
            DC = (DC + signal[i])/1000;
        }
        return DC;
}


/* [] END OF FILE */
