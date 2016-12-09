#ifndef DIALOG_LOAD_DATA_H
#define DIALOG_LOAD_DATA_H

#include <QDialog>
#include <QDir>
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
namespace Ui {
class Dialog_load_data;
}

class Dialog_load_data : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_load_data(QWidget *parent = 0);
    ~Dialog_load_data();
Q_SIGNALS:
    void dialog_closed();
    void dialog_choosed(QString low,QString high,QColor clr);
private slots:
    void on_dir_low_pushButton_clicked();

    void on_dir_high_pushButton_clicked();


    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_Dialog_load_data_rejected();

    void on_ColorChooser_clicked();

private:
    Ui::Dialog_load_data *ui;
    QString low_dir;
    QString high_dir;
    QColor clr;
};

#endif // DIALOG_LOAD_DATA_H
