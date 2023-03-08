#include "../include/mainwindow.h"

void MainWindow::addValidators() {
  doubleValidator.setRegularExpression(
      QRegularExpression("^[-+]?\\d{0,5}(\\.\\d{0,3})?$"));
  intValidator.setRegularExpression(QRegularExpression("^[+]?\\d{0,4}$"));
  fileValidator.setRegularExpression(QRegularExpression("[^/|. ,:?*<>\\\\]+"));
  ui->lineEditMoveX->setValidator(&doubleValidator);
  ui->lineEditMoveY->setValidator(&doubleValidator);
  ui->lineEditMoveZ->setValidator(&doubleValidator);
  ui->lineEditRotateX->setValidator(&doubleValidator);
  ui->lineEditRotateY->setValidator(&doubleValidator);
  ui->lineEditRotateZ->setValidator(&doubleValidator);
  ui->lineEditScale->setValidator(&doubleValidator);
  ui->lineEditResizeX->setValidator(&intValidator);
  ui->lineEditResizeY->setValidator(&intValidator);
}
