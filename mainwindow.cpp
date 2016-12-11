#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QResizeEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(&this->DirWind,SIGNAL(dialog_choosed(QString,QString,QColor)),this,SLOT(load_files(QString,QString,QColor)));
    connect(&this->DirWind,SIGNAL(dialog_closed()),this,SLOT(dir_signal_close()));
    ui->setupUi(this);
    this->pix = new QPixmap(ui->Canvas->maximumSize());
    this->Mgr = new Manager(this,new file_loader,new Graphical_sys,new painter(this->pix),new tesselator);
    this->Mgr->add_camera();;
    this->Mgr->cam_inc_range(0,1000);
    this->Mgr->draw_scene(0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_choose_obj(QTime *tm)
{
    if(!ui->box_current_model->count())
    {
        ui->Pol_count_lbl->setText("Полигоны: "+QString::number(this->Mgr->polygon_count(0)));
        if(tm == NULL)
        {
            tm = new QTime;
            tm->start();
        }
        pix->fill();
        ui->fps_lbl->setText("FPS: "+QString::number((double)1000/tm->elapsed()));
    }
    else
    {
        int i = ui->box_current_model->currentIndex()+1;
        if(tm == NULL)
        {
            tm = new QTime;
            tm->start();
        }
        this->Mgr->draw_scene(0,i);
        ui->Pol_count_lbl->setText("Полигоны: "+QString::number(this->Mgr->polygon_count(i)));
        ui->fps_lbl->setText("FPS: "+QString::number((double)1000/tm->elapsed()));
    }
    ui->Canvas->setPixmap(*this->pix);
}

void MainWindow::load_files(QString low, QString high,QColor clr)
{

    this->Mgr->load_model(low,high,clr);
    QRegExp r1("\\\\|\\\/");
    QString str1 = ".."+low.mid(low.lastIndexOf(r1));
    QString str2 = ".."+high.mid(high.lastIndexOf(r1));
    ui->box_current_model->addItem(str1+" and "+str2);
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
    this->Mgr->cam_pitch(0,30);
    draw_choose_obj();
}

void MainWindow::on_btn_pitch_minus_clicked()
{
    this->Mgr->cam_pitch(0,-30);
    draw_choose_obj();
}

void MainWindow::on_btn_yaw_plus_clicked()
{
    this->Mgr->cam_yaw(0,30);
    draw_choose_obj();
}

void MainWindow::on_btn_yaw_minus_clicked()
{
    this->Mgr->cam_yaw(0,-30);
    draw_choose_obj();
}

void MainWindow::on_btn_roll_plus_clicked()
{
    this->Mgr->cam_roll(0,30);
    draw_choose_obj();
}

void MainWindow::on_btn_roll_minus_clicked()
{
    this->Mgr->cam_roll(0,-30);
    draw_choose_obj();
}

void MainWindow::on_box_current_model_currentIndexChanged(int index)
{
    draw_choose_obj();
}

void MainWindow::on_delete_model_pushButton_clicked()
{
    int i = ui->box_current_model->currentIndex();
    this->Mgr->delete_model(i+1);
    ui->box_current_model->removeItem(i);
    ui->box_current_model->setCurrentIndex(ui->box_current_model->count()-1);
    draw_choose_obj();
}

void MainWindow::on_Tess_up_btn_clicked()
{
    int i = ui->box_current_model->currentIndex();
    if(i<0)
        return;
    QTime tm;
    tm.start();
    this->Mgr->tesselate_up(i+1);
    draw_choose_obj(&tm);
}

void MainWindow::on_Tess_down_btn_clicked()
{
    int i = ui->box_current_model->currentIndex();
    if(i<0)
        return;
    QTime tm;
    tm.start();
    this->Mgr->tesselate_down(i+1);
    draw_choose_obj(&tm);
}

void MainWindow::on_btn_model_scale_plus_clicked()
{
    int i = ui->box_current_model->currentIndex();
    if(i<0)
        return;
    this->Mgr->scale_model(i+1,1.1);
    draw_choose_obj();
}

void MainWindow::on_btn_model_scale_minus_clicked()
{
    int i = ui->box_current_model->currentIndex();
    if(i<0)
        return;
    this->Mgr->scale_model(i+1,0.9);
    draw_choose_obj();
}

void MainWindow::on_btn_move_model_plus_clicked()
{
    int i = ui->box_current_model->currentIndex();
    if(i<0)
        return;
    switch (ui->box_move_model->currentIndex()) {
    case 0:
        this->Mgr->move_model(i+1,20);
        break;
    case 1:
        this->Mgr->move_model(i+1,0,20);
        break;
    case 2:
        this->Mgr->move_model(i+1,0,0,20);
        break;
    default:
        break;
    }
    draw_choose_obj();
}

void MainWindow::on_btn_move_model_minus_clicked()
{
    int i = ui->box_current_model->currentIndex();
    if(i<0)
        return;
    switch (ui->box_move_model->currentIndex()) {
    case 0:
        this->Mgr->move_model(i+1,-20);
        break;
    case 1:
        this->Mgr->move_model(i+1,0,-20);
        break;
    case 2:
        this->Mgr->move_model(i+1,0,0,-20);
        break;
    default:
        break;
    }
    draw_choose_obj();
}

void MainWindow::on_btn_rotate_model_minus_clicked()
{
    int i = ui->box_current_model->currentIndex();
    if(i<0)
        return;
    switch (ui->box_rotate_model->currentIndex()) {
    case 0:
        this->Mgr->rotate_model(i+1,-5,1,0,0);
        break;
    case 1:
        this->Mgr->rotate_model(i+1,-5,0,1,0);
        break;
    case 2:
        this->Mgr->rotate_model(i+1,-5,0,0,1);
        break;
    default:
        break;
    }
    draw_choose_obj();
}

void MainWindow::on_btn_rotate_model_plus_clicked()
{
    int i = ui->box_current_model->currentIndex();
    if(i<0)
        return;
    switch (ui->box_rotate_model->currentIndex()) {
    case 0:
        this->Mgr->rotate_model(i+1,5,1,0,0);
        break;
    case 1:
        this->Mgr->rotate_model(i+1,5,0,1,0);
        break;
    case 2:
        this->Mgr->rotate_model(i+1,5,0,0,1);
        break;
    default:
        break;
    }
    draw_choose_obj();
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox::information(this,"Информация",QString("Эта программная реализация алгоритма тесселяции объекта.\n")+
                                               QString("Для начала работы необходимо загрузить два объекта низкополигональный и\n")+
                             QString("высокополигональный одной и той же модели в формате *.obj.\n"));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    delete this->pix;
    this->pix = new QPixmap(this->size());
    draw_choose_obj();
}
