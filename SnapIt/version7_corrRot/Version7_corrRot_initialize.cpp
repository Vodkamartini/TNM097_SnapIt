/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Version7_corrRot_initialize.cpp
 *
 * Code generation for function 'Version7_corrRot_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "Version7_corrRot_initialize.h"
#include "Version7_corrRot_data.h"

/* Function Definitions */
void Version7_corrRot_initialize()
{
  rt_InitInfAndNaN(8U);
  omp_init_nest_lock(&emlrtNestLockGlobal);
}

/* End of code generation (Version7_corrRot_initialize.cpp) */
