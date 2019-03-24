/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imrotate.h
 *
 * Code generation for function 'imrotate'
 *
 */

#ifndef IMROTATE_H
#define IMROTATE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "Version7_corrRot_types.h"

/* Function Declarations */
extern void b_imrotate(const emxArray_real_T *varargin_1, emxArray_real_T *B);
extern void c_imrotate(const emxArray_real_T *varargin_1, emxArray_real_T *B);
extern void imrotate(const emxArray_real_T *varargin_1, emxArray_real_T *B);

#endif

/* End of code generation (imrotate.h) */
