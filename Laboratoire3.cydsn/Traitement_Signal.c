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
#include "master.h"

 

#define TEST_LENGTH_SAMPLES  1000
#define BLOCK_SIZE            1
#define NUM_TAPS              51

static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];

uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = TEST_LENGTH_SAMPLES/BLOCK_SIZE;


/*******************************************************************************
* Function Name: void filtre_6(float32 signal[], float32 signal_filtre[])

********************************************************************************
*
* Summary: 
* Cette fonction agit comme filtre passe-bas de 6 Hz pour filtrer un signal d’entrée. 
* Cette fonction est basée sur l’exemple qu’on retrouve à l’adresse suivante : 
* https://www.keil.com/pack/doc/CMSIS/DSP/html/group__FIRLPF.html

*Parameters:
* float32 signal[] : le signal à filtrer
* float32 signal_filtre[] : vecteur qui contiendra le signal filtré

* Return:
* None
*
* Side Effects:
* Nécessite plusieurs coefficients
*******************************************************************************/
void filtre_6(float32 signal[], float32 signal_filtre[]){
    
    const float32_t firCoeffs32PasseBasBPM[NUM_TAPS] = {0.0000000000f, 0.0004075633f, 0.0008932012f, 0.0014675649f, 0.0020672200f, 0.0025361043f, 0.0026372657f, 0.0020986258f, 0.0006875722f, -0.0016995698f, -0.0049535090f, -0.0086959251f, -0.0122709651f, -0.0147960057f, -0.0152718668f, -0.0127397517f, -0.0064606125f, 0.0039149652f, 0.0182199792f, 0.0357159540f, 0.0551271230f, 0.0747660098f, 0.0927358341f, 0.1071803126f, 0.1165414494f, 0.1197829218f, 0.1165414494f, 0.1071803126f, 0.0927358341f, 0.0747660098f, 0.0551271230f, 0.0357159540f, 0.0182199792f, 0.0039149652f, -0.0064606125f, -0.0127397517f, -0.0152718668f, -0.0147960057f, -0.0122709651f, -0.0086959251f, -0.0049535090f, -0.0016995698f, 0.0006875722f, 0.0020986258f, 0.0026372657f, 0.0025361043f, 0.0020672200f, 0.0014675649f, 0.0008932012f, 0.0004075633f, 0.0000000000f};

    uint32_t i;
    arm_fir_instance_f32 S;
    float32_t *inputF32;
    float32_t *outputF32;

  
  inputF32 = &signal[0];
  outputF32 = &signal_filtre[0];
  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32PasseBasBPM[0], &firStateF32[0], blockSize);
  /* ----------------------------------------------------------------------
  ** Call the FIR process function for every blockSize samples
  ** ------------------------------------------------------------------- */
  for(i=0; i < numBlocks; i++)
  {
    arm_fir_f32(&S, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
  } 
}


    float32 AC_valeur;
    float max_AC;
    uint32_t  indexmax_AC;
    float min_AC;
    uint32_t  indexmin_AC;
    int k;
    float AC_1000[1000] = {};
    
    
/*******************************************************************************
* Function Name: float32 AC(float32 signal[])
********************************************************************************
*
* Summary: 
* Cette fonction calcule le maximum ainsi que le minimum d’un signal donné en paramètre. 
* Cette fonction calcule par la suite la différence du max et du min pour obtenir l’amplitude du 
* signal et ainsi la composante AC. Elle utilise les valeurs 500 à 1000 du vecteur pour éviter les données 
* erratiques dûes au filtre.
    
* Parameters:
* float32 signal[] : les données dont on veut trouver l'amplitude
* 
* Return:
* float32 AC_valeur : l'amplitude du signal
*
* Side Effects:
* None   
*******************************************************************************/

float32 AC(float32 signal[]){
    AC_valeur = 0;
    max_AC = 0;
    indexmax_AC = 0;
    min_AC = 0;
    indexmin_AC = 0;
    k = 0;
  
    
    arm_max_f32(&signal[500], 500, &max_AC, &indexmax_AC);
    arm_min_f32(&signal[500], 500, &min_AC, &indexmin_AC);
    AC_valeur = max_AC - min_AC;
    return AC_valeur;

}



float32 DC;
float32 moyenne_DC;

/*******************************************************************************
* Function Name: float32 DC_sum(float32 signal[])
********************************************************************************
*
* Summary: 
* Cette fonction calcule la moyenne du signal donné en paramètre pour en retirer la composante DC. 
    
* Parameters:
* float32 signal[] : les données dont on veut trouver l'amplitude
* 
* Return:
* float32 AC_valeur : l'amplitude du signal
*
* Side Effects:
* None   
*******************************************************************************/

float32 DC_sum(float32 signal[]){
     DC=0;
     moyenne_DC = 0;

     for(int i=500; i<1000; i++)
     {
         DC += signal[i];
     }
     moyenne_DC = DC/500;
     return moyenne_DC;
}



/*******************************************************************************
* Function Name: void traitement_task(void*pvParameters)
********************************************************************************
*
* Summary: 
* Cette tâche appelle le traitement des données reçues du capteur MAX30102,
* en filtrant d'abord les signaux, puis en retirant les composantes AC et DC, et finalement en 
* calculant les valeurs de SpO2 et HR.
* 
* Parameters:
* void* pvParameters
* 
* Return:
* None
*
* Side Effects:
* None  
* 
*******************************************************************************/
    
void traitement_task(void* pvParameters)
{
    
    (void)pvParameters;

    R = 0 ;
    S = 0;
    DC_R = 0;
    DC_IF = 0;
    AC_R = 0;
    DC_IF = 0;
    
 
   
    
    for (;;)
    {
        
        if (currentpage == PAGE_SIGNAL_IR || currentpage == PAGE_SIGNAL_R)
        {
            
            if (read_flag_MAX)
            {
                //Filtrage passe-bas des signaux 
                filtre_6(red_data, signal_R);
                filtre_6(ir_data, signal_IF);

                //Extraction du courant DC moyen
                DC_R = DC_sum(signal_R);
                DC_IF = DC_sum(signal_IF);
    
                //Obtention des signaux AC
                for(int i=0; i<1000; i++)
                {
                    signal_AC_R[i] = signal_R[i] - DC_R;
                    signal_AC_IF[i] = signal_IF[i] - DC_IF;
                }
            
                //Extraction du courant AC moyen
                AC_R = AC(signal_AC_R);
                AC_IF = AC(signal_AC_IF);
    
                //Calcul du SpO2
                R = (AC_R/DC_R)/(AC_IF/DC_IF);
                S = -12.5*R + 105;
            

                //Routine de test du SpO2
                /*char displayStr[50];
                sprintf(displayStr,"____%i,____",(int)(1000*R));
                UART_PutString(displayStr);*/


                float32 indice[4]={};
                BPM = 0;
                int j= 0;
               
                //Positionnement des pics d'amplitude
                for (int i=500; i<1000; i++)
                {
                    if(signal_R[i]> signal_R[i-1] && signal_R[i]> signal_R[i+1] && signal_R[i]> signal_R[i-5] && signal_R[i]> signal_R[i+5] && signal_R[i]> signal_R[i-20] && signal_R[i]> signal_R[i+20])
                    {
                        indice[j] = i;
                        j++;
                    } 
                    if(j==5)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                //Calcul du HR
                BPM += (60*100)/(indice[1]-indice[0]);
                BPM += (60*100)/(indice[2]-indice[1]);
                BPM += (60*100)/(indice[3]-indice[2]);
                BPM = BPM/3;
                vTaskDelay(pdMS_TO_TICKS(2000));
            

            
            }
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        
        read_flag_MAX = false;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
 
}

/* [] END OF FILE */
