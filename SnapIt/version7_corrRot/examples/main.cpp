/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.cpp
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "main.h"
#include "Version7_corrRot_terminate.h"
#include "Version7_corrRot_emxAPI.h"
#include "Version7_corrRot_initialize.h"

/* Function Declarations */
static double argInit_real_T();
static emxArray_real_T *c_argInit_UnboundedxUnbounded_r();
static void main_Version7_corrRot();

/* Function Definitions */
static double argInit_real_T()
{
  return 0.0;
}

static emxArray_real_T *c_argInit_UnboundedxUnbounded_r()
{
  emxArray_real_T *result;
  int idx0;
  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreate_real_T(2, 2);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result->data[idx0 + result->size[0] * idx1] = argInit_real_T();
    }
  }

  return result;
}

static void main_Version7_corrRot()
{
  emxArray_real_T *rebuild_final;
  emxArray_real_T *img;
  emxInitArray_real_T(&rebuild_final, 3);

  /* Initialize function 'Version7_corrRot' input arguments. */
  /* Initialize function input argument 'img'. */
  img = c_argInit_UnboundedxUnbounded_r();

  /* Call the entry-point 'Version7_corrRot'. */
  Version7_corrRot(img, rebuild_final);
  emxDestroyArray_real_T(rebuild_final);
  emxDestroyArray_real_T(img);
}

int main(int, const char * const [])
{
  /* Initialize the application.
     You do not need to do this more than one time. */
  Version7_corrRot_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_Version7_corrRot();

  /* Terminate the application.
     You do not need to do this more than one time. */
  Version7_corrRot_terminate();
  return 0;
}

/* End of code generation (main.cpp) */
