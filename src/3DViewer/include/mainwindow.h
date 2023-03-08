#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <math.h>

#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QMovie>
#include <QRegularExpressionValidator>
#include <QTranslator>

#include "../ui_mainwindow.h"
#include "gif.h"
#include "viewer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void setTextImage();
  void saveImage(int format);
  void saveGif(QString fileName);

 protected:
  void resizeEvent(QResizeEvent *event) override;
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void setElementsInterface();
  void on_actionEnglish_triggered();
  void on_actionRussian_triggered();
  void on_radioButtonCentralProj_released();
  void on_radioButtonParallelProj_released();
  void on_buttonScale_released();
  void on_buttonMoveX_released();
  void on_buttonMoveY_released();
  void on_buttonMoveZ_released();
  void on_buttonMoveAll_released();
  void on_buttonRotateX_released();
  void on_buttonRotateY_released();
  void on_buttonRotateZ_released();
  void on_buttonRotateAll_released();
  void on_buttonResize_released();
  void on_actionJpeg_triggered();
  void on_actionBmp_triggered();
  void on_actionCentral_triggered();
  void on_actionParallel_triggered();
  void on_actionGif_triggered();
  void on_actionOBJ_triggered();
  void on_actionGIF_triggered();
  void on_buttonBkgColor_clicked();
  void on_radioButtonEdgeSolid_clicked();
  void on_radioButtonEdgeDashed_clicked();
  void on_radioButtonVertexNone_clicked();
  void on_radioButtonVertexCircle_clicked();
  void on_radioButtonVertexSquare_clicked();
  void on_buttonVertexColor_clicked();
  void on_buttonEdgeColor_clicked();
  void on_sliderEdgeThickness_sliderMoved(int position);
  void on_sliderVertexSize_sliderMoved(int position);
  void on_actionSolid_triggered();
  void on_actionDashed_triggered();
  void on_actionNone_triggered();
  void on_actionCircle_triggered();
  void on_actionSquare_triggered();
  void on_actionQuit_triggered();

 private:
  QMovie mo;
  Ui::MainWindow *ui;
  QString openFileName;
  QTranslator translator;
  t_viewer viewer;
  QRegularExpressionValidator doubleValidator;
  QRegularExpressionValidator intValidator;
  QRegularExpressionValidator fileValidator;
  QColor backgroundColor;
  QColor edgeColor;
  QColor vertexColor;
  QPoint mousePosition;
  void initializeData();
  void loadSettings();
  void uploadSettings();
  void addValidators();
  void keyPressEvent(QKeyEvent *key) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void openFileOBJ();
  void openFileGIF();
  void setLanguage(int language);
};
#endif  // MAINWINDOW_H
