/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Version7_corrRot_types.h
 *
 * Code generation for function 'Version7_corrRot'
 *
 */

#ifndef VERSION7_CORRROT_TYPES_H
#define VERSION7_CORRROT_TYPES_H

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

/* End of code generation (Version7_corrRot_types.h) */
