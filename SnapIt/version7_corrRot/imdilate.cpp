/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imdilate.cpp
 *
 * Code generation for function 'imdilate'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "imdilate.h"
#include "Version7_corrRot_emxutil.h"
#include "Version7_corrRot_data.h"
#include "libmwmorphop_flat_tbb.h"

/* Function Definitions */
void imdilate(const emxArray_real_T *A, emxArray_real_T *B)
{
  int i46;
  double asizeT[3];
  double nsizeT[2];
  i46 = B->size[0] * B->size[1] * B->size[2];
  B->size[0] = A->size[0];
  B->size[1] = A->size[1];
  B->size[2] = A->size[2];
  emxEnsureCapacity_real_T(B, i46);
  asizeT[0] = A->size[0];
  asizeT[1] = A->size[1];
  asizeT[2] = A->size[2];
  nsizeT[0] = 3.0;
  nsizeT[1] = 3.0;
  dilate_flat_real64_tbb(&A->data[0], asizeT, 2.0, bv0, nsizeT, 2.0, &B->data[0]);
}

/* End of code generation (imdilate.cpp) */
