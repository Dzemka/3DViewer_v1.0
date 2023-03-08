#include "../include/imageview.h"

ImageView::ImageView(QWidget *parent) : QOpenGLWidget{parent} {
  initializeTransformation();
  language = RUSSIAN;
}

ImageView::~ImageView() {}

void ImageView::setPointCount(unsigned long count) { pointCount = count; }

unsigned long ImageView::getPointCount() { return (pointCount); }

void ImageView::setVertexArray(double *array, size_t size) {
  vertexArray = new double[size];
  memcpy(vertexArray, array, sizeof(double) * size);
}

void ImageView::setIndexList(unsigned int *indexList) {
  this->indexList = indexList;
}

void ImageView::setIndexSize(size_t indexSize) { this->indexSize = indexSize; }

size_t ImageView::getIndexSize() { return (indexSize); }

void ImageView::setDistanceZ(double distance) { distanceZ = distance; }

void ImageView::updateVertexArray(double *array) {
  memcpy(vertexArray, array, sizeof(double) * pointCount * 3);
}

void ImageView::initializeGL() {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void ImageView::resizeGL(int nWidth, int nHeight) {
  Q_UNUSED(nWidth);
  Q_UNUSED(nHeight);
  if (640.0 / 480.0 > (double)width() / height())
    transform.rSca = width() / 640.0;
  else
    transform.rSca = height() / 480.0;
}
