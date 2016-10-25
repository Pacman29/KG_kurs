#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

#include "Composit_obj/composit_object.h"
#include "loader/loader.h"

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
    file_loader fl;
    composit_object cobj;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
