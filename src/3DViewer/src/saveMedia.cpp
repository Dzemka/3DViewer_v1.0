#include <QFileDialog>

#include "../include/mainwindow.h"
void MainWindow::saveImage(int format) {
  hide();
  QFileDialog fileDialog(this);
  fileDialog.setOption(QFileDialog::DontUseNativeDialog, true);
  auto children = fileDialog.findChildren<QLineEdit *>();
  if (children.size() == 1) {
    children.front()->setValidator(&fileValidator);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (format == JPEG) {
      fileDialog.setDefaultSuffix("jpeg");
      fileDialog.setNameFilter("*.jpg *.jpeg");
    } else if (format == BMP) {
      fileDialog.setDefaultSuffix("bmp");
      fileDialog.setNameFilter("*.bmp");
    } else if (format == GIF) {
      fileDialog.setDefaultSuffix("gif");
      fileDialog.setNameFilter("*.gif");
    }
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setViewMode(QFileDialog::List);
  }
  fileDialog.setWindowTitle(tr("Save As"));
  fileDialog.setLabelText(fileDialog.LookIn, tr("Look In"));
  fileDialog.setLabelText(fileDialog.FileName, tr("File &name:"));
  fileDialog.setLabelText(fileDialog.FileType, tr("Files of type:"));
  fileDialog.setLabelText(fileDialog.Accept, tr("Save"));
  fileDialog.setLabelText(fileDialog.Reject, tr("Cancel"));
  QStringList saveFileName;
  if (fileDialog.exec()) saveFileName = fileDialog.selectedFiles();
  if (!saveFileName.isEmpty()) {
    if (format == BMP || format == JPEG) {
      QPixmap pixmap(ui->widget->size());
      ui->widget->render(&pixmap, QPoint(), QRegion(ui->widget->rect()));
      pixmap.save(saveFileName[0]);
    } else if (format == GIF)
      saveGif(saveFileName[0]);
  }
  show();
}

void MainWindow::saveGif(QString fileName) {
  int count = 0;
  double moveX = ui->lineEditMoveX->text().toDouble() / (FRAMES - 1);
  double moveY = ui->lineEditMoveY->text().toDouble() / (FRAMES - 1);
  double moveZ = ui->lineEditMoveZ->text().toDouble() / (FRAMES - 1);
  double rotX = ui->lineEditRotateX->text().toDouble() / (FRAMES - 1);
  double rotY = ui->lineEditRotateY->text().toDouble() / (FRAMES - 1);
  double rotZ = ui->lineEditRotateZ->text().toDouble() / (FRAMES - 1);
  double scale =
      pow(10, log10(ui->lineEditScale->text().toDouble()) / (FRAMES - 1));
  if (moveX || moveY || moveZ || rotX || rotY || rotZ || scale) {
    Gif gif;
    Gif::GifWriter gifWriter = {};

    ui->widget->setFixedSize(GIF_WIDTH, GIF_HEIGHT);
    gif.GifBegin(&gifWriter, fileName.toStdString().c_str(), GIF_WIDTH,
                 GIF_HEIGHT, 10, 8, true);
    while (count < FRAMES) {
      if (count) {
        ui->widget->setMovingX(moveX);
        ui->widget->setMovingY(moveY);
        ui->widget->setMovingZ(moveZ);
        ui->widget->setRotationX(rotX);
        ui->widget->setRotationY(rotY);
        ui->widget->setRotationZ(rotZ);
        ui->widget->setScale(scale);
        ui->widget->update();
      }
      QPixmap pixmap(ui->widget->size());
      ui->widget->render(&pixmap, QPoint(), QRegion(ui->widget->rect()));
      QImage image = pixmap.toImage().convertToFormat(QImage::Format_RGBA8888);
      gif.GifWriteFrame(&gifWriter, image.bits(), GIF_WIDTH, GIF_HEIGHT, 10, 8,
                        true);
      count++;
    }
    gif.GifEnd(&gifWriter);
    ui->statusbar->showMessage("Gif done");
  } else
    ui->statusbar->showMessage("No transformations set");
}
