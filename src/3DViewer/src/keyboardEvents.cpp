#include "mainwindow.h"

void MainWindow::keyPressEvent(QKeyEvent *key) {
  int k = key->key();
  if (k == Qt::Key_R)
    ui->widget->updateVertexArray(viewer.info.vertexes3d);
  else if (k == Qt::Key_Escape)
    close();
  else if (k == Qt::Key_F5)
    ui->widget->updateVertexArray(viewer.info.vertexes3d);
  ui->widget->update();
}
