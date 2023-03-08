#include "../include/mainwindow.h"
#include "QFileDialog"

void MainWindow::on_actionQuit_triggered() { close(); }

void MainWindow::on_actionEnglish_triggered() { setLanguage(ENGLISH); }

void MainWindow::on_actionRussian_triggered() { setLanguage(RUSSIAN); }

void MainWindow::on_radioButtonCentralProj_released() {
  ui->widget->setProjection(FRUSTUM);
}

void MainWindow::on_radioButtonParallelProj_released() {
  ui->widget->setProjection(ORTHO);
}

void MainWindow::on_buttonScale_released() {
  if (viewer.info.index_array) {
    ui->widget->setScale(ui->lineEditScale->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_buttonMoveX_released() {
  if (viewer.info.index_array) {
    ui->widget->setMovingX(ui->lineEditMoveX->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_buttonMoveY_released() {
  if (viewer.info.index_array) {
    ui->widget->setMovingY(ui->lineEditMoveY->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_buttonMoveZ_released() {
  if (viewer.info.index_array) {
    ui->widget->setMovingZ(ui->lineEditMoveZ->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_buttonMoveAll_released() {
  if (viewer.info.index_array) {
    ui->widget->setMovingX(ui->lineEditMoveX->text().toDouble());
    ui->widget->setMovingY(ui->lineEditMoveY->text().toDouble());
    ui->widget->setMovingZ(ui->lineEditMoveZ->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_buttonRotateX_released() {
  if (viewer.info.index_array) {
    ui->widget->setRotationX(ui->lineEditRotateX->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_buttonRotateY_released() {
  if (viewer.info.index_array) {
    ui->widget->setRotationY(ui->lineEditRotateY->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_buttonRotateZ_released() {
  if (viewer.info.index_array) {
    ui->widget->setRotationZ(ui->lineEditRotateZ->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_buttonRotateAll_released() {
  if (viewer.info.index_array) {
    ui->widget->setRotationX(ui->lineEditRotateX->text().toDouble());
    ui->widget->setRotationY(ui->lineEditRotateY->text().toDouble());
    ui->widget->setRotationZ(ui->lineEditRotateZ->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_buttonResize_released() {
  int width;
  int height;

  width = ui->lineEditResizeX->text().toInt();
  height = ui->lineEditResizeY->text().toInt();
  if (width <= 50)
    width = 50;
  else if (width >= 1920)
    width = 1920;
  if (height <= 50)
    height = 50;
  else if (height >= 1080)
    height = 1080;
  ui->widget->setFixedSize(width, height);
  centralWidget()->adjustSize();
  adjustSize();
  setTextImage();
}

void MainWindow::on_actionJpeg_triggered() { saveImage(JPEG); }

void MainWindow::on_actionBmp_triggered() { saveImage(BMP); }

void MainWindow::on_actionGif_triggered() { saveImage(GIF); }

void MainWindow::on_actionOBJ_triggered() { openFileOBJ(); }

void MainWindow::on_actionGIF_triggered() { openFileGIF(); }

void MainWindow::on_buttonBkgColor_clicked() {
  backgroundColor = QColorDialog::getColor(*ui->widget->getBckgColor(), this,
                                           "Choose background color");
  if (backgroundColor.isValid()) {
    ui->widget->setBckgColor(backgroundColor);
    ui->buttonBkgColor->setStyleSheet("background-color: " +
                                      ui->widget->getBckgColor()->name());
    ui->widget->update();
  }
}

void MainWindow::on_buttonEdgeColor_clicked() {
  edgeColor = QColorDialog::getColor(*ui->widget->getEdgeColor(), this,
                                     "Choose edge color");
  if (edgeColor.isValid()) {
    ui->widget->setEdgeColor(edgeColor);
    ui->buttonEdgeColor->setStyleSheet("background-color:" +
                                       ui->widget->getEdgeColor()->name());
    ui->widget->update();
  }
}

void MainWindow::on_buttonVertexColor_clicked() {
  vertexColor = QColorDialog::getColor(*ui->widget->getVertexColor(), this,
                                       "Choose vertex color");
  if (vertexColor.isValid()) {
    ui->widget->setVertexColor(vertexColor);
    ui->buttonVertexColor->setStyleSheet("background-color: " +
                                         ui->widget->getVertexColor()->name());
    ui->widget->update();
  }
}

void MainWindow::on_sliderVertexSize_sliderMoved(int position) {
  ui->widget->setVertexSize(position);
  ui->widget->update();
}

void MainWindow::on_sliderEdgeThickness_sliderMoved(int position) {
  ui->widget->setEdgeThickness(position);
  ui->widget->update();
}

void MainWindow::on_radioButtonVertexNone_clicked() {
  ui->widget->setVertexType(VERTEX_TYPE_NONE);
  ui->widget->update();
}

void MainWindow::on_radioButtonVertexCircle_clicked() {
  ui->widget->setVertexType(VERTEX_TYPE_CIRCLE);
  ui->widget->update();
}

void MainWindow::on_radioButtonVertexSquare_clicked() {
  ui->widget->setVertexType(VERTEX_TYPE_SQUARE);
  ui->widget->update();
}

void MainWindow::on_radioButtonEdgeSolid_clicked() {
  ui->widget->setEdgeType(EDGE_TYPE_SOLID);
  ui->widget->update();
}

void MainWindow::on_radioButtonEdgeDashed_clicked() {
  ui->widget->setEdgeType(EDGE_TYPE_DASHED);
  ui->widget->update();
}

void MainWindow::on_actionCentral_triggered() {
  if (ui->widget->getProjection() != FRUSTUM) {
    ui->widget->setProjection(FRUSTUM);
    ui->radioButtonCentralProj->toggle();
    ui->widget->update();
  }
}

void MainWindow::on_actionParallel_triggered() {
  if (ui->widget->getProjection() != ORTHO) {
    ui->widget->setProjection(ORTHO);
    ui->radioButtonParallelProj->toggle();
    ui->widget->update();
  }
}

void MainWindow::on_actionNone_triggered() {
  ui->widget->setVertexType(VERTEX_TYPE_NONE);
  ui->radioButtonVertexNone->toggle();
  ui->widget->update();
}

void MainWindow::on_actionCircle_triggered() {
  ui->widget->setVertexType(VERTEX_TYPE_CIRCLE);
  ui->radioButtonVertexCircle->toggle();
  ui->widget->update();
}

void MainWindow::on_actionSquare_triggered() {
  ui->widget->setVertexType(VERTEX_TYPE_SQUARE);
  ui->radioButtonVertexSquare->toggle();
  ui->widget->update();
}

void MainWindow::on_actionSolid_triggered() {
  ui->widget->setEdgeType(EDGE_TYPE_SOLID);
  ui->radioButtonEdgeSolid->toggle();
  ui->widget->update();
}

void MainWindow::on_actionDashed_triggered() {
  ui->widget->setEdgeType(EDGE_TYPE_DASHED);
  ui->radioButtonEdgeDashed->toggle();
  ui->widget->update();
}