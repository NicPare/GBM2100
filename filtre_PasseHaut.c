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
#include "filtre_PasseHaut.h"


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


void filtre_PH(uint32 signal[]){
    const float32_t firCoeffs32PasseHaut[NUM_TAPS] = {0.0161832121486980f, 0.0379660801325973f, 0.0931317312346599f, 0.155878780222433f, 0.196840196261612f, 0.196840196261612f, 0.155878780222433f, 0.0931317312346599f, 0.0379660801325973f, 0.0161832121486980};
    uint32_t i;
    arm_fir_instance_f32 S;
    uint32 *inputF32;
    float32_t *outputF32;
    float32_t testOutput_05[TEST_LENGTH_SAMPLES];
  
  inputF32 = &signal[0];
  outputF32 = &testOutput_05[0];
  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32PasseHaut[0], &firStateF32[0], blockSize);
  /* ----------------------------------------------------------------------
  ** Call the FIR process function for every blockSize samples
  ** ------------------------------------------------------------------- */
  for(i=0; i < numBlocks; i++)
  {
    arm_fir_f32(&S, (float32_t*)inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
  }
}
/* [] END OF FILE */
