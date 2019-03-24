/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * bsxfun.cpp
 *
 * Code generation for function 'bsxfun'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "bsxfun.h"
#include "Version7_corrRot_emxutil.h"

/* Function Definitions */
void bsxfun(const emxArray_int32_T *a, emxArray_int32_T *c)
{
  int csz_idx_0;
  int i25;
  int acoef;
  int k;
  csz_idx_0 = a->size[0];
  i25 = c->size[0] * c->size[1];
  c->size[0] = csz_idx_0;
  c->size[1] = 162;
  emxEnsureCapacity_int32_T(c, i25);
  if (c->size[0] != 0) {
    for (csz_idx_0 = 0; csz_idx_0 < 162; csz_idx_0++) {
      acoef = (a->size[0] != 1);
      i25 = c->size[0] - 1;
      for (k = 0; k <= i25; k++) {
        c->data[k + c->size[0] * csz_idx_0] = a->data[acoef * k] + csz_idx_0;
      }
    }
  }
}

/* End of code generation (bsxfun.cpp) */
