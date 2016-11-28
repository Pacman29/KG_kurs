#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->pix = new QPixmap(ui->label->width(),ui->label->height());
    pix->fill();
    ui->label->setPixmap(*pix);
    model* md = new model;
    model* h_md = new model;
    //fl.Load(*md,"C:/KG_Kurs/Models/low_sphere.txt",Qt::green);
    //fl.Load(*h_md,"C:/KG_Kurs/Models/high_sphere.txt",Qt::green);
    fl.Load(*md,"C:/KG_Kurs/Models/tor_low.obj",Qt::green);
    fl.Load(*h_md,"C:/KG_Kurs/Models/tor_high.obj",Qt::green);
    //fl.Load(*md,"/home/pacman29/Qt_proj/KG_kurs/KG_kurs/Models/low_cube.txt",Qt::green);
    //fl.Load(*h_md,"/home/pacman29/Qt_proj/KG_kurs/KG_kurs/Models/high_cube.txt",Qt::green);

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
    //tmp_model->scale(0.5);
    ts.tesselate(tesselator::UP,tmp_model);
//    ts.tesselate(tesselator::UP,tmp_model);
//    ts.tesselate(tesselator::DOWN,tmp_model);
//    ts.tesselate(tesselator::DOWN,tmp_model);
//    ts.tesselate(tesselator::DOWN,tmp_model);
//    ts.tesselate(tesselator::UP,tmp_model);
//    ts.tesselate(tesselator::UP,tmp_model);
//    ts.tesselate(tesselator::UP,tmp_model,tmp_model->get_high_model());
   tmp_model->scale(0.05);
   tmp_model->move(-400,0);
//    tmp_model->rotate(180,0,0,1);
   anim();
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
    tmp_model->rotate(0.3,1,1,1);
    gr.Draw_scene(this->cobj,cam);
    ui->label->setPixmap(*pix);
    this->pix->fill();
    QTimer::singleShot(10,this,SLOT(anim()));
}





void MainWindow::on_btn_up_clicked()
{
    model* tmp_model =( model*)cobj[0];
    //tmp_model->scale(0.5);
    ts.tesselate(tesselator::UP,tmp_model);
    anim();
}

void MainWindow::on_btn_down_clicked()
{
    model* tmp_model =( model*)cobj[0];
    //tmp_model->scale(0.5);
    ts.tesselate(tesselator::DOWN,tmp_model);
    anim();
}
