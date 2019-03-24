/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * findDirection.cpp
 *
 * Code generation for function 'findDirection'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "findDirection.h"
#include "Version7_corrRot_emxutil.h"
#include "sum.h"
#include "imfilter.h"
#include "imdilate.h"
#include "Version7_corrRot_data.h"
#include "libmwmorphop_flat_tbb.h"
#include "libmwimfilter.h"
#include "libmwippfilter.h"

/* Function Definitions */
double b_findDirection(const emxArray_real_T *subArea)
{
  double direction;
  emxArray_real_T *dilate;
  emxArray_real_T *B;
  int i41;
  double asizeT[3];
  double nsizeT[2];
  int i42;
  int loop_ub;
  emxArray_real_T *b;
  double outSizeT[3];
  boolean_T empty_non_axis_sizes;
  double padSizeT[3];
  int input_sizes_idx_1;
  double connDimsT[2];
  static const boolean_T conn[3] = { true, false, true };

  int sizes_idx_1;
  emxArray_real_T *r7;
  double d5;
  double d6;
  emxArray_real_T *b_B;
  int b_loop_ub;
  int i43;
  int i44;
  emxArray_real_T *c_B;
  emxArray_real_T *d_B;
  int i45;
  double tmp_data[1];
  int tmp_size[3];
  double b_tmp_data[1];
  emxInit_real_T(&dilate, 3);
  emxInit_real_T(&B, 3);

  /*     %% Filters a sub area to determine direction */
  imdilate(subArea, dilate);
  i41 = B->size[0] * B->size[1] * B->size[2];
  B->size[0] = subArea->size[0];
  B->size[1] = subArea->size[1];
  B->size[2] = subArea->size[2];
  emxEnsureCapacity_real_T(B, i41);
  asizeT[0] = subArea->size[0];
  asizeT[1] = subArea->size[1];
  asizeT[2] = subArea->size[2];
  nsizeT[0] = 3.0;
  nsizeT[1] = 3.0;
  erode_flat_real64_tbb(&subArea->data[0], asizeT, 2.0, bv0, nsizeT, 2.0,
                        &B->data[0]);
  i41 = dilate->size[0] * dilate->size[1] * dilate->size[2];
  i42 = dilate->size[0] * dilate->size[1] * dilate->size[2];
  dilate->size[2] = 1;
  emxEnsureCapacity_real_T(dilate, i42);
  loop_ub = i41 - 1;
  for (i41 = 0; i41 <= loop_ub; i41++) {
    dilate->data[i41] -= B->data[i41];
  }

  emxInit_real_T(&b, 3);

  /*  Define filter kernels */
  /*  Filter the sub area with a horizontal kernel and vertical kernel, */
  /*  respectively */
  outSizeT[0] = dilate->size[0];
  asizeT[0] = 0.0;
  outSizeT[1] = dilate->size[1];
  asizeT[1] = 1.0;
  outSizeT[2] = 1.0;
  asizeT[2] = 0.0;
  if ((dilate->size[0] == 0) || (dilate->size[1] == 0)) {
    i41 = b->size[0] * b->size[1] * b->size[2];
    b->size[0] = dilate->size[0];
    b->size[1] = dilate->size[1];
    b->size[2] = 1;
    emxEnsureCapacity_real_T(b, i41);
    loop_ub = dilate->size[0] * dilate->size[1] * dilate->size[2];
    for (i41 = 0; i41 < loop_ub; i41++) {
      b->data[i41] = dilate->data[i41];
    }
  } else {
    b_padImage(dilate, asizeT, B);
    empty_non_axis_sizes = ((int)(unsigned int)outSizeT[0] > 65500);
    if (empty_non_axis_sizes && ((int)(unsigned int)outSizeT[1] > 65500)) {
    } else {
      empty_non_axis_sizes = false;
    }

    i41 = b->size[0] * b->size[1] * b->size[2];
    b->size[0] = (int)outSizeT[0];
    b->size[1] = (int)outSizeT[1];
    b->size[2] = 1;
    emxEnsureCapacity_real_T(b, i41);
    if (!empty_non_axis_sizes) {
      padSizeT[0] = B->size[0];
      asizeT[0] = 1.0;
      padSizeT[1] = B->size[1];
      asizeT[1] = 0.0;
      padSizeT[2] = B->size[2];
      asizeT[2] = -1.0;
      nsizeT[0] = 1.0;
      nsizeT[1] = 3.0;
      ippfilter_real64(&B->data[0], &b->data[0], outSizeT, 2.0, padSizeT, asizeT,
                       nsizeT, false);
    } else {
      padSizeT[0] = B->size[0];
      padSizeT[1] = B->size[1];
      padSizeT[2] = B->size[2];
      nsizeT[0] = 1.0;
      nsizeT[1] = -1.0;
      connDimsT[0] = 1.0;
      connDimsT[1] = 3.0;
      imfilter_real64(&B->data[0], &b->data[0], 3.0, outSizeT, 2.0, padSizeT,
                      nsizeT, 2.0, conn, 2.0, connDimsT, asizeT, 3.0, true,
                      false);
    }
  }

  imfilter(dilate);
  if ((dilate->size[0] != 0) || (dilate->size[1] != 0)) {
    loop_ub = dilate->size[0];
  } else if ((b->size[0] != 0) || (b->size[1] != 0)) {
    loop_ub = b->size[0];
  } else {
    loop_ub = dilate->size[0];
    if (loop_ub <= 0) {
      loop_ub = 0;
    }

    if (b->size[0] > loop_ub) {
      loop_ub = b->size[0];
    }
  }

  empty_non_axis_sizes = (loop_ub == 0);
  if (empty_non_axis_sizes || (dilate->size[0] != 0) || (dilate->size[1] != 0))
  {
    input_sizes_idx_1 = dilate->size[1];
  } else {
    input_sizes_idx_1 = 0;
  }

  if (empty_non_axis_sizes || (b->size[0] != 0) || (b->size[1] != 0)) {
    sizes_idx_1 = b->size[1];
  } else {
    sizes_idx_1 = 0;
  }

  i41 = B->size[0] * B->size[1] * B->size[2];
  B->size[0] = loop_ub;
  B->size[1] = input_sizes_idx_1 + sizes_idx_1;
  B->size[2] = 1;
  emxEnsureCapacity_real_T(B, i41);
  for (i41 = 0; i41 < input_sizes_idx_1; i41++) {
    for (i42 = 0; i42 < loop_ub; i42++) {
      B->data[i42 + B->size[0] * i41] = dilate->data[i42 + loop_ub * i41];
    }
  }

  for (i41 = 0; i41 < sizes_idx_1; i41++) {
    for (i42 = 0; i42 < loop_ub; i42++) {
      B->data[i42 + B->size[0] * (i41 + input_sizes_idx_1)] = b->data[i42 +
        loop_ub * i41];
    }
  }

  emxFree_real_T(&b);

  /*  If the mean value of the horizontal filter is greater than the */
  /*  vertical, we consider the sub area to be horizontal. Otherwise */
  /*  vertical. */
  emxInit_real_T(&r7, 3);
  if (B->data[0] > B->data[1]) {
    /*  If the filter determined that the sub area is horizontal, check */
    /*  if it's "more" horizontal in the left or right half. */
    d5 = (double)B->size[1] / 4.0;
    if (1.0 > d5) {
      loop_ub = 0;
    } else {
      loop_ub = (int)d5;
    }

    d5 = (double)B->size[1] / 4.0 + 1.0;
    d6 = (double)B->size[1] / 2.0;
    if (d5 > d6) {
      i41 = 0;
      i42 = 0;
    } else {
      i41 = (int)d5 - 1;
      i42 = (int)d6;
    }

    emxInit_real_T(&b_B, 3);
    b_loop_ub = B->size[0];
    input_sizes_idx_1 = b_B->size[0] * b_B->size[1] * b_B->size[2];
    b_B->size[0] = b_loop_ub;
    b_B->size[1] = loop_ub;
    b_B->size[2] = 1;
    emxEnsureCapacity_real_T(b_B, input_sizes_idx_1);
    for (input_sizes_idx_1 = 0; input_sizes_idx_1 < loop_ub; input_sizes_idx_1++)
    {
      for (sizes_idx_1 = 0; sizes_idx_1 < b_loop_ub; sizes_idx_1++) {
        b_B->data[sizes_idx_1 + b_B->size[0] * input_sizes_idx_1] = B->
          data[sizes_idx_1 + B->size[0] * input_sizes_idx_1];
      }
    }

    emxInit_real_T(&d_B, 3);
    c_sum(b_B, r7);
    d_sum(r7, tmp_data, tmp_size);
    loop_ub = B->size[0];
    input_sizes_idx_1 = d_B->size[0] * d_B->size[1] * d_B->size[2];
    d_B->size[0] = loop_ub;
    b_loop_ub = i42 - i41;
    d_B->size[1] = b_loop_ub;
    d_B->size[2] = 1;
    emxEnsureCapacity_real_T(d_B, input_sizes_idx_1);
    emxFree_real_T(&b_B);
    for (i42 = 0; i42 < b_loop_ub; i42++) {
      for (input_sizes_idx_1 = 0; input_sizes_idx_1 < loop_ub; input_sizes_idx_1
           ++) {
        d_B->data[input_sizes_idx_1 + d_B->size[0] * i42] = B->
          data[input_sizes_idx_1 + B->size[0] * (i41 + i42)];
      }
    }

    c_sum(d_B, r7);
    d_sum(r7, b_tmp_data, tmp_size);
    empty_non_axis_sizes = true;
    emxFree_real_T(&d_B);
    if (!(tmp_data[0] > b_tmp_data[0])) {
      empty_non_axis_sizes = false;
    }

    if (empty_non_axis_sizes) {
      direction = 2.0;
    } else {
      direction = 3.0;
    }
  } else {
    /*  If the filter determined that the sub area is vertical, check if */
    /*  it's "more" vertical in the upper half or lower half. */
    d5 = (double)B->size[0] / 2.0;
    if (1.0 > d5) {
      loop_ub = 0;
    } else {
      loop_ub = (int)d5;
    }

    d5 = (double)B->size[1] / 2.0 + 1.0;
    if (d5 > B->size[1]) {
      i41 = 0;
      i42 = 0;
    } else {
      i41 = (int)d5 - 1;
      i42 = B->size[1];
    }

    d5 = (double)B->size[0] / 2.0 + 1.0;
    if (d5 > B->size[0]) {
      input_sizes_idx_1 = 0;
      sizes_idx_1 = 0;
    } else {
      input_sizes_idx_1 = (int)d5 - 1;
      sizes_idx_1 = B->size[0];
    }

    d5 = (double)B->size[1] / 2.0 + 1.0;
    if (d5 > B->size[1]) {
      i43 = 0;
      i44 = 0;
    } else {
      i43 = (int)d5 - 1;
      i44 = B->size[1];
    }

    emxInit_real_T(&c_B, 3);
    i45 = c_B->size[0] * c_B->size[1] * c_B->size[2];
    c_B->size[0] = loop_ub;
    b_loop_ub = i42 - i41;
    c_B->size[1] = b_loop_ub;
    c_B->size[2] = 1;
    emxEnsureCapacity_real_T(c_B, i45);
    for (i42 = 0; i42 < b_loop_ub; i42++) {
      for (i45 = 0; i45 < loop_ub; i45++) {
        c_B->data[i45 + c_B->size[0] * i42] = B->data[i45 + B->size[0] * (i41 +
          i42)];
      }
    }

    c_sum(c_B, r7);
    d_sum(r7, tmp_data, tmp_size);
    i41 = dilate->size[0] * dilate->size[1] * dilate->size[2];
    loop_ub = sizes_idx_1 - input_sizes_idx_1;
    dilate->size[0] = loop_ub;
    b_loop_ub = i44 - i43;
    dilate->size[1] = b_loop_ub;
    dilate->size[2] = 1;
    emxEnsureCapacity_real_T(dilate, i41);
    emxFree_real_T(&c_B);
    for (i41 = 0; i41 < b_loop_ub; i41++) {
      for (i42 = 0; i42 < loop_ub; i42++) {
        dilate->data[i42 + dilate->size[0] * i41] = B->data[(input_sizes_idx_1 +
          i42) + B->size[0] * (i43 + i41)];
      }
    }

    c_sum(dilate, r7);
    d_sum(r7, b_tmp_data, tmp_size);
    empty_non_axis_sizes = true;
    if (!(tmp_data[0] > b_tmp_data[0])) {
      empty_non_axis_sizes = false;
    }

    direction = !empty_non_axis_sizes;
  }

  emxFree_real_T(&r7);
  emxFree_real_T(&B);
  emxFree_real_T(&dilate);
  return direction;
}

double findDirection(const emxArray_real_T *subArea)
{
  double direction;
  emxArray_real_T *B;
  int i28;
  double asizeT[2];
  double nsizeT[2];
  emxArray_real_T *b_B;
  int i29;
  int loop_ub;
  emxArray_real_T *b;
  double outSizeT[2];
  boolean_T empty_non_axis_sizes;
  double padSizeT[2];
  double kernel[3];
  double connDimsT[2];
  static const boolean_T conn[3] = { true, false, true };

  int input_sizes_idx_1;
  int sizes_idx_1;
  static const boolean_T b_conn[3] = { true, false, true };

  emxArray_real_T *r5;
  emxArray_real_T *r6;
  double d3;
  double d4;
  int b_loop_ub;
  int i30;
  int i31;
  int i32;
  emxInit_real_T(&B, 2);

  /*     %% Filters a sub area to determine direction */
  i28 = B->size[0] * B->size[1];
  B->size[0] = subArea->size[0];
  B->size[1] = subArea->size[1];
  emxEnsureCapacity_real_T(B, i28);
  asizeT[0] = subArea->size[0];
  asizeT[1] = subArea->size[1];
  nsizeT[0] = 3.0;
  nsizeT[1] = 3.0;
  emxInit_real_T(&b_B, 2);
  dilate_flat_real64_tbb(&subArea->data[0], asizeT, 2.0, bv0, nsizeT, 2.0,
    &B->data[0]);
  i28 = b_B->size[0] * b_B->size[1];
  b_B->size[0] = subArea->size[0];
  b_B->size[1] = subArea->size[1];
  emxEnsureCapacity_real_T(b_B, i28);
  asizeT[0] = subArea->size[0];
  asizeT[1] = subArea->size[1];
  nsizeT[0] = 3.0;
  nsizeT[1] = 3.0;
  erode_flat_real64_tbb(&subArea->data[0], asizeT, 2.0, bv0, nsizeT, 2.0,
                        &b_B->data[0]);
  i28 = B->size[0] * B->size[1];
  i29 = B->size[0] * B->size[1];
  emxEnsureCapacity_real_T(B, i29);
  loop_ub = i28 - 1;
  for (i28 = 0; i28 <= loop_ub; i28++) {
    B->data[i28] -= b_B->data[i28];
  }

  emxInit_real_T(&b, 2);

  /*  Define filter kernels */
  /*  Filter the sub area with a horizontal kernel and vertical kernel, */
  /*  respectively */
  outSizeT[0] = B->size[0];
  asizeT[0] = 1.0;
  outSizeT[1] = B->size[1];
  asizeT[1] = 0.0;
  if ((B->size[0] == 0) || (B->size[1] == 0)) {
    i28 = b->size[0] * b->size[1];
    b->size[0] = B->size[0];
    b->size[1] = B->size[1];
    emxEnsureCapacity_real_T(b, i28);
    loop_ub = B->size[0] * B->size[1];
    for (i28 = 0; i28 < loop_ub; i28++) {
      b->data[i28] = B->data[i28];
    }
  } else {
    padImage(B, asizeT, b_B);
    empty_non_axis_sizes = ((int)(unsigned int)outSizeT[0] > 65500);
    if (empty_non_axis_sizes && ((int)(unsigned int)outSizeT[1] > 65500)) {
    } else {
      empty_non_axis_sizes = false;
    }

    i28 = b->size[0] * b->size[1];
    b->size[0] = (int)outSizeT[0];
    b->size[1] = (int)outSizeT[1];
    emxEnsureCapacity_real_T(b, i28);
    if (!empty_non_axis_sizes) {
      padSizeT[0] = b_B->size[0];
      padSizeT[1] = b_B->size[1];
      kernel[0] = 1.0;
      kernel[1] = 0.0;
      kernel[2] = -1.0;
      asizeT[0] = 3.0;
      asizeT[1] = 1.0;
      ippfilter_real64(&b_B->data[0], &b->data[0], outSizeT, 2.0, padSizeT,
                       kernel, asizeT, false);
    } else {
      padSizeT[0] = b_B->size[0];
      nsizeT[0] = 1.0;
      padSizeT[1] = b_B->size[1];
      nsizeT[1] = -1.0;
      connDimsT[0] = 3.0;
      connDimsT[1] = 1.0;
      imfilter_real64(&b_B->data[0], &b->data[0], 2.0, outSizeT, 2.0, padSizeT,
                      nsizeT, 2.0, conn, 2.0, connDimsT, asizeT, 2.0, true,
                      false);
    }
  }

  outSizeT[0] = B->size[0];
  asizeT[0] = 0.0;
  outSizeT[1] = B->size[1];
  asizeT[1] = 1.0;
  if ((B->size[0] != 0) && (B->size[1] != 0)) {
    padImage(B, asizeT, b_B);
    empty_non_axis_sizes = ((int)(unsigned int)outSizeT[0] > 65500);
    if (empty_non_axis_sizes && ((int)(unsigned int)outSizeT[1] > 65500)) {
    } else {
      empty_non_axis_sizes = false;
    }

    i28 = B->size[0] * B->size[1];
    B->size[0] = (int)outSizeT[0];
    B->size[1] = (int)outSizeT[1];
    emxEnsureCapacity_real_T(B, i28);
    if (!empty_non_axis_sizes) {
      padSizeT[0] = b_B->size[0];
      padSizeT[1] = b_B->size[1];
      kernel[0] = 1.0;
      kernel[1] = 0.0;
      kernel[2] = -1.0;
      asizeT[0] = 1.0;
      asizeT[1] = 3.0;
      ippfilter_real64(&b_B->data[0], &B->data[0], outSizeT, 2.0, padSizeT,
                       kernel, asizeT, false);
    } else {
      padSizeT[0] = b_B->size[0];
      nsizeT[0] = 1.0;
      padSizeT[1] = b_B->size[1];
      nsizeT[1] = -1.0;
      connDimsT[0] = 1.0;
      connDimsT[1] = 3.0;
      imfilter_real64(&b_B->data[0], &B->data[0], 2.0, outSizeT, 2.0, padSizeT,
                      nsizeT, 2.0, b_conn, 2.0, connDimsT, asizeT, 2.0, true,
                      false);
    }
  }

  if ((b->size[0] != 0) && (b->size[1] != 0)) {
    loop_ub = b->size[0];
  } else if ((B->size[0] != 0) && (B->size[1] != 0)) {
    loop_ub = B->size[0];
  } else {
    loop_ub = b->size[0];
    if (loop_ub <= 0) {
      loop_ub = 0;
    }

    if (B->size[0] > loop_ub) {
      loop_ub = B->size[0];
    }
  }

  empty_non_axis_sizes = (loop_ub == 0);
  if (empty_non_axis_sizes || ((b->size[0] != 0) && (b->size[1] != 0))) {
    input_sizes_idx_1 = b->size[1];
  } else {
    input_sizes_idx_1 = 0;
  }

  if (empty_non_axis_sizes || ((B->size[0] != 0) && (B->size[1] != 0))) {
    sizes_idx_1 = B->size[1];
  } else {
    sizes_idx_1 = 0;
  }

  i28 = b_B->size[0] * b_B->size[1];
  b_B->size[0] = loop_ub;
  b_B->size[1] = input_sizes_idx_1 + sizes_idx_1;
  emxEnsureCapacity_real_T(b_B, i28);
  for (i28 = 0; i28 < input_sizes_idx_1; i28++) {
    for (i29 = 0; i29 < loop_ub; i29++) {
      b_B->data[i29 + b_B->size[0] * i28] = b->data[i29 + loop_ub * i28];
    }
  }

  emxFree_real_T(&b);
  for (i28 = 0; i28 < sizes_idx_1; i28++) {
    for (i29 = 0; i29 < loop_ub; i29++) {
      b_B->data[i29 + b_B->size[0] * (i28 + input_sizes_idx_1)] = B->data[i29 +
        loop_ub * i28];
    }
  }

  /*  If the mean value of the horizontal filter is greater than the */
  /*  vertical, we consider the sub area to be horizontal. Otherwise */
  /*  vertical. */
  emxInit_real_T(&r5, 2);
  emxInit_real_T(&r6, 2);
  if (b_B->data[0] > b_B->data[1]) {
    /*  If the filter determined that the sub area is horizontal, check */
    /*  if it's "more" horizontal in the left or right half. */
    d3 = (double)b_B->size[1] / 4.0;
    if (1.0 > d3) {
      loop_ub = 0;
    } else {
      loop_ub = (int)d3;
    }

    d3 = (double)b_B->size[1] / 4.0 + 1.0;
    d4 = (double)b_B->size[1] / 2.0;
    if (d3 > d4) {
      i28 = 0;
      i29 = 0;
    } else {
      i28 = (int)d3 - 1;
      i29 = (int)d4;
    }

    b_loop_ub = b_B->size[0];
    input_sizes_idx_1 = B->size[0] * B->size[1];
    B->size[0] = b_loop_ub;
    B->size[1] = loop_ub;
    emxEnsureCapacity_real_T(B, input_sizes_idx_1);
    for (input_sizes_idx_1 = 0; input_sizes_idx_1 < loop_ub; input_sizes_idx_1++)
    {
      for (sizes_idx_1 = 0; sizes_idx_1 < b_loop_ub; sizes_idx_1++) {
        B->data[sizes_idx_1 + B->size[0] * input_sizes_idx_1] = b_B->
          data[sizes_idx_1 + b_B->size[0] * input_sizes_idx_1];
      }
    }

    sum(B, r5);
    loop_ub = b_B->size[0];
    input_sizes_idx_1 = B->size[0] * B->size[1];
    B->size[0] = loop_ub;
    b_loop_ub = i29 - i28;
    B->size[1] = b_loop_ub;
    emxEnsureCapacity_real_T(B, input_sizes_idx_1);
    for (i29 = 0; i29 < b_loop_ub; i29++) {
      for (input_sizes_idx_1 = 0; input_sizes_idx_1 < loop_ub; input_sizes_idx_1
           ++) {
        B->data[input_sizes_idx_1 + B->size[0] * i29] = b_B->
          data[input_sizes_idx_1 + b_B->size[0] * (i28 + i29)];
      }
    }

    sum(B, r6);
    if (b_sum(r5) > b_sum(r6)) {
      direction = 2.0;
    } else {
      direction = 3.0;
    }
  } else {
    /*  If the filter determined that the sub area is vertical, check if */
    /*  it's "more" vertical in the upper half or lower half. */
    d3 = (double)b_B->size[0] / 2.0;
    if (1.0 > d3) {
      loop_ub = 0;
    } else {
      loop_ub = (int)d3;
    }

    d3 = (double)b_B->size[1] / 2.0 + 1.0;
    if (d3 > b_B->size[1]) {
      i28 = 0;
      i29 = 0;
    } else {
      i28 = (int)d3 - 1;
      i29 = b_B->size[1];
    }

    d3 = (double)b_B->size[0] / 2.0 + 1.0;
    if (d3 > b_B->size[0]) {
      input_sizes_idx_1 = 0;
      sizes_idx_1 = 0;
    } else {
      input_sizes_idx_1 = (int)d3 - 1;
      sizes_idx_1 = b_B->size[0];
    }

    d3 = (double)b_B->size[1] / 2.0 + 1.0;
    if (d3 > b_B->size[1]) {
      i30 = 0;
      i31 = 0;
    } else {
      i30 = (int)d3 - 1;
      i31 = b_B->size[1];
    }

    i32 = B->size[0] * B->size[1];
    B->size[0] = loop_ub;
    b_loop_ub = i29 - i28;
    B->size[1] = b_loop_ub;
    emxEnsureCapacity_real_T(B, i32);
    for (i29 = 0; i29 < b_loop_ub; i29++) {
      for (i32 = 0; i32 < loop_ub; i32++) {
        B->data[i32 + B->size[0] * i29] = b_B->data[i32 + b_B->size[0] * (i28 +
          i29)];
      }
    }

    sum(B, r5);
    i28 = B->size[0] * B->size[1];
    loop_ub = sizes_idx_1 - input_sizes_idx_1;
    B->size[0] = loop_ub;
    b_loop_ub = i31 - i30;
    B->size[1] = b_loop_ub;
    emxEnsureCapacity_real_T(B, i28);
    for (i28 = 0; i28 < b_loop_ub; i28++) {
      for (i29 = 0; i29 < loop_ub; i29++) {
        B->data[i29 + B->size[0] * i28] = b_B->data[(input_sizes_idx_1 + i29) +
          b_B->size[0] * (i30 + i28)];
      }
    }

    sum(B, r6);
    direction = !(b_sum(r5) > b_sum(r6));
  }

  emxFree_real_T(&r6);
  emxFree_real_T(&r5);
  emxFree_real_T(&b_B);
  emxFree_real_T(&B);
  return direction;
}

/* End of code generation (findDirection.cpp) */
