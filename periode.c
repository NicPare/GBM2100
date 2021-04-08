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
#include "periode.h"
uint32 indice[50];

uint32 periode(){
       uint32 vecteur_temps[1000];
    uint32 temps_max[50];
    uint32 vecteur_periode[50];
    uint32 periode;
    int j=0;
    for(int i=0; i<1000; i++){
        vecteur_temps[i] = (double)i/(1000-5);
        temps_max[i] = vecteur_temps[indice[j]]; 
        j++;
    }
     for(int i=0; i<sizeof(temps_max); i++){
        vecteur_periode[i] = temps_max[i+1] - temps_max[i];
        periode = (vecteur_periode[i]+ vecteur_periode[i+1])/sizeof(vecteur_periode);
    }
return periode;
   
}

/* [] END OF FILE */
