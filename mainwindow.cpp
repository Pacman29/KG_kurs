#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(ui->label->height(),ui->label->width());
    pix.fill();
    ui->label->setPixmap(pix);
    base_model model;
    fl.Load(model,)
    cobj.add()
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*14****
