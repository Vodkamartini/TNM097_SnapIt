/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imfilter.cpp
 *
 * Code generation for function 'imfilter'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "imfilter.h"
#include "Version7_corrRot_emxutil.h"
#include "libmwimfilter.h"
#include "libmwippfilter.h"

/* Function Definitions */
void b_padImage(const emxArray_real_T *a_tmp, const double pad[3],
                emxArray_real_T *a)
{
  double sizeB_idx_0;
  double sizeB_idx_1;
  int i47;
  int j;
  int i48;
  int i49;
  int i;
  int i50;
  if ((a_tmp->size[0] == 0) || (a_tmp->size[1] == 0)) {
    sizeB_idx_0 = (double)a_tmp->size[0] + 2.0 * pad[0];
    sizeB_idx_1 = (double)a_tmp->size[1] + 2.0 * pad[1];
    i47 = a->size[0] * a->size[1] * a->size[2];
    a->size[0] = (int)sizeB_idx_0;
    a->size[1] = (int)sizeB_idx_1;
    a->size[2] = 1;
    emxEnsureCapacity_real_T(a, i47);
    j = (int)sizeB_idx_0 * (int)sizeB_idx_1;
    for (i47 = 0; i47 < j; i47++) {
      a->data[i47] = 0.0;
    }
  } else {
    sizeB_idx_0 = (double)a_tmp->size[0] + 2.0 * pad[0];
    sizeB_idx_1 = (double)a_tmp->size[1] + 2.0 * pad[1];
    i47 = a->size[0] * a->size[1] * a->size[2];
    a->size[0] = (int)sizeB_idx_0;
    a->size[1] = (int)sizeB_idx_1;
    a->size[2] = 1;
    emxEnsureCapacity_real_T(a, i47);
    i47 = (int)pad[1];
    for (j = 0; j < i47; j++) {
      i48 = a->size[0];
      for (i = 0; i < i48; i++) {
        a->data[i] = 0.0;
      }
    }

    i48 = (a_tmp->size[1] + i47) + 1;
    i49 = a->size[1];
    for (j = i48; j <= i49; j++) {
      i50 = a->size[0];
      for (i = 0; i < i50; i++) {
        a->data[i + a->size[0] * (j - 1)] = 0.0;
      }
    }

    i48 = a_tmp->size[1];
    for (j = 0; j < i48; j++) {
      i49 = (int)pad[0];
      for (i = 0; i < i49; i++) {
        a->data[a->size[0] * (j + i47)] = 0.0;
      }
    }

    i48 = a_tmp->size[1];
    for (j = 0; j < i48; j++) {
      i49 = ((int)pad[0] + a_tmp->size[0]) + 1;
      i50 = a->size[0];
      for (i = i49; i <= i50; i++) {
        a->data[(i + a->size[0] * (j + i47)) - 1] = 0.0;
      }
    }

    i48 = a_tmp->size[1];
    for (j = 0; j < i48; j++) {
      i49 = a_tmp->size[0];
      for (i = 0; i < i49; i++) {
        a->data[(i + (int)pad[0]) + a->size[0] * (j + i47)] = a_tmp->data[i +
          a_tmp->size[0] * j];
      }
    }
  }
}

void imfilter(emxArray_real_T *varargin_1)
{
  double outSizeT[3];
  double startT[3];
  emxArray_real_T *a;
  boolean_T tooBig;
  int i51;
  double padSizeT[3];
  double kernelSizeT[2];
  double connDimsT[2];
  static const boolean_T conn[3] = { true, false, true };

  outSizeT[0] = varargin_1->size[0];
  startT[0] = 1.0;
  outSizeT[1] = varargin_1->size[1];
  startT[1] = 0.0;
  outSizeT[2] = 1.0;
  startT[2] = 0.0;
  if ((varargin_1->size[0] != 0) && (varargin_1->size[1] != 0)) {
    emxInit_real_T(&a, 3);
    b_padImage(varargin_1, startT, a);
    tooBig = (outSizeT[0] > 65500.0);
    if (tooBig && (outSizeT[1] > 65500.0)) {
      tooBig = true;
    } else {
      tooBig = false;
    }

    i51 = varargin_1->size[0] * varargin_1->size[1] * varargin_1->size[2];
    varargin_1->size[0] = (int)outSizeT[0];
    varargin_1->size[1] = (int)outSizeT[1];
    varargin_1->size[2] = 1;
    emxEnsureCapacity_real_T(varargin_1, i51);
    if (!tooBig) {
      padSizeT[0] = a->size[0];
      startT[0] = 1.0;
      padSizeT[1] = a->size[1];
      startT[1] = 0.0;
      padSizeT[2] = a->size[2];
      startT[2] = -1.0;
      kernelSizeT[0] = 3.0;
      kernelSizeT[1] = 1.0;
      ippfilter_real64(&a->data[0], &varargin_1->data[0], outSizeT, 2.0,
                       padSizeT, startT, kernelSizeT, false);
    } else {
      padSizeT[0] = a->size[0];
      padSizeT[1] = a->size[1];
      padSizeT[2] = a->size[2];
      kernelSizeT[0] = 1.0;
      kernelSizeT[1] = -1.0;
      connDimsT[0] = 3.0;
      connDimsT[1] = 1.0;
      imfilter_real64(&a->data[0], &varargin_1->data[0], 3.0, outSizeT, 2.0,
                      padSizeT, kernelSizeT, 2.0, conn, 2.0, connDimsT, startT,
                      3.0, true, false);
    }

    emxFree_real_T(&a);
  }
}

void padImage(const emxArray_real_T *a_tmp, const double pad[2], emxArray_real_T
              *a)
{
  double sizeB_idx_0;
  double sizeB_idx_1;
  int i33;
  int j;
  int i34;
  int i35;
  int i;
  int i36;
  if ((a_tmp->size[0] == 0) || (a_tmp->size[1] == 0)) {
    sizeB_idx_0 = (double)a_tmp->size[0] + 2.0 * pad[0];
    sizeB_idx_1 = (double)a_tmp->size[1] + 2.0 * pad[1];
    i33 = a->size[0] * a->size[1];
    a->size[0] = (int)sizeB_idx_0;
    a->size[1] = (int)sizeB_idx_1;
    emxEnsureCapacity_real_T(a, i33);
    j = (int)sizeB_idx_0 * (int)sizeB_idx_1;
    for (i33 = 0; i33 < j; i33++) {
      a->data[i33] = 0.0;
    }
  } else {
    sizeB_idx_0 = (double)a_tmp->size[0] + 2.0 * pad[0];
    sizeB_idx_1 = (double)a_tmp->size[1] + 2.0 * pad[1];
    i33 = a->size[0] * a->size[1];
    a->size[0] = (int)sizeB_idx_0;
    a->size[1] = (int)sizeB_idx_1;
    emxEnsureCapacity_real_T(a, i33);
    i33 = (int)pad[1];
    for (j = 0; j < i33; j++) {
      i34 = a->size[0];
      for (i = 0; i < i34; i++) {
        a->data[i] = 0.0;
      }
    }

    i34 = (a_tmp->size[1] + i33) + 1;
    i35 = a->size[1];
    for (j = i34; j <= i35; j++) {
      i36 = a->size[0];
      for (i = 0; i < i36; i++) {
        a->data[i + a->size[0] * (j - 1)] = 0.0;
      }
    }

    i34 = a_tmp->size[1];
    for (j = 0; j < i34; j++) {
      i35 = (int)pad[0];
      for (i = 0; i < i35; i++) {
        a->data[a->size[0] * (j + i33)] = 0.0;
      }
    }

    i34 = a_tmp->size[1];
    for (j = 0; j < i34; j++) {
      i35 = ((int)pad[0] + a_tmp->size[0]) + 1;
      i36 = a->size[0];
      for (i = i35; i <= i36; i++) {
        a->data[(i + a->size[0] * (j + i33)) - 1] = 0.0;
      }
    }

    i34 = a_tmp->size[1];
    for (j = 0; j < i34; j++) {
      i35 = a_tmp->size[0];
      for (i = 0; i < i35; i++) {
        a->data[(i + (int)pad[0]) + a->size[0] * (j + i33)] = a_tmp->data[i +
          a_tmp->size[0] * j];
      }
    }
  }
}

/* End of code generation (imfilter.cpp) */
