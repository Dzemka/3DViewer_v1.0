#include "../include/imageview.h"

void ImageView::initializeTransformation() {
  transform.xTra = 0;
  transform.yTra = 0;
  transform.zTra = 0;
  transform.xRot = 0;
  transform.yRot = 0;
  transform.zRot = 0;
  transform.nSca = 1;
  transform.rSca = 1;
  distanceZ = 0;
  pointCount = 0;
  indexSize = 0;
  vertexArray = nullptr;
  indexList = nullptr;
}
