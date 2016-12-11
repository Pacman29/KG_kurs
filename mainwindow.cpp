#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

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
//    this->Mgr->draw_scene(0,0);
    ui->Canvas->setPixmap(*this->pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_choose_obj()
{
    if(!ui->box_current_model->count())
        pix->fill();
    else
    {
        int i = ui->box_current_model->currentIndex()+1;
        QTime tm;
        tm.start();
        this->Mgr->draw_scene(0,i);
        ui->fps_lbl->setText("FPS: "+QString::number((double)1000/tm.elapsed()));
    }
    ui->Canvas->setPixmap(*this->pix);
}

void MainWindow::load_files(QString low, QString high,QColor clr)
{

    this->Mgr->load_model(low,high,clr);
    QRegExp r1("\\\\|\\\/");
    QString str1 = ".."+low.mid(low.lastIndexOf(r1));
    QString str2 = ".."+high.mid(high.lastIndexOf(r1));
    ui->box_current_model->addItem(str1+" \\ "+str2);
    ui->box_current_model->setCurrentIndex(ui->box_current_model->count()-1);
    draw_choose_obj();
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
    draw_choose_obj();
}

void MainWindow::on_btn_scale_minus_clicked()
{
    this->Mgr->cam_inc_range(0,500);
    draw_choose_obj();
}

void MainWindow::on_btn_pitch_plus_clicked()
{
    this->Mgr->cam_pitch(0,15);
    draw_choose_obj();
}

void MainWindow::on_btn_pitch_minus_clicked()
{
    this->Mgr->cam_pitch(0,-15);
    draw_choose_obj();
}

void MainWindow::on_btn_yaw_plus_clicked()
{
    this->Mgr->cam_yaw(0,15);
    draw_choose_obj();
}

void MainWindow::on_btn_yaw_minus_clicked()
{
    this->Mgr->cam_yaw(0,-15);
    draw_choose_obj();
}

void MainWindow::on_btn_roll_plus_clicked()
{
    this->Mgr->cam_roll(0,15);
    draw_choose_obj();
}

void MainWindow::on_btn_roll_minus_clicked()
{
    this->Mgr->cam_roll(0,-15);
    draw_choose_obj();
}

void MainWindow::on_box_current_model_currentIndexChanged(int index)
{
    draw_choose_obj();
}
