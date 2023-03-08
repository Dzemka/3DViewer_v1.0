#include "../include/imageview.h"

void ImageView::settingBackground() {
  glClearColor(backgroundColor.red() / 255.0, backgroundColor.green() / 255.0,
               backgroundColor.blue() / 255.0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ImageView::drawVertex() {
  if (vertexType) {
    if (vertexType == VERTEX_TYPE_CIRCLE)
      glEnable(GL_POINT_SMOOTH);
    else
      glDisable(GL_POINT_SMOOTH);
    glPointSize(vertexSize);
    glColor4d(vertexColor.red() / 255.0, vertexColor.green() / 255.0,
              vertexColor.blue() / 255.0, 1);
    glDrawArrays(GL_POINTS, 0, (int)pointCount);
  }
}

void ImageView::settingEdge() {
  glColor4d(edgeColor.red() / 255.0, edgeColor.green() / 255.0,
            edgeColor.blue() / 255.0, 1);
  glLineWidth(edgeThickness);
  if (edgeType == EDGE_TYPE_DASHED) {
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  } else
    glDisable(GL_LINE_STIPPLE);
}

void ImageView::settingProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection == FRUSTUM) {
    glFrustum(-width() / 2, width() / 2, -height() / 2, height() / 2,
              distanceZ * transform.rSca * 2,
              distanceZ * transform.rSca * 1000);
    glTranslatef(0, 0, -distanceZ * transform.rSca * 4);
  } else
    glOrtho(-width() / 2 - 150, width() / 2 + 150, -height() / 2 - 150,
            height() / 2 + 150, -distanceZ * transform.rSca * 1000,
            distanceZ * transform.rSca * 1000);
}

void ImageView::paintGL() {
  settingBackground();
  settingEdge();
  settingProjection();
  glMatrixMode(GL_MODELVIEW);
  if (!indexList) return;
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, vertexArray);
  glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, indexList);
  drawVertex();
  glDisableClientState(GL_VERTEX_ARRAY);
}
