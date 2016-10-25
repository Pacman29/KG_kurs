#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

#include "Composit_obj/composit_object.h"
#include "loader/loader.h"
#include "Model/model.h"
#include "canvas/graphical_sys.h"
#include "Camera/camera.h"
#include "canvas/painter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    painter* pntr;
    file_loader fl;
    composit_object cobj;
    Graphical_sys gr;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
