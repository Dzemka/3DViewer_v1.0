#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H
#define GL_SILENCE_DEPRECATION
#include <QOpenGLWidget>
#include <QWidget>

#include "viewer.h"

class ImageView : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit ImageView(QWidget *parent = nullptr);
  ~ImageView();
  void initializeData();
  void setLanguage(int language);
  int getLanguage();
  void setPointCount(unsigned long count);
  unsigned long getPointCount();
  void setVertexArray(double *array, size_t size);
  void setIndexList(unsigned int *indexList);
  void setIndexSize(size_t indexSize);
  size_t getIndexSize();
  void setDistanceZ(double distance);
  void setProjection(int projection);
  int getProjection();
  void setScale(double scale);
  void setMovingX(double traX);
  void setMovingY(double traY);
  void setMovingZ(double traZ);
  void setRotationX(double rotX);
  void setRotationY(double rotY);
  void setRotationZ(double rotZ);
  void setBckgColor(QColor color);
  QColor *getBckgColor();
  void setEdgeColor(QColor color);
  QColor *getEdgeColor();
  void setVertexColor(QColor color);
  QColor *getVertexColor();
  void setVertexSize(int size);
  void setVertexTypeNone();
  void setVertexTypeCircle();
  void setVertexTypeSquare();
  void setEdgeTypeSolid();
  void setEdgeTypeDashed();
  double getSca();
  int getEdgeThickness();
  void setEdgeThickness(int thickness);
  int getVertexSize();
  void setVertexType(int type);
  int getVertexType();
  int getEdgeType();
  void setEdgeType(int type);
  void cleanVertexArray();
  void updateVertexArray(double *array);
  void addTraX(double value);
  void addTraY(double value);
  void addTraZ(double value);
  double getTraX();
  double getTraY();
  double getTraZ();
  void initializeTransformation();

 signals:

 protected:
  void initializeGL() override;
  void resizeGL(int nWidth, int nHeight) override;
  void paintGL() override;

 private:
  unsigned long pointCount;
  double *vertexArray;
  unsigned int *indexList;
  size_t indexSize;
  double distanceZ;
  t_transform transform;
  int projection;
  int language;
  QColor backgroundColor;
  QColor edgeColor;
  QColor vertexColor;
  int edgeThickness;
  int vertexSize;
  int vertexType;
  int edgeType;
  void drawVertex();
  void settingBackground();
  void settingEdge();
  void settingProjection();
};

#endif  // IMAGEVIEW_H
