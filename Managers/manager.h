#ifndef MANAGER_H
#define MANAGER_H
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <Camera/camera.h>
#include <Composit_obj/composit_object.h>
#include <loader/base_loader.h>
#include <Model/model.h>
#include <Model/model_transf.h>
#include <canvas/graphical_sys.h>
#include <canvas/painter.h>
#include <Tesselator/tesselator.h>
class Manager
{
public:
    Manager(QWidget* parent, base_loader *loader, Graphical_sys_base* gr, base_painter* pntr, base_tesselator* ts);
    ~Manager(void);


    int add_camera(void);
    int add_model(QString low_model_dir, QString high_model_dir, QColor color);
    void cam_inc_range(size_t id,size_t value);
    void cam_dec_range(size_t id,size_t value);
    void delete_model(size_t id);
    void rotate_model(size_t id, float angle, float X, float Y, float Z);
    void move_model(size_t id, float posX = 0, float posY = 0, float posZ = 0);
    void scale_model(size_t id, float scale);
    void set_pixmap(QPixmap* pix);
    void draw_scene(size_t cam_id,size_t model_id);
    void cam_set_position(size_t id,Point3D pos);
    void cam_set_target(size_t id,Point3D target);
    void cam_pitch(size_t id,double angle);
    void cam_yaw(size_t id,double angle);
    void cam_roll(size_t id,double angle);
    void tesselate_up(size_t id);
    void tesselate_down(size_t id);
    void load_model(QString low,QString high,QColor clr);
private:
    QVector<camera> cams;
    composit_object objects;
    base_loader* loader;
    QWidget* parent;
    Graphical_sys_base* gr;
    QPixmap* pix;
    base_painter* pntr;
    base_tesselator* ts;
};

#endif // MANAGER_H
