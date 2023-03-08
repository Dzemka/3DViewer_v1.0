#include "mainwindow.h"

void MainWindow::mousePressEvent(QMouseEvent *event) {
  mousePosition = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  double rotationX;
  double rotationZ;
  double differenceX;
  double differenceY;

  differenceX = event->pos().y() - mousePosition.y();
  differenceY = event->pos().x() - mousePosition.x();
  rotationX = 0;
  rotationZ = 0;
  if (differenceX)
    rotationX = 360.0 / ui->widget->getSca() * differenceX /
                (double)ui->widget->height();
  if (differenceY)
    rotationZ = 360.0 / ui->widget->getSca() * differenceY /
                (double)ui->widget->width();
  if (rotationX) ui->widget->setRotationX(rotationX);
  if (rotationZ) ui->widget->setRotationY(rotationZ);
  mousePosition = event->pos();
  ui->widget->update();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0)
    ui->widget->setScale(1.1);
  else
    ui->widget->setScale(0.9);
  ui->widget->update();
}
