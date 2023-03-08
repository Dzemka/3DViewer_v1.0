#include "mainwindow.h"

void MainWindow::setElementsInterface() {
  ui->sliderEdgeThickness->setRange(MIN_EDGE_THICKNESS, MAX_EDGE_THICKNESS);
  ui->sliderVertexSize->setRange(MIN_VERTEX_SIZE, MAX_VERTEX_SIZE);
  ui->sliderEdgeThickness->setValue(ui->widget->getEdgeThickness());
  ui->sliderVertexSize->setValue(ui->widget->getVertexSize());
  if (ui->widget->getProjection() == FRUSTUM)
    ui->radioButtonCentralProj->toggle();
  else
    ui->radioButtonParallelProj->toggle();
  if (ui->widget->getEdgeType() == EDGE_TYPE_DASHED)
    ui->radioButtonEdgeDashed->toggle();
  else
    ui->radioButtonEdgeSolid->toggle();
  if (ui->widget->getVertexType() == VERTEX_TYPE_NONE)
    ui->radioButtonVertexNone->toggle();
  else if (ui->widget->getVertexType() == VERTEX_TYPE_CIRCLE)
    ui->radioButtonVertexCircle->toggle();
  else
    ui->radioButtonVertexSquare->toggle();
  ui->buttonBkgColor->setStyleSheet("background-color: " +
                                    ui->widget->getBckgColor()->name());
  ui->buttonEdgeColor->setStyleSheet("background-color: " +
                                     ui->widget->getEdgeColor()->name());
  ui->buttonVertexColor->setStyleSheet("background-color: " +
                                       ui->widget->getVertexColor()->name());
}
