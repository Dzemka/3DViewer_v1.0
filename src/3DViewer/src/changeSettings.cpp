#include "../include/imageview.h"

void ImageView::setLanguage(int language) { this->language = language; }

int ImageView::getLanguage() { return (language); }

int ImageView::getProjection() { return (projection); }

void ImageView::setProjection(int projection) {
  if (getProjection() != projection) {
    this->projection = projection;
    update();
  }
}

void ImageView::setScale(double scale) {
  if (scale == 0) {
    scaleArray(vertexArray, pointCount * 3, 1 / transform.nSca);
    transform.nSca = 1;
  } else {
    transform.nSca *= scale;
    scaleArray(vertexArray, pointCount * 3, scale);
  }
}

void ImageView::setMovingX(double traX) {
  if (!traX) {
    moveArray(vertexArray, pointCount * 3, -transform.xTra, 0);
    transform.xTra = 0;
  } else {
    transform.xTra += traX;
    moveArray(vertexArray, pointCount * 3, traX, 0);
  }
}

void ImageView::setMovingY(double traY) {
  if (!traY) {
    moveArray(vertexArray, pointCount * 3, -transform.yTra, 1);
    transform.yTra = 0;
  } else {
    transform.yTra += traY;
    moveArray(vertexArray, pointCount * 3, traY, 1);
  }
}

void ImageView::setMovingZ(double traZ) {
  if (!traZ) {
    moveArray(vertexArray, pointCount * 3, -transform.zTra, 2);
    transform.zTra = 0;
  } else {
    transform.zTra += traZ;
    moveArray(vertexArray, pointCount * 3, traZ, 2);
  }
}

void ImageView::setRotationX(double rotX) {
  if (!rotX) {
    rotateArray(vertexArray, pointCount * 3, -transform.xRot, 0);
    transform.xRot = 0;
  } else {
    transform.xRot += rotX;
    rotateArray(vertexArray, pointCount * 3, rotX, 0);
  }
}

void ImageView::setRotationY(double rotY) {
  if (!rotY) {
    rotateArray(vertexArray, pointCount * 3, -transform.yRot, 1);
    transform.yRot = 0;
  } else {
    transform.yRot += rotY;
    rotateArray(vertexArray, pointCount * 3, rotY, 1);
  }
}

void ImageView::setRotationZ(double rotZ) {
  if (!rotZ) {
    rotateArray(vertexArray, pointCount * 3, -transform.zRot, 2);
    transform.zRot = 0;
  } else {
    transform.zRot += rotZ;
    rotateArray(vertexArray, pointCount * 3, rotZ, 2);
  }
}

void ImageView::setBckgColor(QColor color) { backgroundColor = color; }

QColor *ImageView::getBckgColor() { return (&backgroundColor); }

void ImageView::setEdgeColor(QColor color) { edgeColor = color; }

QColor *ImageView::getEdgeColor() { return (&edgeColor); }

void ImageView::setVertexColor(QColor color) { vertexColor = color; }

QColor *ImageView::getVertexColor() { return (&vertexColor); }

void ImageView::setEdgeThickness(int thickness) { edgeThickness = thickness; }

void ImageView::setVertexSize(int size) { vertexSize = size; }

void ImageView::setEdgeTypeSolid() { edgeType = EDGE_TYPE_SOLID; }

void ImageView::setEdgeTypeDashed() { edgeType = EDGE_TYPE_DASHED; }

double ImageView::getSca() { return (transform.rSca); }

int ImageView::getEdgeThickness() { return (edgeThickness); }

int ImageView::getVertexSize() { return (vertexSize); }

int ImageView::getVertexType() { return (vertexType); }

int ImageView::getEdgeType() { return (edgeType); }

void ImageView::setVertexType(int type) { vertexType = type; }

void ImageView::setEdgeType(int type) { edgeType = type; }

void ImageView::cleanVertexArray() {
  delete[] vertexArray;
  vertexArray = nullptr;
}
