#include "../include/mainwindow.h"

#include <QColor>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  initializeData();
  loadSettings();
  setElementsInterface();
  addValidators();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::closeEvent(QCloseEvent *event) {
  QMessageBox::StandardButton resBtn = QMessageBox::question(
      this, tr("3DViewer"), tr("Are you sure?\n"),
      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
      QMessageBox::Yes);
  if (resBtn != QMessageBox::Yes) {
    event->ignore();
  } else {
    uploadSettings();
    clean_data_object(&viewer);
    ui->widget->cleanVertexArray();
    event->accept();
  }
}

void MainWindow::setTextImage() {
  QString string((openFileName + ", %1x%2")
                     .arg(ui->widget->width())
                     .arg(ui->widget->height()));
  unsigned long pointCount;
  size_t facesCount;

  pointCount = ui->widget->getPointCount();
  facesCount = ui->widget->getIndexSize() / 2;
  if (openFileName != tr("Image")) {
    string.append(
        QString(", %1 vertexes, %2 edge").arg(pointCount).arg(facesCount));
  }
  ui->labelImage->setText(string);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);
  ui->widget->update();
  setTextImage();
}
