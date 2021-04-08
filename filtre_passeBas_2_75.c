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
#include "filtre_passeBas_2_75.h"

#define TEST_LENGTH_SAMPLES  1000
#define BLOCK_SIZE            100
#define NUM_TAPS              10

extern uint32 testInput_f32_05[TEST_LENGTH_SAMPLES];
extern uint32 refOutput[TEST_LENGTH_SAMPLES];

static uint32 testOutput[TEST_LENGTH_SAMPLES];
static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];

uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = TEST_LENGTH_SAMPLES/BLOCK_SIZE;
float32_t  snr;


void filtre_PB_BPM(uint32 signal[]){
    const float32_t firCoeffs32PasseBasBPM[NUM_TAPS] = {0.0158592579480012f, 0.0375688912986410f, 0.0928281442294643f,	0.156121656005195f,	0.197622050518699f,	0.197622050518699f,	0.156121656005195f,	0.0928281442294643f,	0.0375688912986410f,	0.0158592579480012f};
      uint32_t i;
    arm_fir_instance_f32 S;
    uint32 *inputF32;
    float32_t *outputF32;
    float32_t testOutput_2[TEST_LENGTH_SAMPLES];
  
  inputF32 = &signal[0];
  outputF32 = &testOutput_2[0];
  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32PasseBasBPM[0], &firStateF32[0], blockSize);
  /* ----------------------------------------------------------------------
  ** Call the FIR process function for every blockSize samples
  ** ------------------------------------------------------------------- */
  for(i=0; i < numBlocks; i++)
  {
    arm_fir_f32(&S, (float32_t*)inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
  } 
}
/* [] END OF FILE */
