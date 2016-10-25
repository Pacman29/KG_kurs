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
    model md, h_md;
    fl.Load(md,"C:/KG_Kurs/Models/low_cube.txt",Qt::green);
    fl.Load(h_md,"C:/KG_Kurs/Models/high_cube.txt",Qt::green);
    md.set_high_model(h_md);
    cobj.add(&md);
    camera cam;
            //need model with highmodel and nowmodel
    this->pntr = new painter(&pix);
    gr.set_scene(*this->pntr);
    gr.Draw_scene(this->cobj,cam);
    ui->label->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

