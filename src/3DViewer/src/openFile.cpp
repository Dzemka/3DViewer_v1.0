#include <QFileDialog>

#include "mainwindow.h"

void MainWindow::openFileOBJ() {
  hide();
  QString tempFileName;
  tempFileName =
      QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("*.obj"));
  if (!tempFileName.isNull()) {
    mo.stop();
    ui->labelMovie->hide();
    ui->widget->show();
    clean_data_object(&viewer);
    ui->widget->cleanVertexArray();
    ui->widget->initializeTransformation();
    int status = parser(tempFileName.toStdString().c_str(), &viewer);
    openFileName.clear();
    if (!status) {
      openFileName = viewer.filename;
      set_values(&viewer);
      ui->widget->setPointCount(viewer.info.count_v);
      ui->widget->setVertexArray(viewer.info.vertexes3d,
                                 viewer.info.count_v * 3);
      ui->widget->setIndexList(viewer.info.index_array);

      ui->widget->setIndexSize(viewer.info.count_indexes * 2);
      if (viewer.dimensions.z_max >= viewer.dimensions.x_max &&
          viewer.dimensions.z_max >= viewer.dimensions.y_max)
        ui->widget->setDistanceZ(viewer.dimensions.z_max);
      else if (viewer.dimensions.y_max >= viewer.dimensions.x_max &&
               viewer.dimensions.y_max >= viewer.dimensions.z_max)
        ui->widget->setDistanceZ(viewer.dimensions.y_max);
      else
        ui->widget->setDistanceZ(viewer.dimensions.x_max);
      ui->widget->update();
    } else {
      openFileName = tr("Image");
      ui->statusbar->showMessage(viewer.filename);
      ui->widget->update();
    }
  }
  clean_data_parse(&viewer);
  setTextImage();
  show();
}

void MainWindow::openFileGIF() {
  hide();
  QString openGif =
      QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("*.gif"));
  if (!openGif.isNull()) {
    mo.stop();
    ui->widget->hide();
    ui->labelMovie->show();
    mo.setFileName(openGif);
    mo.setScaledSize(QSize(640, 480));
    ui->labelMovie->setMovie(&mo);
    mo.start();
  }
  show();
}
