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
#include "filtre_passeBas_5.h"

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

void filtre_PB_AC(uint32 signal[]){
 const float32_t firCoeffs32PasseBasAC[NUM_TAPS] = {0.0150969213546239f, 0.0366236533871337f, 0.0920956254220551f,	0.156693587173906f,	0.199490212662281f,	0.199490212662281f,	0.156693587173906f,	0.0920956254220551f,	0.0366236533871337f,	0.0150969213546239f};
    uint32_t i;
    arm_fir_instance_f32 S;
    uint32 *inputF32;
    float32_t *outputF32;
    float32_t testOutput_5[TEST_LENGTH_SAMPLES];
  
  inputF32 = &signal[0];
  outputF32 = &testOutput_5[0];
  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32PasseBasAC[0], &firStateF32[0], blockSize);
  /* ----------------------------------------------------------------------
  ** Call the FIR process function for every blockSize samples
  ** ------------------------------------------------------------------- */
  for(i=0; i < numBlocks; i++)
  {
    arm_fir_f32(&S, (float32_t*)inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
  }  
}
/* [] END OF FILE */
