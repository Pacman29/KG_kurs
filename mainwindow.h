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
#include "Tesselator/tesselator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void _show();
    ~MainWindow();
private slots:
    void anim();

    void on_btn_up_clicked();

    void on_btn_down_clicked();

private:
    camera cam;
    size_t i;
    QPixmap* pix;
    tesselator ts;
    painter* pntr;
    file_loader fl;
    composit_object cobj;
    Graphical_sys gr;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
