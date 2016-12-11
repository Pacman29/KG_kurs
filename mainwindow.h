#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog_load_data.h>
#include <QPixmap>
#include <Managers/manager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void _show();
    ~MainWindow();
private:
    void draw_choose_obj(QTime *tm = NULL);
private slots:

    void load_files(QString low, QString high, QColor clr);

    void dir_signal_close();
    
    void on_action_triggered();

    void on_btn_scale_plus_clicked();

    void on_btn_scale_minus_clicked();

    void on_btn_pitch_plus_clicked();

    void on_btn_pitch_minus_clicked();

    void on_btn_yaw_plus_clicked();

    void on_btn_yaw_minus_clicked();

    void on_btn_roll_plus_clicked();

    void on_btn_roll_minus_clicked();

    void on_box_current_model_currentIndexChanged(int index);

    void on_delete_model_pushButton_clicked();

    void on_Tess_up_btn_clicked();

    void on_Tess_down_btn_clicked();

    void on_btn_model_scale_plus_clicked();

    void on_btn_model_scale_minus_clicked();

    void on_btn_move_model_plus_clicked();

    void on_btn_move_model_minus_clicked();

    void on_btn_rotate_model_minus_clicked();

    void on_btn_rotate_model_plus_clicked();

    void on_action_2_triggered();

    void resizeEvent(QResizeEvent *event);
private:
    Manager *Mgr;
    QPixmap *pix;
    Ui::MainWindow *ui;
    Dialog_load_data DirWind;
    
};

#endif // MAINWINDOW_H
