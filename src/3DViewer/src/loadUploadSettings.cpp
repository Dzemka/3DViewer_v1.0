#include <QSettings>

#include "../include/mainwindow.h"

void MainWindow::loadSettings() {
  QSettings setting("settings_3DViewer.ini", QSettings::IniFormat);

  setting.beginGroup("Settings");
  ui->widget->setProjection(setting.value("Projection", FRUSTUM).toInt());
  ui->widget->setBckgColor(setting.value("Background color").value<QColor>());
  ui->widget->setEdgeColor(
      setting.value("Edge color", QColor(255, 0, 255)).value<QColor>());
  ui->widget->setVertexColor(
      setting.value("Vertex color", QColor(0, 255, 255)).value<QColor>());
  ui->widget->setEdgeThickness(
      (setting.value("Edge thickness", MIN_EDGE_THICKNESS)).toInt());
  ui->widget->setVertexSize(
      (setting.value("Vertex size", MIN_VERTEX_SIZE)).toInt());
  ui->widget->setVertexType(
      (setting.value("Vertex type", VERTEX_TYPE_NONE)).toInt());
  ui->widget->setEdgeType(
      (setting.value("Edge type", EDGE_TYPE_SOLID)).toInt());
  ui->widget->setLanguage(setting.value("Language", ENGLISH).toInt());
  setting.endGroup();
  if (ui->widget->getLanguage() == RUSSIAN) {
    const QString baseName = "3DViewer_ru_RU";
    if (translator.load(":/i18n/" + baseName)) {
      qApp->installTranslator(&translator);
      ui->retranslateUi(this);
      setTextImage();
    }
  }
}

void MainWindow::uploadSettings() {
  QSettings setting("settings_3DViewer.ini", QSettings::IniFormat);
  setting.beginGroup("Settings");
  setting.setValue("Projection", ui->widget->getProjection());
  setting.setValue("Background color", *ui->widget->getBckgColor());
  setting.setValue("Edge color", *ui->widget->getEdgeColor());
  setting.setValue("Vertex color", *ui->widget->getVertexColor());
  setting.setValue("Edge thickness", ui->widget->getEdgeThickness());
  setting.setValue("Vertex size", ui->widget->getVertexSize());
  setting.setValue("Vertex type", ui->widget->getVertexType());
  setting.setValue("Edge type", ui->widget->getEdgeType());
  setting.setValue("Language", ui->widget->getLanguage());
  setting.endGroup();
}
