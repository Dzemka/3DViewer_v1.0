#include "mainwindow.h"

void MainWindow::setLanguage(int language) {
  if (ui->widget->getLanguage() != language) {
    if (language == RUSSIAN)
      if (!translator.load(":/i18n/3DViewer_ru_RU"))
        return;
      else
        qApp->installTranslator(&translator);
    else
      qApp->removeTranslator(&translator);
    ui->retranslateUi(this);
    ui->widget->setLanguage(language);
    setTextImage();
  }
}
