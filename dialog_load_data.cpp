#include "dialog_load_data.h"
#include "ui_dialog_load_data.h"

Dialog_load_data::Dialog_load_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_load_data)
{
    ui->setupUi(this);
    this->clr = Qt::white;
    ui->ColorChooser->setStyleSheet("QPushButton{background:"+this->clr.name()+"}");
}

Dialog_load_data::~Dialog_load_data()
{
    delete ui;
}

void Dialog_load_data::on_dir_low_pushButton_clicked()
{
    this->ui->low_lineEdit->setText(QFileDialog::getOpenFileName(this,tr("Выберите низкополигональную модель"),QDir::currentPath(),tr("Objects (*.obj)")));
}

void Dialog_load_data::on_dir_high_pushButton_clicked()
{
    this->ui->high_lineEdit->setText(QFileDialog::getOpenFileName(this,tr("Выберите высокополигональную модель"),QDir::currentPath(),tr("Objects (*.obj)")));
}


void Dialog_load_data::on_buttonBox_accepted()
{
    if( ((this->high_dir = this->ui->high_lineEdit->text()) == "") ||
            ((this->low_dir = this->ui->low_lineEdit->text()) == "")  )
    {
        QMessageBox::warning(this,"Ошибка","Не выбраны файлы для загрузки!");
        emit this->dialog_closed();
        return;
    }
    emit this->dialog_choosed(this->low_dir,this->high_dir,this->clr);
}

void Dialog_load_data::on_buttonBox_rejected()
{
    emit this->dialog_closed();
}

void Dialog_load_data::on_Dialog_load_data_rejected()
{
    emit this->dialog_closed();
}

void Dialog_load_data::on_ColorChooser_clicked()
{
    this->clr = QColorDialog::getColor();
    ui->ColorChooser->setStyleSheet("QPushButton{background:"+this->clr.name()+"}");
}
