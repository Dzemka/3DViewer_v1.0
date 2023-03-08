#include <math.h>

#include "../include/viewer.h"

void moveArray(double *array, size_t size, double move, int axes) {
  size_t i;

  i = 0;
  if (move <= -100000 || move >= 100000) return;
  while (i < size) {
    array[i + axes] += move;
    i += 3;
  }
}

void rotateArray(double *array, size_t size, double rotate, int axes) {
  size_t i;
  double *m;
  double v1;
  double v2;
  int el1;
  int el2;

  if (rotate <= -100000 || rotate >= 100000) return;
  el1 = (axes + 1) % 3;
  el2 = (axes + 2) % 3;
  i = 0;
  m = array;
  rotate = rotate * M_PI / 180;
  while (i < size) {
    v1 = m[i + el1] * cos(rotate) + m[i + el2] * sin(rotate);
    v2 = -1 * m[i + el1] * sin(rotate) + m[i + el2] * cos(rotate);
    m[i + el1] = v1;
    m[i + el2] = v2;
    i += 3;
  }
}

void scaleArray(double *array, size_t size, double scale) {
  size_t i;

  i = 0;
  if (scale <= 0 || scale >= 100000) return;
  while (i < size) {
    array[i] *= scale;
    i++;
  }
}
