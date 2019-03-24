/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imcrop.cpp
 *
 * Code generation for function 'imcrop'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "imcrop.h"
#include "Version7_corrRot_emxutil.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */
static double rt_roundd_snf(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

void imcrop(const emxArray_real_T *varargin_1, emxArray_real_T *varargout_1)
{
  unsigned int xdata_idx_1;
  unsigned int ydata_idx_1;
  int xmax;
  int xmin;
  int ymax;
  int ymin;
  double pixelsPerVerticalUnit;
  double pixelsPerHorizontalUnit;
  double r1;
  int i21;
  int i22;
  int i23;
  xdata_idx_1 = (unsigned int)varargin_1->size[1];
  ydata_idx_1 = (unsigned int)varargin_1->size[0];
  xmax = 1;
  xmin = 1;
  if ((int)xdata_idx_1 > 1) {
    xmax = (int)xdata_idx_1;
  }

  if ((int)xdata_idx_1 < 1) {
    xmin = 0;
  }

  ymax = 1;
  ymin = 1;
  if ((int)ydata_idx_1 > 1) {
    ymax = (int)ydata_idx_1;
  }

  if ((int)ydata_idx_1 < 1) {
    ymin = 0;
  }

  if (varargin_1->size[0] == 1) {
    pixelsPerVerticalUnit = 1.0;
  } else {
    pixelsPerVerticalUnit = ((double)varargin_1->size[0] - 1.0) / (double)(ymax
      - ymin);
  }

  if (varargin_1->size[1] == 1) {
    pixelsPerHorizontalUnit = 1.0;
  } else {
    pixelsPerHorizontalUnit = ((double)varargin_1->size[1] - 1.0) / (double)
      (xmax - xmin);
  }

  r1 = (1.0 - (double)ymin) * pixelsPerVerticalUnit + 1.0;
  ymin = (int)rt_roundd_snf(r1 + 720.0 * pixelsPerVerticalUnit);
  xmax = (int)rt_roundd_snf(r1);
  pixelsPerVerticalUnit = (280.0 - (double)xmin) * pixelsPerHorizontalUnit + 1.0;
  xmin = (int)rt_roundd_snf(pixelsPerVerticalUnit + 719.0 *
    pixelsPerHorizontalUnit);
  ymax = (int)rt_roundd_snf(pixelsPerVerticalUnit);
  if ((xmax > varargin_1->size[0]) || (ymin < 1) || (ymax > varargin_1->size[1])
      || (xmin < 1)) {
    varargout_1->size[0] = 0;
    varargout_1->size[1] = 0;
  } else {
    if (xmax < 1) {
      xmax = 1;
    }

    if (ymin > varargin_1->size[0]) {
      ymin = varargin_1->size[0];
    }

    if (ymax < 1) {
      ymax = 1;
    }

    if (xmin > varargin_1->size[1]) {
      xmin = varargin_1->size[1];
    }

    if (xmax > ymin) {
      i21 = 0;
      ymin = 0;
    } else {
      i21 = xmax - 1;
    }

    if (ymax > xmin) {
      i22 = 0;
      xmin = 0;
    } else {
      i22 = ymax - 1;
    }

    i23 = varargout_1->size[0] * varargout_1->size[1];
    ymin -= i21;
    varargout_1->size[0] = ymin;
    xmax = xmin - i22;
    varargout_1->size[1] = xmax;
    emxEnsureCapacity_real_T(varargout_1, i23);
    for (i23 = 0; i23 < xmax; i23++) {
      for (ymax = 0; ymax < ymin; ymax++) {
        varargout_1->data[ymax + varargout_1->size[0] * i23] = varargin_1->data
          [(i21 + ymax) + varargin_1->size[0] * (i22 + i23)];
      }
    }
  }
}

/* End of code generation (imcrop.cpp) */
