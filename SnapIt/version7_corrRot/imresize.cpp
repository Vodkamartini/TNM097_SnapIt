/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imresize.cpp
 *
 * Code generation for function 'imresize'
 *
 */

/* Include files */
#include <cmath>
#include <string.h>
#include "rt_nonfinite.h"
#include <math.h>
#include "Version7_corrRot.h"
#include "imresize.h"
#include "Version7_corrRot_emxutil.h"
#include "bsxfun.h"
#include "floor.h"

/* Function Declarations */
static void b_resizeAlongDim(const emxArray_real_T *in_, const emxArray_real_T
  *weights, const emxArray_int32_T *indices, emxArray_real_T *out);
static void contributions(int in_length, double out_length, emxArray_real_T
  *weights, emxArray_int32_T *indices);
static void resizeAlongDim(const emxArray_real_T *in_, const emxArray_real_T
  *weights, const emxArray_int32_T *indices, emxArray_real_T *out);
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */
static void b_resizeAlongDim(const emxArray_real_T *in_, const emxArray_real_T
  *weights, const emxArray_int32_T *indices, emxArray_real_T *out)
{
  emxArray_real_T *in;
  int out_length;
  unsigned int outSize_idx_1;
  int ub_loop;
  int loop_ub;
  int inRInd;
  int pixelIndex;
  int linearInds;
  double sumVal1;
  int outCInd;
  int i27;
  int k;
  emxInit_real_T(&in, 2);
  out_length = weights->size[1];
  outSize_idx_1 = (unsigned int)weights->size[1];
  ub_loop = out->size[0] * out->size[1];
  out->size[0] = in_->size[0];
  out->size[1] = (int)outSize_idx_1;
  emxEnsureCapacity_real_T(out, ub_loop);
  ub_loop = in->size[0] * in->size[1];
  in->size[0] = in_->size[0];
  in->size[1] = in_->size[1];
  emxEnsureCapacity_real_T(in, ub_loop);
  loop_ub = in_->size[0] * in_->size[1];
  for (ub_loop = 0; ub_loop < loop_ub; ub_loop++) {
    in->data[ub_loop] = in_->data[ub_loop];
  }

  ub_loop = in_->size[0];
  ub_loop--;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(pixelIndex,linearInds,sumVal1,outCInd,i27,k)

  for (inRInd = 0; inRInd <= ub_loop; inRInd++) {
    for (outCInd = 0; outCInd < out_length; outCInd++) {
      sumVal1 = 0.0;

      /*  Core - second dimension */
      linearInds = 1 + weights->size[0] * outCInd;
      i27 = weights->size[0];
      for (k = 0; k < i27; k++) {
        pixelIndex = (inRInd + (indices->data[linearInds - 1] - 1) * in->size[0])
          + 1;
        sumVal1 += weights->data[linearInds - 1] * in->data[pixelIndex - 1];
        linearInds++;
      }

      out->data[inRInd + out->size[0] * outCInd] = sumVal1;
    }
  }

  emxFree_real_T(&in);
}

static void contributions(int in_length, double out_length, emxArray_real_T
  *weights, emxArray_int32_T *indices)
{
  emxArray_real_T *y;
  int i24;
  int csz_idx_0;
  emxArray_real_T *u;
  emxArray_real_T *r3;
  emxArray_int32_T *r4;
  emxArray_int32_T *b_indices;
  emxArray_real_T *x;
  emxArray_real_T *absx2;
  int bcoef;
  int k;
  int vstride;
  emxArray_real_T *absx;
  emxArray_int32_T *aux;
  int i;
  double b_k;
  boolean_T copyCols[162];
  boolean_T exitg1;
  unsigned char tmp_data[162];
  unsigned char b_tmp_data[162];

  /*  Contributions, using pixel indices */
  emxInit_real_T(&y, 2);
  if (out_length < 1.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i24 = y->size[0] * y->size[1];
    y->size[0] = 1;
    csz_idx_0 = (int)std::floor(out_length - 1.0);
    y->size[1] = csz_idx_0 + 1;
    emxEnsureCapacity_real_T(y, i24);
    for (i24 = 0; i24 <= csz_idx_0; i24++) {
      y->data[i24] = 1.0 + (double)i24;
    }
  }

  emxInit_real_T(&u, 1);
  i24 = u->size[0];
  u->size[0] = y->size[1];
  emxEnsureCapacity_real_T(u, i24);
  csz_idx_0 = y->size[1];
  for (i24 = 0; i24 < csz_idx_0; i24++) {
    u->data[i24] = y->data[i24] / 0.025 + -19.5;
  }

  emxFree_real_T(&y);
  emxInit_real_T(&r3, 1);
  i24 = r3->size[0];
  r3->size[0] = u->size[0];
  emxEnsureCapacity_real_T(r3, i24);
  csz_idx_0 = u->size[0];
  for (i24 = 0; i24 < csz_idx_0; i24++) {
    r3->data[i24] = u->data[i24] - 80.0;
  }

  emxInit_int32_T(&r4, 1);
  b_floor(r3);
  i24 = r4->size[0];
  r4->size[0] = r3->size[0];
  emxEnsureCapacity_int32_T(r4, i24);
  csz_idx_0 = r3->size[0];
  for (i24 = 0; i24 < csz_idx_0; i24++) {
    r4->data[i24] = (int)r3->data[i24];
  }

  emxFree_real_T(&r3);
  emxInit_int32_T(&b_indices, 2);
  emxInit_real_T(&x, 2);
  emxInit_real_T(&absx2, 2);
  bsxfun(r4, b_indices);
  i24 = absx2->size[0] * absx2->size[1];
  absx2->size[0] = b_indices->size[0];
  absx2->size[1] = 162;
  emxEnsureCapacity_real_T(absx2, i24);
  csz_idx_0 = b_indices->size[0] * b_indices->size[1];
  emxFree_int32_T(&r4);
  for (i24 = 0; i24 < csz_idx_0; i24++) {
    absx2->data[i24] = b_indices->data[i24];
  }

  csz_idx_0 = absx2->size[0];
  bcoef = u->size[0];
  if (csz_idx_0 < bcoef) {
    bcoef = csz_idx_0;
  }

  if (absx2->size[0] == 1) {
    csz_idx_0 = u->size[0];
  } else if (u->size[0] == 1) {
    csz_idx_0 = absx2->size[0];
  } else if (u->size[0] == absx2->size[0]) {
    csz_idx_0 = u->size[0];
  } else {
    csz_idx_0 = bcoef;
  }

  i24 = x->size[0] * x->size[1];
  x->size[0] = csz_idx_0;
  x->size[1] = 162;
  emxEnsureCapacity_real_T(x, i24);
  if (x->size[0] != 0) {
    for (k = 0; k < 162; k++) {
      csz_idx_0 = (u->size[0] != 1);
      bcoef = (absx2->size[0] != 1);
      i24 = x->size[0] - 1;
      for (vstride = 0; vstride <= i24; vstride++) {
        x->data[vstride + x->size[0] * k] = u->data[csz_idx_0 * vstride] -
          absx2->data[bcoef * vstride + absx2->size[0] * k];
      }
    }
  }

  i24 = x->size[0] * x->size[1];
  bcoef = x->size[0] * x->size[1];
  x->size[1] = 162;
  emxEnsureCapacity_real_T(x, bcoef);
  csz_idx_0 = i24 - 1;
  for (i24 = 0; i24 <= csz_idx_0; i24++) {
    x->data[i24] *= 0.025;
  }

  emxInit_real_T(&absx, 2);
  bcoef = x->size[0] * 162;
  i24 = absx->size[0] * absx->size[1];
  absx->size[0] = x->size[0];
  absx->size[1] = 162;
  emxEnsureCapacity_real_T(absx, i24);
  for (k = 0; k < bcoef; k++) {
    absx->data[k] = std::abs(x->data[k]);
  }

  i24 = absx2->size[0] * absx2->size[1];
  absx2->size[0] = absx->size[0];
  absx2->size[1] = 162;
  emxEnsureCapacity_real_T(absx2, i24);
  bcoef = absx->size[0] * 162;
  for (k = 0; k < bcoef; k++) {
    absx2->data[k] = absx->data[k] * absx->data[k];
  }

  i24 = x->size[0] * x->size[1];
  x->size[0] = absx->size[0];
  x->size[1] = 162;
  emxEnsureCapacity_real_T(x, i24);
  bcoef = absx->size[0] * 162;
  for (k = 0; k < bcoef; k++) {
    x->data[k] = rt_powd_snf(absx->data[k], 3.0);
  }

  i24 = absx2->size[0] * absx2->size[1];
  bcoef = absx2->size[0] * absx2->size[1];
  absx2->size[1] = 162;
  emxEnsureCapacity_real_T(absx2, bcoef);
  csz_idx_0 = i24 - 1;
  for (i24 = 0; i24 <= csz_idx_0; i24++) {
    absx2->data[i24] *= 2.5;
  }

  i24 = x->size[0] * x->size[1];
  bcoef = x->size[0] * x->size[1];
  x->size[1] = 162;
  emxEnsureCapacity_real_T(x, bcoef);
  csz_idx_0 = i24 - 1;
  for (i24 = 0; i24 <= csz_idx_0; i24++) {
    x->data[i24] = 0.025 * (((1.5 * x->data[i24] - absx2->data[i24]) + 1.0) *
      (double)(absx->data[i24] <= 1.0) + (((-0.5 * x->data[i24] + absx2->
      data[i24]) - 4.0 * absx->data[i24]) + 2.0) * (double)((1.0 < absx->
      data[i24]) && (absx->data[i24] <= 2.0)));
  }

  emxFree_real_T(&absx);
  if (x->size[0] == 0) {
    u->size[0] = 0;
  } else {
    vstride = x->size[0];
    i24 = u->size[0];
    u->size[0] = x->size[0];
    emxEnsureCapacity_real_T(u, i24);
    for (csz_idx_0 = 0; csz_idx_0 < vstride; csz_idx_0++) {
      u->data[csz_idx_0] = x->data[csz_idx_0];
    }

    for (k = 0; k < 161; k++) {
      bcoef = (k + 1) * vstride;
      for (csz_idx_0 = 0; csz_idx_0 < vstride; csz_idx_0++) {
        u->data[csz_idx_0] += x->data[bcoef + csz_idx_0];
      }
    }
  }

  i24 = absx2->size[0] * absx2->size[1];
  absx2->size[0] = x->size[0];
  absx2->size[1] = 162;
  emxEnsureCapacity_real_T(absx2, i24);
  csz_idx_0 = x->size[0] * x->size[1];
  for (i24 = 0; i24 < csz_idx_0; i24++) {
    absx2->data[i24] = x->data[i24];
  }

  csz_idx_0 = u->size[0];
  bcoef = x->size[0];
  if (csz_idx_0 < bcoef) {
    bcoef = csz_idx_0;
  }

  if (u->size[0] == 1) {
    csz_idx_0 = x->size[0];
  } else if (x->size[0] == 1) {
    csz_idx_0 = u->size[0];
  } else if (x->size[0] == u->size[0]) {
    csz_idx_0 = x->size[0];
  } else {
    csz_idx_0 = bcoef;
  }

  i24 = x->size[0] * x->size[1];
  x->size[0] = csz_idx_0;
  x->size[1] = 162;
  emxEnsureCapacity_real_T(x, i24);
  if (x->size[0] != 0) {
    for (k = 0; k < 162; k++) {
      csz_idx_0 = (absx2->size[0] != 1);
      bcoef = (u->size[0] != 1);
      i24 = x->size[0] - 1;
      for (vstride = 0; vstride <= i24; vstride++) {
        x->data[vstride + x->size[0] * k] = absx2->data[csz_idx_0 * vstride +
          absx2->size[0] * k] / u->data[bcoef * vstride];
      }
    }
  }

  emxFree_real_T(&absx2);
  emxFree_real_T(&u);
  emxInit_int32_T(&aux, 2);

  /*  Create the auxiliary matrix: */
  csz_idx_0 = in_length << 1;
  i24 = aux->size[0] * aux->size[1];
  aux->size[0] = 1;
  aux->size[1] = csz_idx_0;
  emxEnsureCapacity_int32_T(aux, i24);
  aux->data[0] = 1;
  aux->data[in_length] = in_length;
  for (i = 2; i <= in_length; i++) {
    aux->data[i - 1] = aux->data[i - 2] + 1;
    i24 = in_length + i;
    aux->data[i24 - 1] = aux->data[i24 - 2] - 1;
  }

  /*  Mirror the out-of-bounds indices using mod: */
  i24 = b_indices->size[0] * 162;
  for (i = 0; i < i24; i++) {
    b_k = (double)b_indices->data[i] - 1.0;
    if ((double)b_indices->data[i] - 1.0 == 0.0) {
      b_k = 0.0;
    } else {
      if (csz_idx_0 != 0) {
        b_k = std::fmod((double)b_indices->data[i] - 1.0, (double)csz_idx_0);
        if (b_k == 0.0) {
          b_k = 0.0;
        } else {
          if ((double)b_indices->data[i] - 1.0 < 0.0) {
            b_k += (double)csz_idx_0;
          }
        }
      }
    }

    b_indices->data[i] = aux->data[(int)b_k];
  }

  emxFree_int32_T(&aux);
  memset(&copyCols[0], 0, 162U * sizeof(boolean_T));
  csz_idx_0 = 0;
  bcoef = -1;
  for (i = 0; i < 162; i++) {
    vstride = csz_idx_0 + x->size[0];
    k = csz_idx_0;
    csz_idx_0 += x->size[0];
    bcoef++;
    exitg1 = false;
    while ((!exitg1) && (k + 1 <= vstride)) {
      if ((x->data[k] == 0.0) || rtIsNaN(x->data[k])) {
        k++;
      } else {
        copyCols[bcoef] = true;
        exitg1 = true;
      }
    }
  }

  vstride = 0;
  for (i = 0; i < 162; i++) {
    if (copyCols[i]) {
      vstride++;
    }
  }

  csz_idx_0 = 0;
  for (i = 0; i < 162; i++) {
    if (copyCols[i]) {
      tmp_data[csz_idx_0] = (unsigned char)(i + 1);
      csz_idx_0++;
    }
  }

  csz_idx_0 = x->size[0];
  i24 = weights->size[0] * weights->size[1];
  weights->size[0] = vstride;
  weights->size[1] = csz_idx_0;
  emxEnsureCapacity_real_T(weights, i24);
  for (i24 = 0; i24 < csz_idx_0; i24++) {
    for (bcoef = 0; bcoef < vstride; bcoef++) {
      weights->data[bcoef + weights->size[0] * i24] = x->data[i24 + x->size[0] *
        (tmp_data[bcoef] - 1)];
    }
  }

  emxFree_real_T(&x);
  vstride = 0;
  for (i = 0; i < 162; i++) {
    if (copyCols[i]) {
      vstride++;
    }
  }

  csz_idx_0 = 0;
  for (i = 0; i < 162; i++) {
    if (copyCols[i]) {
      b_tmp_data[csz_idx_0] = (unsigned char)(i + 1);
      csz_idx_0++;
    }
  }

  csz_idx_0 = b_indices->size[0];
  i24 = indices->size[0] * indices->size[1];
  indices->size[0] = vstride;
  indices->size[1] = csz_idx_0;
  emxEnsureCapacity_int32_T(indices, i24);
  for (i24 = 0; i24 < csz_idx_0; i24++) {
    for (bcoef = 0; bcoef < vstride; bcoef++) {
      indices->data[bcoef + indices->size[0] * i24] = b_indices->data[i24 +
        b_indices->size[0] * (b_tmp_data[bcoef] - 1)];
    }
  }

  emxFree_int32_T(&b_indices);
}

static void resizeAlongDim(const emxArray_real_T *in_, const emxArray_real_T
  *weights, const emxArray_int32_T *indices, emxArray_real_T *out)
{
  emxArray_real_T *in;
  int out_length;
  unsigned int outSize_idx_0;
  int ub_loop;
  int loop_ub;
  int inCInd;
  int linearInds;
  double sumVal1;
  int outRInd;
  int i26;
  int k;
  emxInit_real_T(&in, 2);
  out_length = weights->size[1];
  outSize_idx_0 = (unsigned int)weights->size[1];
  ub_loop = out->size[0] * out->size[1];
  out->size[0] = (int)outSize_idx_0;
  out->size[1] = in_->size[1];
  emxEnsureCapacity_real_T(out, ub_loop);
  ub_loop = in->size[0] * in->size[1];
  in->size[0] = in_->size[0];
  in->size[1] = in_->size[1];
  emxEnsureCapacity_real_T(in, ub_loop);
  loop_ub = in_->size[0] * in_->size[1];
  for (ub_loop = 0; ub_loop < loop_ub; ub_loop++) {
    in->data[ub_loop] = in_->data[ub_loop];
  }

  ub_loop = (int)((double)(in_->size[0] * in_->size[1]) / (double)in_->size[0]);
  ub_loop--;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(linearInds,sumVal1,outRInd,i26,k)

  for (inCInd = 0; inCInd <= ub_loop; inCInd++) {
    for (outRInd = 0; outRInd < out_length; outRInd++) {
      sumVal1 = 0.0;
      linearInds = 1 + weights->size[0] * outRInd;

      /*  Core - first dimension */
      i26 = weights->size[0];
      for (k = 0; k < i26; k++) {
        sumVal1 += weights->data[linearInds - 1] * in->data[(indices->
          data[linearInds - 1] + in->size[0] * inCInd) - 1];
        linearInds++;
      }

      out->data[outRInd + out->size[0] * inCInd] = sumVal1;
    }
  }

  emxFree_real_T(&in);
}

static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d7;
  double d8;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d7 = std::abs(u0);
    d8 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d7 == 1.0) {
        y = 1.0;
      } else if (d7 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d8 == 0.0) {
      y = 1.0;
    } else if (d8 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

void imresize(const emxArray_real_T *Ain, emxArray_real_T *Bout)
{
  double outputSize_idx_0;
  double outputSize_idx_1;
  emxArray_real_T *weights;
  emxArray_int32_T *indices;
  emxArray_real_T *b_weights;
  emxArray_int32_T *b_indices;
  emxArray_real_T *r2;
  outputSize_idx_0 = (double)Ain->size[0] * 0.025;
  outputSize_idx_1 = (double)Ain->size[1] * 0.025;
  outputSize_idx_0 = std::ceil(outputSize_idx_0);
  outputSize_idx_1 = std::ceil(outputSize_idx_1);
  emxInit_real_T(&weights, 2);
  emxInit_int32_T(&indices, 2);
  emxInit_real_T(&b_weights, 2);
  emxInit_int32_T(&b_indices, 2);
  emxInit_real_T(&r2, 2);

  /*  Resize first dimension */
  contributions(Ain->size[0], outputSize_idx_0, weights, indices);

  /*  Resize second dimension */
  contributions(Ain->size[1], outputSize_idx_1, b_weights, b_indices);
  resizeAlongDim(Ain, weights, indices, r2);
  b_resizeAlongDim(r2, b_weights, b_indices, Bout);
  emxFree_real_T(&r2);
  emxFree_int32_T(&b_indices);
  emxFree_real_T(&b_weights);
  emxFree_int32_T(&indices);
  emxFree_real_T(&weights);
}

/* End of code generation (imresize.cpp) */
