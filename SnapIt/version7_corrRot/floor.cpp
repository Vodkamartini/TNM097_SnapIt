/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * floor.cpp
 *
 * Code generation for function 'floor'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "floor.h"

/* Function Definitions */
void b_floor(emxArray_real_T *x)
{
  int nx;
  int k;
  nx = x->size[0];
  for (k = 0; k < nx; k++) {
    x->data[k] = std::floor(x->data[k]);
  }
}

/* End of code generation (floor.cpp) */
