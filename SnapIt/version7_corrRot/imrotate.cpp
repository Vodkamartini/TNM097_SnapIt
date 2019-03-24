/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imrotate.cpp
 *
 * Code generation for function 'imrotate'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "imrotate.h"
#include "Version7_corrRot_emxutil.h"

/* Function Definitions */
void b_imrotate(const emxArray_real_T *varargin_1, emxArray_real_T *B)
{
  unsigned int sizeA_idx_0;
  int i38;
  unsigned int sizeA_idx_1;
  int j;
  int i39;
  int i;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    i38 = B->size[0] * B->size[1];
    B->size[0] = varargin_1->size[0];
    B->size[1] = varargin_1->size[1];
    emxEnsureCapacity_real_T(B, i38);
    j = varargin_1->size[0] * varargin_1->size[1];
    for (i38 = 0; i38 < j; i38++) {
      B->data[i38] = varargin_1->data[i38];
    }
  } else {
    sizeA_idx_0 = (unsigned int)varargin_1->size[0];
    sizeA_idx_1 = (unsigned int)varargin_1->size[1];
    i38 = B->size[0] * B->size[1];
    B->size[0] = (int)sizeA_idx_0;
    B->size[1] = (int)sizeA_idx_1;
    emxEnsureCapacity_real_T(B, i38);
    i38 = (int)sizeA_idx_1;
    for (j = 0; j < i38; j++) {
      i39 = (int)sizeA_idx_0;
      for (i = 0; i < i39; i++) {
        B->data[i + B->size[0] * j] = varargin_1->data[(((int)sizeA_idx_0 - i) +
          varargin_1->size[0] * (((int)sizeA_idx_1 - j) - 1)) - 1];
      }
    }
  }
}

void c_imrotate(const emxArray_real_T *varargin_1, emxArray_real_T *B)
{
  int m;
  int i40;
  int n;
  int sizeB_idx_0;
  int sizeB_idx_1;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    i40 = B->size[0] * B->size[1];
    B->size[0] = varargin_1->size[0];
    B->size[1] = varargin_1->size[1];
    emxEnsureCapacity_real_T(B, i40);
    sizeB_idx_0 = varargin_1->size[0] * varargin_1->size[1];
    for (i40 = 0; i40 < sizeB_idx_0; i40++) {
      B->data[i40] = varargin_1->data[i40];
    }
  } else {
    m = varargin_1->size[0] - 1;
    n = varargin_1->size[1];
    sizeB_idx_0 = varargin_1->size[1];
    sizeB_idx_1 = varargin_1->size[0];
    i40 = B->size[0] * B->size[1];
    B->size[0] = sizeB_idx_0;
    B->size[1] = sizeB_idx_1;
    emxEnsureCapacity_real_T(B, i40);
    for (sizeB_idx_0 = 0; sizeB_idx_0 < n; sizeB_idx_0++) {
      for (sizeB_idx_1 = 0; sizeB_idx_1 <= m; sizeB_idx_1++) {
        B->data[sizeB_idx_0 + B->size[0] * sizeB_idx_1] = varargin_1->data[(m -
          sizeB_idx_1) + varargin_1->size[0] * sizeB_idx_0];
      }
    }
  }
}

void imrotate(const emxArray_real_T *varargin_1, emxArray_real_T *B)
{
  int m;
  int i37;
  int n;
  int sizeB_idx_0;
  int sizeB_idx_1;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    i37 = B->size[0] * B->size[1];
    B->size[0] = varargin_1->size[0];
    B->size[1] = varargin_1->size[1];
    emxEnsureCapacity_real_T(B, i37);
    sizeB_idx_0 = varargin_1->size[0] * varargin_1->size[1];
    for (i37 = 0; i37 < sizeB_idx_0; i37++) {
      B->data[i37] = varargin_1->data[i37];
    }
  } else {
    m = varargin_1->size[0];
    n = varargin_1->size[1] - 1;
    sizeB_idx_0 = varargin_1->size[1];
    sizeB_idx_1 = varargin_1->size[0];
    i37 = B->size[0] * B->size[1];
    B->size[0] = sizeB_idx_0;
    B->size[1] = sizeB_idx_1;
    emxEnsureCapacity_real_T(B, i37);
    for (sizeB_idx_0 = 0; sizeB_idx_0 <= n; sizeB_idx_0++) {
      for (sizeB_idx_1 = 0; sizeB_idx_1 < m; sizeB_idx_1++) {
        B->data[sizeB_idx_0 + B->size[0] * sizeB_idx_1] = varargin_1->
          data[sizeB_idx_1 + varargin_1->size[0] * (n - sizeB_idx_0)];
      }
    }
  }
}

/* End of code generation (imrotate.cpp) */
