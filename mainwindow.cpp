#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(&this->DirWind,SIGNAL(dialog_choosed(QString,QString,QColor)),this,SLOT(load_files(QString,QString,QColor)));
    connect(&this->DirWind,SIGNAL(dialog_closed()),this,SLOT(dir_signal_close()));
    ui->setupUi(this);
    this->pix = new QPixmap(ui->Canvas->width(),ui->Canvas->height());
    pix->fill();
    ui->Canvas->setPixmap(*pix);
    this->Mgr = new Manager(this,new file_loader,new Graphical_sys,new painter(this->pix),new tesselator);
    this->Mgr->add_camera();
//    this->Mgr->load_model("C:/KG_Kurs/Models/tor_low.obj","C:/KG_Kurs/Models/tor_high.obj",Qt::blue);
//    this->Mgr->scale_model(1,0.0125);
//    this->Mgr->rotate_model(1,60,1,1,1);
//    this->Mgr->move_model(1,-250);
    this->Mgr->cam_inc_range(0,1000);
    this->Mgr->draw_scene(0,0);
    ui->Canvas->setPixmap(*this->pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_files(QString low, QString high,QColor clr)
{
    this->Mgr->load_model(low,high,clr);
    this->Mgr->scale_model(1,0.125);
    this->Mgr->draw_scene(0,1);
    ui->Canvas->setPixmap(*this->pix);
    this->setEnabled(true);
}

void MainWindow::dir_signal_close()
{
    this->setEnabled(true);
}

void MainWindow::on_action_triggered()
{
    this->setEnabled(false);
    this->DirWind.show();
}


void MainWindow::on_btn_scale_plus_clicked()
{

    this->Mgr->cam_dec_range(0,500);
    this->Mgr->draw_scene(0,1);

    ui->Canvas->setPixmap(*this->pix);
}

void MainWindow::on_btn_scale_minus_clicked()
{
    this->Mgr->cam_inc_range(0,500);
    this->Mgr->draw_scene(0,1);

    ui->Canvas->setPixmap(*this->pix);
}

void MainWindow::on_btn_pitch_plus_clicked()
{
    this->Mgr->cam_pitch(0,15);
    this->Mgr->draw_scene(0,1);
    ui->Canvas->setPixmap(*this->pix);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->Mgr->cam_pitch(0,-15);
    this->Mgr->draw_scene(0,1);
    ui->Canvas->setPixmap(*this->pix);
}
