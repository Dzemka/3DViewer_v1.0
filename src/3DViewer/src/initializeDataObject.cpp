#include "../include/mainwindow.h"

void MainWindow::initializeData() {
  openFileName = tr("Image");
  viewer.info.count_v = 0;
  viewer.filename = NULL;
  viewer.vertex_list = NULL;
  viewer.tmp = NULL;
  viewer.tmp2 = NULL;
  viewer.faces = NULL;
  viewer.info.index_array = NULL;
  viewer.info.count_indexes = 0;
  viewer.info.vertexes3d = NULL;
  viewer.info.width = ui->widget->width();
  viewer.info.height = ui->widget->height();
}
