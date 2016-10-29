#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->pix = new QPixmap(ui->label->height(),ui->label->width());
    pix->fill();
    ui->label->setPixmap(*pix);
    model* md = new model;
    model* h_md = new model;
    //fl.Load(*md,"C:/KG_Kurs/Models/low_cube.txt",Qt::green);
    //fl.Load(*h_md,"C:/KG_Kurs/Models/high_cube.txt",Qt::green);

    fl.Load(*md,"/home/pacman29/Qt_proj/KG_kurs/KG_kurs/Models/low_cube.txt",Qt::green);
    fl.Load(*h_md,"/home/pacman29/Qt_proj/KG_kurs/KG_kurs/Models/high_cube.txt",Qt::green);
    qDebug() << h_md->get_size();
    md->set_high_model(*h_md);
    cobj.add(md);
            //need model with highmodel and nowmodel
}

void MainWindow::_show()
{
    this->show();

    this->pntr = new painter(pix);
    gr.set_scene(*this->pntr);
    model* tmp_model =( model*)cobj[0];
    ts.tesselate(tesselator::UP,tmp_model);
    ts.tesselate(tesselator::UP,tmp_model);
    ts.tesselate(tesselator::DOWN,tmp_model);
//    ts.tesselate(tesselator::UP,tmp_model);
//    ts.tesselate(tesselator::UP,tmp_model);
//    ts.tesselate(tesselator::UP,tmp_model,tmp_model->get_high_model());
    tmp_model->scale(16);
    QTimer::singleShot(1,this,SLOT(anim()));
}

MainWindow::~MainWindow()
{
    delete this->pntr;
    delete this->pix;
    delete ui;
}

void MainWindow::anim()
{
    model* tmp_model =( model*)cobj[0];
    tmp_model->rotate(1,1,1,1);
    gr.Draw_scene(this->cobj,cam);
    ui->label->setPixmap(*pix);
    this->pix->fill();
    QTimer::singleShot(1,this,SLOT(anim()));
}




