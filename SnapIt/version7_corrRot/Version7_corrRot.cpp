/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Version7_corrRot.cpp
 *
 * Code generation for function 'Version7_corrRot'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "Version7_corrRot.h"
#include "Version7_corrRot_emxutil.h"
#include "mean2.h"
#include "findDirection.h"
#include "imrotate.h"
#include "imresize.h"
#include "imcrop.h"

/* Function Definitions */
void Version7_corrRot(const emxArray_real_T *img, emxArray_real_T *rebuild_final)
{
  emxArray_real_T *original;
  emxArray_real_T *sub;
  unsigned int originalSize_idx_0;
  unsigned int subSize_idx_0;
  unsigned int originalSize_idx_1;
  unsigned int subSize_idx_1;
  double d0;
  double ref_direction;
  emxArray_real_T *refA;
  emxArray_real_T *refB;
  emxArray_real_T *refC;
  emxArray_real_T *refD;
  int i0;
  int loop_ub;
  emxArray_real_T *meanR;
  int i1;
  int i2;
  int loop_ub_tmp;
  emxArray_real_T *meanG;
  emxArray_real_T *meanB;
  emxArray_real_T *temp;
  emxArray_real_T *b_temp;
  emxArray_real_T *c_temp;
  emxArray_real_T *d_temp;
  int i;
  double d1;
  emxArray_real_T *corrected;
  int j;
  int i3;
  int i4;
  int i5;
  int i6;
  int b_loop_ub;
  int c_loop_ub;
  int i7;
  int i8;
  int d_loop_ub;
  emxArray_real_T e_temp;
  int i9;
  int iv0[3];
  emxArray_real_T *f_temp;
  emxArray_int32_T *r0;
  int i10;
  emxArray_int32_T *r1;
  int i11;
  emxArray_real_T *g_temp;
  int e_loop_ub;
  int f_loop_ub;
  int i12;
  int i13;
  int g_loop_ub;
  int i14;
  int i15;
  int h_loop_ub;
  int i_loop_ub;
  int i16;
  int i17;
  int i18;
  int j_loop_ub;
  int i19;
  int i20;
  double d2;
  double delta_R;
  double delta_R_idx_0;
  double delta_R_idx_1;
  double delta_R_idx_2;
  double delta_G;
  double delta_G_idx_0;
  double delta_G_idx_1;
  double delta_G_idx_2;
  double delta_B;
  double delta_B_idx_0;
  double delta_B_idx_1;
  emxInit_real_T(&original, 2);
  emxInit_real_T(&sub, 2);

  /*  STEP 0: Use webcam to snapshot an image to work with */
  /*  clear cam */
  /*  cam = webcam; */
  /*  cam.resolution = '1280x720'; */
  /*  original = snapshot(cam); */
  /* original = imread('reading_org.png'); */
  /*  STEP 1: Copy and compress original image and convert to double */
  /*  Create a sub image and convert original image to CIELab */
  imcrop(img, original);

  /*  [leftX leftY rightX rightY] (Don't know why this results in 480x480 though)11 */
  imresize(original, sub);

  /*  Convert original and sub to double to normalize them before processing */
  /*  STEP 2: Check scale between compressed and original image */
  /*  How many sub images fit in the original image according to aspect ratio */
  originalSize_idx_0 = (unsigned int)original->size[0];
  subSize_idx_0 = (unsigned int)sub->size[0];
  originalSize_idx_1 = (unsigned int)original->size[1];
  subSize_idx_1 = (unsigned int)sub->size[1];
  d0 = std::floor((double)originalSize_idx_0 / (double)subSize_idx_0);

  /*  STEP 2.5: Create reference images and label their frequencies */
  /*  Create four different reference images (different rotations)  */
  /*  and a vector to store them in */
  ref_direction = findDirection(sub);
  emxInit_real_T(&refA, 2);
  emxInit_real_T(&refB, 2);
  emxInit_real_T(&refC, 2);
  emxInit_real_T(&refD, 2);
  if (ref_direction == 0.0) {
    i0 = refA->size[0] * refA->size[1];
    refA->size[0] = sub->size[0];
    refA->size[1] = sub->size[1];
    emxEnsureCapacity_real_T(refA, i0);
    loop_ub = sub->size[0] * sub->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      refA->data[i0] = sub->data[i0];
    }

    /*  Up */
    imrotate(sub, refB);

    /*  Right */
    b_imrotate(sub, refC);

    /*  Down */
    c_imrotate(sub, refD);

    /*  Left */
  } else if (ref_direction == 2.0) {
    i0 = refB->size[0] * refB->size[1];
    refB->size[0] = sub->size[0];
    refB->size[1] = sub->size[1];
    emxEnsureCapacity_real_T(refB, i0);
    loop_ub = sub->size[0] * sub->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      refB->data[i0] = sub->data[i0];
    }

    /*  Right */
    imrotate(sub, refC);

    /*  Down */
    b_imrotate(sub, refD);

    /*  Left */
    c_imrotate(sub, refA);

    /*  Up */
  } else if (ref_direction == 1.0) {
    i0 = refC->size[0] * refC->size[1];
    refC->size[0] = sub->size[0];
    refC->size[1] = sub->size[1];
    emxEnsureCapacity_real_T(refC, i0);
    loop_ub = sub->size[0] * sub->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      refC->data[i0] = sub->data[i0];
    }

    /*  Down */
    imrotate(sub, refD);

    /*  Left */
    b_imrotate(sub, refA);

    /*  Up */
    c_imrotate(sub, refB);

    /*  Right */
  } else {
    i0 = refD->size[0] * refD->size[1];
    refD->size[0] = sub->size[0];
    refD->size[1] = sub->size[1];
    emxEnsureCapacity_real_T(refD, i0);
    loop_ub = sub->size[0] * sub->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      refD->data[i0] = sub->data[i0];
    }

    /*  Left */
    imrotate(sub, refA);

    /*  Down */
    b_imrotate(sub, refB);

    /*  Right */
    c_imrotate(sub, refC);

    /*  Up */
  }

  emxInit_real_T(&meanR, 4);

  /*  STEP 3: Get mean RGB-values for sub-areas */
  /*  Extract an area, with respect of aspect ratio and scale between original */
  /*  and compressed image, and calculate mean RGB for that area. */
  i0 = meanR->size[0] * meanR->size[1] * meanR->size[2] * meanR->size[3];
  meanR->size[0] = 2;
  meanR->size[1] = 2;
  i1 = (int)std::floor((double)originalSize_idx_1 / (double)subSize_idx_1);
  meanR->size[2] = i1;
  i2 = (int)d0;
  meanR->size[3] = i2;
  emxEnsureCapacity_real_T(meanR, i0);
  loop_ub_tmp = (i1 << 2) * i2;
  for (i0 = 0; i0 < loop_ub_tmp; i0++) {
    meanR->data[i0] = 0.0;
  }

  emxInit_real_T(&meanG, 4);
  i0 = meanG->size[0] * meanG->size[1] * meanG->size[2] * meanG->size[3];
  meanG->size[0] = 2;
  meanG->size[1] = 2;
  meanG->size[2] = i1;
  meanG->size[3] = i2;
  emxEnsureCapacity_real_T(meanG, i0);
  for (i0 = 0; i0 < loop_ub_tmp; i0++) {
    meanG->data[i0] = 0.0;
  }

  emxInit_real_T(&meanB, 4);
  i0 = meanB->size[0] * meanB->size[1] * meanB->size[2] * meanB->size[3];
  meanB->size[0] = 2;
  meanB->size[1] = 2;
  meanB->size[2] = i1;
  meanB->size[3] = i2;
  emxEnsureCapacity_real_T(meanB, i0);
  for (i0 = 0; i0 < loop_ub_tmp; i0++) {
    meanB->data[i0] = 0.0;
  }

  i0 = sub->size[0] * sub->size[1];
  sub->size[0] = i1;
  sub->size[1] = i2;
  emxEnsureCapacity_real_T(sub, i0);
  loop_ub = i1 * i2;
  for (i0 = 0; i0 < loop_ub; i0++) {
    sub->data[i0] = 0.0;
  }

  emxInit_real_T(&temp, 2);
  emxInit_real_T(&b_temp, 2);
  emxInit_real_T(&c_temp, 2);
  emxInit_real_T(&d_temp, 2);
  for (i = 0; i < i1; i++) {
    if (0 <= (int)d0 - 1) {
      d1 = (double)subSize_idx_0 * (1.0 + (double)i);
      ref_direction = 1.0 + (d1 - (double)subSize_idx_0);
      if (ref_direction > d1) {
        i3 = 1;
        i4 = 1;
      } else {
        i3 = (int)ref_direction;
        i4 = (int)d1 + 1;
      }

      i5 = i4 - i3;
      d1 = (double)i5 / 2.0;
      if (1.0 > d1) {
        b_loop_ub = 0;
      } else {
        b_loop_ub = (int)d1;
      }

      if (d1 + 1.0 > i5) {
        i7 = 0;
        i8 = 0;
      } else {
        i7 = (int)(d1 + 1.0) - 1;
        i8 = i5;
      }

      if (1.0 > d1) {
        d_loop_ub = 0;
      } else {
        d_loop_ub = (int)d1;
      }

      ref_direction = (double)(i4 - i3) / 2.0 + 1.0;
      if (ref_direction > i5) {
        i10 = 0;
        i11 = 0;
      } else {
        i10 = (int)ref_direction - 1;
        i11 = i5;
      }

      if (1.0 > d1) {
        e_loop_ub = 0;
      } else {
        e_loop_ub = (int)d1;
      }

      ref_direction = (double)(i4 - i3) / 2.0 + 1.0;
      if (ref_direction > i5) {
        i12 = 0;
        i13 = 0;
      } else {
        i12 = (int)ref_direction - 1;
        i13 = i5;
      }

      if (1.0 > d1) {
        g_loop_ub = 0;
      } else {
        g_loop_ub = (int)d1;
      }

      ref_direction = (double)(i4 - i3) / 2.0 + 1.0;
      if (ref_direction > i5) {
        i14 = 0;
        i15 = 0;
      } else {
        i14 = (int)ref_direction - 1;
        i15 = i5;
      }

      if (1.0 > d1) {
        h_loop_ub = 0;
      } else {
        h_loop_ub = (int)d1;
      }

      ref_direction = (double)(i4 - i3) / 2.0 + 1.0;
      if (ref_direction > i5) {
        i16 = 0;
        i17 = 0;
      } else {
        i16 = (int)ref_direction - 1;
        i17 = i5;
      }

      if (1.0 > d1) {
        j_loop_ub = 0;
      } else {
        j_loop_ub = (int)d1;
      }

      d1 = (double)(i4 - i3) / 2.0 + 1.0;
      if (d1 > i5) {
        i19 = 0;
        i5 = 0;
      } else {
        i19 = (int)d1 - 1;
      }
    }

    for (j = 0; j < i2; j++) {
      d1 = (double)subSize_idx_1 * (1.0 + (double)j);
      ref_direction = 1.0 + (d1 - (double)subSize_idx_1);
      if (ref_direction > d1) {
        i0 = 1;
        loop_ub_tmp = 1;
      } else {
        i0 = (int)ref_direction;
        loop_ub_tmp = (int)d1 + 1;
      }

      i6 = temp->size[0] * temp->size[1];
      loop_ub = i4 - i3;
      temp->size[0] = loop_ub;
      c_loop_ub = loop_ub_tmp - i0;
      temp->size[1] = c_loop_ub;
      emxEnsureCapacity_real_T(temp, i6);
      for (i6 = 0; i6 < c_loop_ub; i6++) {
        for (i9 = 0; i9 < loop_ub; i9++) {
          temp->data[i9 + temp->size[0] * i6] = original->data[((i3 + i9) +
            original->size[0] * ((i0 + i6) - 1)) - 1];
        }
      }

      e_temp = *temp;
      iv0[0] = loop_ub;
      iv0[1] = c_loop_ub;
      iv0[2] = 1;
      e_temp.size = &iv0[0];
      e_temp.numDimensions = 1;
      sub->data[i + sub->size[0] * j] = b_findDirection(&e_temp);

      /*  Check R for all four quadrants */
      d1 = (double)c_loop_ub / 2.0;
      if (1.0 > d1) {
        f_loop_ub = 0;
      } else {
        f_loop_ub = (int)d1;
      }

      i6 = d_temp->size[0] * d_temp->size[1];
      d_temp->size[0] = b_loop_ub;
      d_temp->size[1] = f_loop_ub;
      emxEnsureCapacity_real_T(d_temp, i6);
      for (i6 = 0; i6 < f_loop_ub; i6++) {
        for (i9 = 0; i9 < b_loop_ub; i9++) {
          d_temp->data[i9 + d_temp->size[0] * i6] = temp->data[i9 + loop_ub * i6];
        }
      }

      i6 = i << 2;
      meanR->data[i6 + (meanR->size[2] << 2) * j] = mean2(d_temp);

      /*  Top left */
      if (1.0 > d1) {
        f_loop_ub = 0;
      } else {
        f_loop_ub = (int)d1;
      }

      i9 = c_temp->size[0] * c_temp->size[1];
      i_loop_ub = i8 - i7;
      c_temp->size[0] = i_loop_ub;
      c_temp->size[1] = f_loop_ub;
      emxEnsureCapacity_real_T(c_temp, i9);
      for (i9 = 0; i9 < f_loop_ub; i9++) {
        for (i18 = 0; i18 < i_loop_ub; i18++) {
          c_temp->data[i18 + c_temp->size[0] * i9] = temp->data[(i7 + i18) +
            loop_ub * i9];
        }
      }

      meanR->data[((i << 2) + (meanR->size[2] << 2) * j) + 2] = mean2(c_temp);

      /*  Top right */
      if (d1 + 1.0 > loop_ub_tmp - i0) {
        i9 = 0;
        i18 = 0;
      } else {
        i9 = (int)(d1 + 1.0) - 1;
        i18 = c_loop_ub;
      }

      i20 = b_temp->size[0] * b_temp->size[1];
      b_temp->size[0] = d_loop_ub;
      f_loop_ub = i18 - i9;
      b_temp->size[1] = f_loop_ub;
      emxEnsureCapacity_real_T(b_temp, i20);
      for (i18 = 0; i18 < f_loop_ub; i18++) {
        for (i20 = 0; i20 < d_loop_ub; i20++) {
          b_temp->data[i20 + b_temp->size[0] * i18] = temp->data[i20 + loop_ub *
            (i9 + i18)];
        }
      }

      meanR->data[((i << 2) + (meanR->size[2] << 2) * j) + 1] = mean2(b_temp);

      /*  Bottom left */
      ref_direction = (double)(loop_ub_tmp - i0) / 2.0 + 1.0;
      if (ref_direction > loop_ub_tmp - i0) {
        i9 = 0;
        i18 = 0;
      } else {
        i9 = (int)ref_direction - 1;
        i18 = c_loop_ub;
      }

      i20 = d_temp->size[0] * d_temp->size[1];
      f_loop_ub = i11 - i10;
      d_temp->size[0] = f_loop_ub;
      i_loop_ub = i18 - i9;
      d_temp->size[1] = i_loop_ub;
      emxEnsureCapacity_real_T(d_temp, i20);
      for (i18 = 0; i18 < i_loop_ub; i18++) {
        for (i20 = 0; i20 < f_loop_ub; i20++) {
          d_temp->data[i20 + d_temp->size[0] * i18] = temp->data[(i10 + i20) +
            loop_ub * (i9 + i18)];
        }
      }

      meanR->data[((i << 2) + (meanR->size[2] << 2) * j) + 3] = mean2(d_temp);

      /*  Bottom right */
      /*  Check G for all four quadrants */
      if (1.0 > d1) {
        f_loop_ub = 0;
      } else {
        f_loop_ub = (int)d1;
      }

      i9 = d_temp->size[0] * d_temp->size[1];
      d_temp->size[0] = e_loop_ub;
      d_temp->size[1] = f_loop_ub;
      emxEnsureCapacity_real_T(d_temp, i9);
      for (i9 = 0; i9 < f_loop_ub; i9++) {
        for (i18 = 0; i18 < e_loop_ub; i18++) {
          d_temp->data[i18 + d_temp->size[0] * i9] = temp->data[(i18 + loop_ub *
            i9) + loop_ub * c_loop_ub];
        }
      }

      meanG->data[i6 + (meanG->size[2] << 2) * j] = mean2(d_temp);

      /*  Top left */
      if (1.0 > d1) {
        f_loop_ub = 0;
      } else {
        f_loop_ub = (int)d1;
      }

      i9 = c_temp->size[0] * c_temp->size[1];
      i_loop_ub = i13 - i12;
      c_temp->size[0] = i_loop_ub;
      c_temp->size[1] = f_loop_ub;
      emxEnsureCapacity_real_T(c_temp, i9);
      for (i9 = 0; i9 < f_loop_ub; i9++) {
        for (i18 = 0; i18 < i_loop_ub; i18++) {
          c_temp->data[i18 + c_temp->size[0] * i9] = temp->data[((i12 + i18) +
            loop_ub * i9) + loop_ub * c_loop_ub];
        }
      }

      meanG->data[((i << 2) + (meanG->size[2] << 2) * j) + 2] = mean2(c_temp);

      /*  Top right */
      ref_direction = (double)(loop_ub_tmp - i0) / 2.0 + 1.0;
      if (ref_direction > loop_ub_tmp - i0) {
        i9 = 0;
        i18 = 0;
      } else {
        i9 = (int)ref_direction - 1;
        i18 = c_loop_ub;
      }

      i20 = b_temp->size[0] * b_temp->size[1];
      b_temp->size[0] = g_loop_ub;
      f_loop_ub = i18 - i9;
      b_temp->size[1] = f_loop_ub;
      emxEnsureCapacity_real_T(b_temp, i20);
      for (i18 = 0; i18 < f_loop_ub; i18++) {
        for (i20 = 0; i20 < g_loop_ub; i20++) {
          b_temp->data[i20 + b_temp->size[0] * i18] = temp->data[(i20 + loop_ub *
            (i9 + i18)) + loop_ub * c_loop_ub];
        }
      }

      meanG->data[((i << 2) + (meanG->size[2] << 2) * j) + 1] = mean2(b_temp);

      /*  Bottom left */
      ref_direction = (double)(loop_ub_tmp - i0) / 2.0 + 1.0;
      if (ref_direction > loop_ub_tmp - i0) {
        i9 = 0;
        i18 = 0;
      } else {
        i9 = (int)ref_direction - 1;
        i18 = c_loop_ub;
      }

      i20 = d_temp->size[0] * d_temp->size[1];
      f_loop_ub = i15 - i14;
      d_temp->size[0] = f_loop_ub;
      i_loop_ub = i18 - i9;
      d_temp->size[1] = i_loop_ub;
      emxEnsureCapacity_real_T(d_temp, i20);
      for (i18 = 0; i18 < i_loop_ub; i18++) {
        for (i20 = 0; i20 < f_loop_ub; i20++) {
          d_temp->data[i20 + d_temp->size[0] * i18] = temp->data[((i14 + i20) +
            loop_ub * (i9 + i18)) + loop_ub * c_loop_ub];
        }
      }

      meanG->data[((i << 2) + (meanG->size[2] << 2) * j) + 3] = mean2(d_temp);

      /*  Bottom right */
      /*  Check B for all four quadrants */
      if (1.0 > d1) {
        f_loop_ub = 0;
      } else {
        f_loop_ub = (int)d1;
      }

      i9 = d_temp->size[0] * d_temp->size[1];
      d_temp->size[0] = h_loop_ub;
      d_temp->size[1] = f_loop_ub;
      emxEnsureCapacity_real_T(d_temp, i9);
      for (i9 = 0; i9 < f_loop_ub; i9++) {
        for (i18 = 0; i18 < h_loop_ub; i18++) {
          d_temp->data[i18 + d_temp->size[0] * i9] = temp->data[(i18 + loop_ub *
            i9) + ((loop_ub * c_loop_ub) << 1)];
        }
      }

      meanB->data[i6 + (meanB->size[2] << 2) * j] = mean2(d_temp);

      /*  Top left */
      if (1.0 > d1) {
        f_loop_ub = 0;
      } else {
        f_loop_ub = (int)d1;
      }

      i6 = c_temp->size[0] * c_temp->size[1];
      i_loop_ub = i17 - i16;
      c_temp->size[0] = i_loop_ub;
      c_temp->size[1] = f_loop_ub;
      emxEnsureCapacity_real_T(c_temp, i6);
      for (i6 = 0; i6 < f_loop_ub; i6++) {
        for (i9 = 0; i9 < i_loop_ub; i9++) {
          c_temp->data[i9 + c_temp->size[0] * i6] = temp->data[((i16 + i9) +
            loop_ub * i6) + ((loop_ub * c_loop_ub) << 1)];
        }
      }

      meanB->data[((i << 2) + (meanB->size[2] << 2) * j) + 2] = mean2(c_temp);

      /*  Top right */
      d1 = (double)(loop_ub_tmp - i0) / 2.0 + 1.0;
      if (d1 > loop_ub_tmp - i0) {
        i6 = 0;
        i9 = 0;
      } else {
        i6 = (int)d1 - 1;
        i9 = c_loop_ub;
      }

      i18 = b_temp->size[0] * b_temp->size[1];
      b_temp->size[0] = j_loop_ub;
      f_loop_ub = i9 - i6;
      b_temp->size[1] = f_loop_ub;
      emxEnsureCapacity_real_T(b_temp, i18);
      for (i9 = 0; i9 < f_loop_ub; i9++) {
        for (i18 = 0; i18 < j_loop_ub; i18++) {
          b_temp->data[i18 + b_temp->size[0] * i9] = temp->data[(i18 + loop_ub *
            (i6 + i9)) + ((loop_ub * c_loop_ub) << 1)];
        }
      }

      meanB->data[((i << 2) + (meanB->size[2] << 2) * j) + 1] = mean2(b_temp);

      /*  Bottom left */
      d1 = (double)(loop_ub_tmp - i0) / 2.0 + 1.0;
      if (d1 > loop_ub_tmp - i0) {
        i0 = 0;
        loop_ub_tmp = 0;
      } else {
        i0 = (int)d1 - 1;
        loop_ub_tmp = c_loop_ub;
      }

      i6 = d_temp->size[0] * d_temp->size[1];
      f_loop_ub = i5 - i19;
      d_temp->size[0] = f_loop_ub;
      i_loop_ub = loop_ub_tmp - i0;
      d_temp->size[1] = i_loop_ub;
      emxEnsureCapacity_real_T(d_temp, i6);
      for (loop_ub_tmp = 0; loop_ub_tmp < i_loop_ub; loop_ub_tmp++) {
        for (i6 = 0; i6 < f_loop_ub; i6++) {
          d_temp->data[i6 + d_temp->size[0] * loop_ub_tmp] = temp->data[((i19 +
            i6) + loop_ub * (i0 + loop_ub_tmp)) + ((loop_ub * c_loop_ub) << 1)];
        }
      }

      meanB->data[((i << 2) + (meanB->size[2] << 2) * j) + 3] = mean2(d_temp);

      /*  Bottom right */
    }
  }

  emxFree_real_T(&c_temp);
  emxFree_real_T(&b_temp);
  emxInit_real_T(&corrected, 5);

  /*  STEP 4: Compare RGB values for sub-areas with compressed image's RGB values */
  /*  Calculate mean RGB value for the compressed image and compare with mean */
  /*  luminance values for the sub-areas */
  /*  Create a vector containing corrected compressed images that will later be */
  /*  used as building stones for our reproducted image */
  /*  (Three first dimensions let us use RGB image as element, two last */
  /*  dimensions represent the number of sub areas in the original image) */
  i0 = corrected->size[0] * corrected->size[1] * corrected->size[2] *
    corrected->size[3] * corrected->size[4];
  corrected->size[0] = (int)subSize_idx_0;
  corrected->size[1] = (int)subSize_idx_1;
  corrected->size[2] = 3;
  corrected->size[3] = i1;
  corrected->size[4] = i2;
  emxEnsureCapacity_real_T(corrected, i0);
  loop_ub = (int)subSize_idx_0 * (int)subSize_idx_1 * 3 * i1 * i2;
  for (i0 = 0; i0 < loop_ub; i0++) {
    corrected->data[i0] = 0.0;
  }

  emxInit_real_T(&f_temp, 3);
  emxInit_int32_T(&r0, 1);
  emxInit_int32_T(&r1, 1);
  emxInit_real_T(&g_temp, 2);
  for (i = 0; i < i1; i++) {
    for (j = 0; j < i2; j++) {
      if (sub->data[i + sub->size[0] * j] == 0.0) {
        i0 = f_temp->size[0] * f_temp->size[1] * f_temp->size[2];
        f_temp->size[0] = refA->size[0];
        f_temp->size[1] = refA->size[1];
        f_temp->size[2] = 1;
        emxEnsureCapacity_real_T(f_temp, i0);
        loop_ub = refA->size[0] * refA->size[1];
        for (i0 = 0; i0 < loop_ub; i0++) {
          f_temp->data[i0] = refA->data[i0];
        }
      } else if (sub->data[i + sub->size[0] * j] == 2.0) {
        i0 = f_temp->size[0] * f_temp->size[1] * f_temp->size[2];
        f_temp->size[0] = refB->size[0];
        f_temp->size[1] = refB->size[1];
        f_temp->size[2] = 1;
        emxEnsureCapacity_real_T(f_temp, i0);
        loop_ub = refB->size[0] * refB->size[1];
        for (i0 = 0; i0 < loop_ub; i0++) {
          f_temp->data[i0] = refB->data[i0];
        }
      } else if (sub->data[i + sub->size[0] * j] == 1.0) {
        i0 = f_temp->size[0] * f_temp->size[1] * f_temp->size[2];
        f_temp->size[0] = refC->size[0];
        f_temp->size[1] = refC->size[1];
        f_temp->size[2] = 1;
        emxEnsureCapacity_real_T(f_temp, i0);
        loop_ub = refC->size[0] * refC->size[1];
        for (i0 = 0; i0 < loop_ub; i0++) {
          f_temp->data[i0] = refC->data[i0];
        }
      } else {
        i0 = f_temp->size[0] * f_temp->size[1] * f_temp->size[2];
        f_temp->size[0] = refD->size[0];
        f_temp->size[1] = refD->size[1];
        f_temp->size[2] = 1;
        emxEnsureCapacity_real_T(f_temp, i0);
        loop_ub = refD->size[0] * refD->size[1];
        for (i0 = 0; i0 < loop_ub; i0++) {
          f_temp->data[i0] = refD->data[i0];
        }
      }

      /*  Get mean R value for each quadrant of compressed image */
      /*          % Top left */
      /*     % Top right */
      /*        % Bottom left */
      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        b_loop_ub = 0;
      } else {
        b_loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[0] / 2.0;
      if (d0 > f_temp->size[0]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        d_loop_ub = 0;
      } else {
        d_loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        e_loop_ub = 0;
      } else {
        e_loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (d0 > f_temp->size[1]) {
        i4 = 0;
        i5 = 0;
      } else {
        i4 = (int)d0 - 1;
        i5 = f_temp->size[1];
      }

      d0 = (double)f_temp->size[0] / 2.0;
      if (d0 > f_temp->size[0]) {
        i7 = 0;
        i8 = 0;
      } else {
        i7 = (int)d0 - 1;
        i8 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (d0 > f_temp->size[1]) {
        i10 = 0;
        i11 = 0;
      } else {
        i10 = (int)d0 - 1;
        i11 = f_temp->size[1];
      }

      /*  Bottom right */
      i12 = temp->size[0] * temp->size[1];
      temp->size[0] = loop_ub;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i12);
      for (i12 = 0; i12 < b_loop_ub; i12++) {
        for (i13 = 0; i13 < loop_ub; i13++) {
          temp->data[i13 + temp->size[0] * i12] = f_temp->data[i13 +
            f_temp->size[0] * i12];
        }
      }

      i12 = d_temp->size[0] * d_temp->size[1];
      loop_ub = i3 - i0;
      d_temp->size[0] = loop_ub;
      d_temp->size[1] = d_loop_ub;
      emxEnsureCapacity_real_T(d_temp, i12);
      for (i3 = 0; i3 < d_loop_ub; i3++) {
        for (i12 = 0; i12 < loop_ub; i12++) {
          d_temp->data[i12 + d_temp->size[0] * i3] = f_temp->data[(i0 + i12) +
            f_temp->size[0] * i3];
        }
      }

      i0 = original->size[0] * original->size[1];
      original->size[0] = e_loop_ub;
      loop_ub = i5 - i4;
      original->size[1] = loop_ub;
      emxEnsureCapacity_real_T(original, i0);
      for (i0 = 0; i0 < loop_ub; i0++) {
        for (i3 = 0; i3 < e_loop_ub; i3++) {
          original->data[i3 + original->size[0] * i0] = f_temp->data[i3 +
            f_temp->size[0] * (i4 + i0)];
        }
      }

      i0 = g_temp->size[0] * g_temp->size[1];
      loop_ub = i8 - i7;
      g_temp->size[0] = loop_ub;
      b_loop_ub = i11 - i10;
      g_temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(g_temp, i0);
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i3 = 0; i3 < loop_ub; i3++) {
          g_temp->data[i3 + g_temp->size[0] * i0] = f_temp->data[(i7 + i3) +
            f_temp->size[0] * (i10 + i0)];
        }
      }

      d0 = mean2(temp);
      d1 = mean2(d_temp);
      ref_direction = mean2(original);
      d2 = mean2(g_temp);
      delta_R = meanR->data[0] - d0;
      delta_R_idx_0 = delta_R;
      delta_R = meanR->data[1] - ref_direction;
      delta_R_idx_1 = delta_R;
      delta_R = meanR->data[2] - d1;
      delta_R_idx_2 = delta_R;
      delta_R = meanR->data[3] - d2;

      /*  Get mean G value for each quadrant of compressed image */
      /*          % Top left */
      /*     % Top right */
      /*        % Bottom left */
      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        b_loop_ub = 0;
      } else {
        b_loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[0] / 2.0;
      if (d0 > f_temp->size[0]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        d_loop_ub = 0;
      } else {
        d_loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        e_loop_ub = 0;
      } else {
        e_loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (d0 > f_temp->size[1]) {
        i4 = 0;
        i5 = 0;
      } else {
        i4 = (int)d0 - 1;
        i5 = f_temp->size[1];
      }

      d0 = (double)f_temp->size[0] / 2.0;
      if (d0 > f_temp->size[0]) {
        i7 = 0;
        i8 = 0;
      } else {
        i7 = (int)d0 - 1;
        i8 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (d0 > f_temp->size[1]) {
        i10 = 0;
        i11 = 0;
      } else {
        i10 = (int)d0 - 1;
        i11 = f_temp->size[1];
      }

      /*  Bottom right */
      i12 = temp->size[0] * temp->size[1];
      temp->size[0] = loop_ub;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i12);
      for (i12 = 0; i12 < b_loop_ub; i12++) {
        for (i13 = 0; i13 < loop_ub; i13++) {
          temp->data[i13 + temp->size[0] * i12] = f_temp->data[(i13 +
            f_temp->size[0] * i12) + f_temp->size[0] * f_temp->size[1]];
        }
      }

      i12 = d_temp->size[0] * d_temp->size[1];
      loop_ub = i3 - i0;
      d_temp->size[0] = loop_ub;
      d_temp->size[1] = d_loop_ub;
      emxEnsureCapacity_real_T(d_temp, i12);
      for (i3 = 0; i3 < d_loop_ub; i3++) {
        for (i12 = 0; i12 < loop_ub; i12++) {
          d_temp->data[i12 + d_temp->size[0] * i3] = f_temp->data[((i0 + i12) +
            f_temp->size[0] * i3) + f_temp->size[0] * f_temp->size[1]];
        }
      }

      i0 = original->size[0] * original->size[1];
      original->size[0] = e_loop_ub;
      loop_ub = i5 - i4;
      original->size[1] = loop_ub;
      emxEnsureCapacity_real_T(original, i0);
      for (i0 = 0; i0 < loop_ub; i0++) {
        for (i3 = 0; i3 < e_loop_ub; i3++) {
          original->data[i3 + original->size[0] * i0] = f_temp->data[(i3 +
            f_temp->size[0] * (i4 + i0)) + f_temp->size[0] * f_temp->size[1]];
        }
      }

      i0 = g_temp->size[0] * g_temp->size[1];
      loop_ub = i8 - i7;
      g_temp->size[0] = loop_ub;
      b_loop_ub = i11 - i10;
      g_temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(g_temp, i0);
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i3 = 0; i3 < loop_ub; i3++) {
          g_temp->data[i3 + g_temp->size[0] * i0] = f_temp->data[((i7 + i3) +
            f_temp->size[0] * (i10 + i0)) + f_temp->size[0] * f_temp->size[1]];
        }
      }

      d0 = mean2(temp);
      d1 = mean2(d_temp);
      ref_direction = mean2(original);
      d2 = mean2(g_temp);
      delta_G = meanG->data[0] - d0;
      delta_G_idx_0 = delta_G;
      delta_G = meanG->data[1] - ref_direction;
      delta_G_idx_1 = delta_G;
      delta_G = meanG->data[2] - d1;
      delta_G_idx_2 = delta_G;
      delta_G = meanG->data[3] - d2;

      /*  Get mean B value for each quadrant of compressed image */
      /*          % Top left */
      /*     % Top right */
      /*        % Bottom left */
      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        b_loop_ub = 0;
      } else {
        b_loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[0] / 2.0;
      if (d0 > f_temp->size[0]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        d_loop_ub = 0;
      } else {
        d_loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        e_loop_ub = 0;
      } else {
        e_loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (d0 > f_temp->size[1]) {
        i4 = 0;
        i5 = 0;
      } else {
        i4 = (int)d0 - 1;
        i5 = f_temp->size[1];
      }

      d0 = (double)f_temp->size[0] / 2.0;
      if (d0 > f_temp->size[0]) {
        i7 = 0;
        i8 = 0;
      } else {
        i7 = (int)d0 - 1;
        i8 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (d0 > f_temp->size[1]) {
        i10 = 0;
        i11 = 0;
      } else {
        i10 = (int)d0 - 1;
        i11 = f_temp->size[1];
      }

      /*  Bottom right */
      i12 = temp->size[0] * temp->size[1];
      temp->size[0] = loop_ub;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i12);
      for (i12 = 0; i12 < b_loop_ub; i12++) {
        for (i13 = 0; i13 < loop_ub; i13++) {
          temp->data[i13 + temp->size[0] * i12] = f_temp->data[(i13 +
            f_temp->size[0] * i12) + ((f_temp->size[0] * f_temp->size[1]) << 1)];
        }
      }

      i12 = d_temp->size[0] * d_temp->size[1];
      loop_ub = i3 - i0;
      d_temp->size[0] = loop_ub;
      d_temp->size[1] = d_loop_ub;
      emxEnsureCapacity_real_T(d_temp, i12);
      for (i3 = 0; i3 < d_loop_ub; i3++) {
        for (i12 = 0; i12 < loop_ub; i12++) {
          d_temp->data[i12 + d_temp->size[0] * i3] = f_temp->data[((i0 + i12) +
            f_temp->size[0] * i3) + ((f_temp->size[0] * f_temp->size[1]) << 1)];
        }
      }

      i0 = original->size[0] * original->size[1];
      original->size[0] = e_loop_ub;
      loop_ub = i5 - i4;
      original->size[1] = loop_ub;
      emxEnsureCapacity_real_T(original, i0);
      for (i0 = 0; i0 < loop_ub; i0++) {
        for (i3 = 0; i3 < e_loop_ub; i3++) {
          original->data[i3 + original->size[0] * i0] = f_temp->data[(i3 +
            f_temp->size[0] * (i4 + i0)) + ((f_temp->size[0] * f_temp->size[1]) <<
            1)];
        }
      }

      i0 = g_temp->size[0] * g_temp->size[1];
      loop_ub = i8 - i7;
      g_temp->size[0] = loop_ub;
      b_loop_ub = i11 - i10;
      g_temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(g_temp, i0);
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i3 = 0; i3 < loop_ub; i3++) {
          g_temp->data[i3 + g_temp->size[0] * i0] = f_temp->data[((i7 + i3) +
            f_temp->size[0] * (i10 + i0)) + ((f_temp->size[0] * f_temp->size[1])
            << 1)];
        }
      }

      d0 = mean2(temp);
      d1 = mean2(d_temp);
      ref_direction = mean2(original);
      d2 = mean2(g_temp);
      delta_B = meanB->data[0] - d0;
      delta_B_idx_0 = delta_B;
      delta_B = meanB->data[1] - ref_direction;
      delta_B_idx_1 = delta_B;
      delta_B = meanB->data[2] - d1;
      ref_direction = delta_B;
      delta_B = meanB->data[3] - d2;

      /*  Add mean R value for each quadrant to corresponding area */
      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        b_loop_ub = 0;
      } else {
        b_loop_ub = (int)d0;
      }

      i0 = temp->size[0] * temp->size[1];
      temp->size[0] = loop_ub;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i0);
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i3 = 0; i3 < loop_ub; i3++) {
          temp->data[i3 + temp->size[0] * i0] = f_temp->data[i3 + f_temp->size[0]
            * i0] + delta_R_idx_0;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[i3 + f_temp->size[0] * i0] = temp->data[i3 + temp->size[0]
            * i0];
        }
      }

      /*  Top left */
      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i4 = 0;
      } else {
        i4 = (int)d0 - 1;
      }

      i5 = temp->size[0] * temp->size[1];
      b_loop_ub = i3 - i0;
      temp->size[0] = b_loop_ub;
      temp->size[1] = loop_ub;
      emxEnsureCapacity_real_T(temp, i5);
      for (i3 = 0; i3 < loop_ub; i3++) {
        for (i5 = 0; i5 < b_loop_ub; i5++) {
          temp->data[i5 + temp->size[0] * i3] = f_temp->data[(i0 + i5) +
            f_temp->size[0] * i3] + delta_R_idx_2;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[(i4 + i3) + f_temp->size[0] * i0] = temp->data[i3 +
            temp->size[0] * i0];
        }
      }

      /*  Top right */
      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[1];
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i4 = 0;
      } else {
        i4 = (int)d0 - 1;
      }

      i5 = temp->size[0] * temp->size[1];
      temp->size[0] = loop_ub;
      b_loop_ub = i3 - i0;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i5);
      for (i3 = 0; i3 < b_loop_ub; i3++) {
        for (i5 = 0; i5 < loop_ub; i5++) {
          temp->data[i5 + temp->size[0] * i3] = f_temp->data[i5 + f_temp->size[0]
            * (i0 + i3)] + delta_R_idx_1;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[i3 + f_temp->size[0] * (i4 + i0)] = temp->data[i3 +
            temp->size[0] * i0];
        }
      }

      /*  Bottom left */
      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i4 = 0;
        i5 = 0;
      } else {
        i4 = (int)d0 - 1;
        i5 = f_temp->size[1];
      }

      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i7 = 0;
      } else {
        i7 = (int)d0 - 1;
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i8 = 0;
      } else {
        i8 = (int)d0 - 1;
      }

      i10 = temp->size[0] * temp->size[1];
      loop_ub = i3 - i0;
      temp->size[0] = loop_ub;
      b_loop_ub = i5 - i4;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i10);
      for (i3 = 0; i3 < b_loop_ub; i3++) {
        for (i5 = 0; i5 < loop_ub; i5++) {
          temp->data[i5 + temp->size[0] * i3] = f_temp->data[(i0 + i5) +
            f_temp->size[0] * (i4 + i3)] + delta_R;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[(i7 + i3) + f_temp->size[0] * (i8 + i0)] = temp->data[i3
            + temp->size[0] * i0];
        }
      }

      /*  Bottom right */
      /*  Add mean G value for each quadrant to corresponding area */
      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        b_loop_ub = 0;
      } else {
        b_loop_ub = (int)d0;
      }

      i0 = temp->size[0] * temp->size[1];
      temp->size[0] = loop_ub;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i0);
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i3 = 0; i3 < loop_ub; i3++) {
          temp->data[i3 + temp->size[0] * i0] = f_temp->data[(i3 + f_temp->size
            [0] * i0) + f_temp->size[0] * f_temp->size[1]] + delta_G_idx_0;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[(i3 + f_temp->size[0] * i0) + f_temp->size[0] *
            f_temp->size[1]] = temp->data[i3 + temp->size[0] * i0];
        }
      }

      /*  Top left */
      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i4 = 0;
      } else {
        i4 = (int)d0 - 1;
      }

      i5 = temp->size[0] * temp->size[1];
      b_loop_ub = i3 - i0;
      temp->size[0] = b_loop_ub;
      temp->size[1] = loop_ub;
      emxEnsureCapacity_real_T(temp, i5);
      for (i3 = 0; i3 < loop_ub; i3++) {
        for (i5 = 0; i5 < b_loop_ub; i5++) {
          temp->data[i5 + temp->size[0] * i3] = f_temp->data[((i0 + i5) +
            f_temp->size[0] * i3) + f_temp->size[0] * f_temp->size[1]] +
            delta_G_idx_2;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[((i4 + i3) + f_temp->size[0] * i0) + f_temp->size[0] *
            f_temp->size[1]] = temp->data[i3 + temp->size[0] * i0];
        }
      }

      /*  Top right */
      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[1];
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i4 = 0;
      } else {
        i4 = (int)d0 - 1;
      }

      i5 = temp->size[0] * temp->size[1];
      temp->size[0] = loop_ub;
      b_loop_ub = i3 - i0;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i5);
      for (i3 = 0; i3 < b_loop_ub; i3++) {
        for (i5 = 0; i5 < loop_ub; i5++) {
          temp->data[i5 + temp->size[0] * i3] = f_temp->data[(i5 + f_temp->size
            [0] * (i0 + i3)) + f_temp->size[0] * f_temp->size[1]] +
            delta_G_idx_1;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[(i3 + f_temp->size[0] * (i4 + i0)) + f_temp->size[0] *
            f_temp->size[1]] = temp->data[i3 + temp->size[0] * i0];
        }
      }

      /*  Bottom left */
      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i4 = 0;
        i5 = 0;
      } else {
        i4 = (int)d0 - 1;
        i5 = f_temp->size[1];
      }

      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i7 = 0;
      } else {
        i7 = (int)d0 - 1;
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i8 = 0;
      } else {
        i8 = (int)d0 - 1;
      }

      i10 = temp->size[0] * temp->size[1];
      loop_ub = i3 - i0;
      temp->size[0] = loop_ub;
      b_loop_ub = i5 - i4;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i10);
      for (i3 = 0; i3 < b_loop_ub; i3++) {
        for (i5 = 0; i5 < loop_ub; i5++) {
          temp->data[i5 + temp->size[0] * i3] = f_temp->data[((i0 + i5) +
            f_temp->size[0] * (i4 + i3)) + f_temp->size[0] * f_temp->size[1]] +
            delta_G;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[((i7 + i3) + f_temp->size[0] * (i8 + i0)) + f_temp->size
            [0] * f_temp->size[1]] = temp->data[i3 + temp->size[0] * i0];
        }
      }

      /*  Bottom right */
      /*  Add mean B value for each quadrant to corresponding area */
      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        b_loop_ub = 0;
      } else {
        b_loop_ub = (int)d0;
      }

      i0 = temp->size[0] * temp->size[1];
      temp->size[0] = loop_ub;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i0);
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i3 = 0; i3 < loop_ub; i3++) {
          temp->data[i3 + temp->size[0] * i0] = f_temp->data[(i3 + f_temp->size
            [0] * i0) + ((f_temp->size[0] * f_temp->size[1]) << 1)] +
            delta_B_idx_0;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[(i3 + f_temp->size[0] * i0) + ((f_temp->size[0] *
            f_temp->size[1]) << 1)] = temp->data[i3 + temp->size[0] * i0];
        }
      }

      /*  Top left */
      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i4 = 0;
      } else {
        i4 = (int)d0 - 1;
      }

      i5 = temp->size[0] * temp->size[1];
      b_loop_ub = i3 - i0;
      temp->size[0] = b_loop_ub;
      temp->size[1] = loop_ub;
      emxEnsureCapacity_real_T(temp, i5);
      for (i3 = 0; i3 < loop_ub; i3++) {
        for (i5 = 0; i5 < b_loop_ub; i5++) {
          temp->data[i5 + temp->size[0] * i3] = f_temp->data[((i0 + i5) +
            f_temp->size[0] * i3) + ((f_temp->size[0] * f_temp->size[1]) << 1)]
            + ref_direction;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[((i4 + i3) + f_temp->size[0] * i0) + ((f_temp->size[0] *
            f_temp->size[1]) << 1)] = temp->data[i3 + temp->size[0] * i0];
        }
      }

      /*  Top right */
      d0 = (double)f_temp->size[0] / 2.0;
      if (1.0 > d0) {
        loop_ub = 0;
      } else {
        loop_ub = (int)d0;
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[1];
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i4 = 0;
      } else {
        i4 = (int)d0 - 1;
      }

      i5 = temp->size[0] * temp->size[1];
      temp->size[0] = loop_ub;
      b_loop_ub = i3 - i0;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i5);
      for (i3 = 0; i3 < b_loop_ub; i3++) {
        for (i5 = 0; i5 < loop_ub; i5++) {
          temp->data[i5 + temp->size[0] * i3] = f_temp->data[(i5 + f_temp->size
            [0] * (i0 + i3)) + ((f_temp->size[0] * f_temp->size[1]) << 1)] +
            delta_B_idx_1;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[(i3 + f_temp->size[0] * (i4 + i0)) + ((f_temp->size[0] *
            f_temp->size[1]) << 1)] = temp->data[i3 + temp->size[0] * i0];
        }
      }

      /*  Bottom left */
      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i0 = 0;
        i3 = 0;
      } else {
        i0 = (int)d0 - 1;
        i3 = f_temp->size[0];
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i4 = 0;
        i5 = 0;
      } else {
        i4 = (int)d0 - 1;
        i5 = f_temp->size[1];
      }

      d0 = (double)f_temp->size[0] / 2.0 + 1.0;
      if (d0 > f_temp->size[0]) {
        i7 = 0;
      } else {
        i7 = (int)d0 - 1;
      }

      d0 = (double)f_temp->size[1] / 2.0 + 1.0;
      if (d0 > f_temp->size[1]) {
        i8 = 0;
      } else {
        i8 = (int)d0 - 1;
      }

      i10 = temp->size[0] * temp->size[1];
      loop_ub = i3 - i0;
      temp->size[0] = loop_ub;
      b_loop_ub = i5 - i4;
      temp->size[1] = b_loop_ub;
      emxEnsureCapacity_real_T(temp, i10);
      for (i3 = 0; i3 < b_loop_ub; i3++) {
        for (i5 = 0; i5 < loop_ub; i5++) {
          temp->data[i5 + temp->size[0] * i3] = f_temp->data[((i0 + i5) +
            f_temp->size[0] * (i4 + i3)) + ((f_temp->size[0] * f_temp->size[1]) <<
            1)] + delta_B;
        }
      }

      loop_ub = temp->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        b_loop_ub = temp->size[0];
        for (i3 = 0; i3 < b_loop_ub; i3++) {
          f_temp->data[((i7 + i3) + f_temp->size[0] * (i8 + i0)) +
            ((f_temp->size[0] * f_temp->size[1]) << 1)] = temp->data[i3 +
            temp->size[0] * i0];
        }
      }

      /*  Bottom right */
      loop_ub = corrected->size[0];
      i0 = r0->size[0];
      r0->size[0] = loop_ub;
      emxEnsureCapacity_int32_T(r0, i0);
      for (i0 = 0; i0 < loop_ub; i0++) {
        r0->data[i0] = i0;
      }

      loop_ub = corrected->size[1];
      i0 = r1->size[0];
      r1->size[0] = loop_ub;
      emxEnsureCapacity_int32_T(r1, i0);
      for (i0 = 0; i0 < loop_ub; i0++) {
        r1->data[i0] = i0;
      }

      loop_ub_tmp = r0->size[0];
      loop_ub = r1->size[0];
      for (i0 = 0; i0 < 3; i0++) {
        for (i3 = 0; i3 < loop_ub; i3++) {
          for (i4 = 0; i4 < loop_ub_tmp; i4++) {
            corrected->data[(r0->data[i4] + corrected->size[0] * r1->data[i3]) +
              corrected->size[0] * corrected->size[1] * i0] = f_temp->data[(i4 +
              loop_ub_tmp * i3) + loop_ub_tmp * loop_ub * i0];
          }
        }
      }
    }
  }

  emxFree_real_T(&g_temp);
  emxFree_real_T(&d_temp);
  emxFree_int32_T(&r1);
  emxFree_int32_T(&r0);
  emxFree_real_T(&temp);
  emxFree_real_T(&f_temp);
  emxFree_real_T(&meanB);
  emxFree_real_T(&meanG);
  emxFree_real_T(&meanR);
  emxFree_real_T(&refD);
  emxFree_real_T(&refC);
  emxFree_real_T(&refB);
  emxFree_real_T(&refA);
  emxFree_real_T(&sub);
  emxFree_real_T(&original);

  /*  STEP 5: Rebuild original image with corrected sub-areas */
  /*  Get rebuild size and create a workspace of zeros */
  i0 = rebuild_final->size[0] * rebuild_final->size[1] * rebuild_final->size[2];
  rebuild_final->size[0] = (int)originalSize_idx_0;
  rebuild_final->size[1] = (int)originalSize_idx_1;
  rebuild_final->size[2] = 3;
  emxEnsureCapacity_real_T(rebuild_final, i0);
  loop_ub = (int)originalSize_idx_0 * (int)originalSize_idx_1 * 3;
  for (i0 = 0; i0 < loop_ub; i0++) {
    rebuild_final->data[i0] = 0.0;
  }

  for (i = 0; i < i1; i++) {
    for (j = 0; j < i2; j++) {
      d0 = 1.0 + ((double)subSize_idx_0 * (1.0 + (double)i) - (double)
                  subSize_idx_0);
      if (d0 > (double)subSize_idx_0 * (1.0 + (double)i)) {
        i0 = 0;
      } else {
        i0 = (int)d0 - 1;
      }

      d0 = 1.0 + ((double)subSize_idx_1 * (1.0 + (double)j) - (double)
                  subSize_idx_1);
      if (d0 > (double)subSize_idx_1 * (1.0 + (double)j)) {
        i3 = 0;
      } else {
        i3 = (int)d0 - 1;
      }

      loop_ub = corrected->size[0] - 1;
      b_loop_ub = corrected->size[1] - 1;
      for (i4 = 0; i4 < 3; i4++) {
        for (i5 = 0; i5 <= b_loop_ub; i5++) {
          for (i7 = 0; i7 <= loop_ub; i7++) {
            rebuild_final->data[((i0 + i7) + rebuild_final->size[0] * (i3 + i5))
              + rebuild_final->size[0] * rebuild_final->size[1] * i4] =
              corrected->data[(((i7 + corrected->size[0] * i5) + corrected->
                                size[0] * corrected->size[1] * i4) +
                               corrected->size[0] * corrected->size[1] * 3 * i)
              + corrected->size[0] * corrected->size[1] * 3 * corrected->size[3]
              * j];
          }
        }
      }
    }
  }

  emxFree_real_T(&corrected);

  /*  STEP 6: Display the iamges */
  /*  subplot(1,2,1)%(total_rows,total_cols,current_index) */
  /*  imshow(original) */
  /*  title('Original image'); */
  /*  subplot(1,2,2) */
  /*  imshow(rebuild) */
  /*  title('Rebuilt image'); */
  /*   */
  /*  rot_rebuild = rebuild; */
  /*   */
  /*  % figure */
  /*  % imshow(rebuild) */
  /*  % figure */
  /*  % imshow(original) */
  /*   */
  /*  [SNR, MSE, deltaE, SCIELAB] = Evaluation(original, rebuild); */
  /*  MSE */
  /*  SNR */
  /*  mean2(deltaE) */
}

/* End of code generation (Version7_corrRot.cpp) */
