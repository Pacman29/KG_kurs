#include "manager.h"

Manager::Manager(QWidget* parent, base_loader *loader, Graphical_sys_base *gr, base_painter *pntr, base_tesselator *ts)
{
    this->loader = loader;
    this->parent = parent;
    this->gr = gr;
    this->pntr = pntr;
    gr->set_scene(*pntr);
    this->ts = ts;
}

Manager::~Manager()
{
    delete this->loader;
    delete this->gr;
    delete this->pntr;
    delete this->ts;
}

int Manager::add_camera()
{
    this->cams.push_back(camera());
    return this->cams.size()-1;
}

int Manager::add_model(QString low_model_dir,QString high_model_dir, QColor color)
{
    model* tmp_low = new model;
    model* tmp_high = new model;
    try
    {
        this->loader->Load(*tmp_low,low_model_dir,color);
        this->loader->Load(*tmp_high,high_model_dir,color);
        tmp_low->set_high_model(*tmp_high);
        tmp_low->move_to_position();
        this->objects.add(tmp_low);

    }
    catch(base_error& err)
    {
        delete tmp_high;
        delete tmp_low;
        QMessageBox::warning(this->parent,"ERROR!",err.what());
        return 0;
    }
    return this->objects.size();
}

void Manager::cam_inc_range(size_t id, size_t value)
{
    this->cams[id].inc_range(value);
}

void Manager::cam_dec_range(size_t id, size_t value)
{
    this->cams[id].dec_range(value);
}

void Manager::delete_model(size_t id)
{
    if(!id)
        this->objects.dell_all();
    else
        this->objects.del(id-1);
}

void Manager::rotate_model(size_t id, float angle, float X, float Y, float Z)
{
    base_model_trans* trans =(base_model_trans*) new model_trans::rotate(angle,X,Y,Z);
    if(!id)
        this->objects.execute(trans);
    else
        this->objects[id-1]->execute(trans);

}

void Manager::move_model(size_t id, float posX, float posY, float posZ)
{
    base_model_trans* trans =(base_model_trans*) new model_trans::move(posX,posY,posZ);
    if(!id)
        this->objects.execute(trans);
    else
        this->objects[id-1]->execute(trans);
}

void Manager::scale_model(size_t id, float scale)
{
    base_model_trans* trans =(base_model_trans*) new model_trans::scale(scale);
    if(!id)
        this->objects.execute(trans);
    else
        this->objects[id-1]->execute(trans);
}

void Manager::set_pixmap(QPixmap *pix)
{
    this->pix = pix;
}

void Manager::draw_scene(size_t cam_id,size_t model_id)
{
    this->gr->clear_scene();
    if(model_id)
        this->gr->Draw_scene((model*)this->objects[model_id-1],this->cams[cam_id]);
    else
        this->gr->Draw_scene(this->objects,this->cams[cam_id]);
}

void Manager::cam_set_position(size_t id, Point3D pos)
{
    base_camera_transformations *trans = new camera_transform::position(pos);
    if(!id)
        for(QVector<camera>::iterator it = this->cams.begin(); it<this->cams.end(); ++it)
            it->execute(trans);
    else
        this->cams[id-1].execute(trans);
}

void Manager::cam_set_target(size_t id, Point3D target)
{
    base_camera_transformations *trans = new camera_transform::target(target);
    if(!id)
        for(QVector<camera>::iterator it = this->cams.begin(); it<this->cams.end(); ++it)
            it->execute(trans);
    else
        this->cams[id-1].execute(trans);
}

void Manager::cam_pitch(size_t id, double angle)
{
    base_camera_transformations *trans = new camera_transform::pitch(angle);
    if(!id)
        for(QVector<camera>::iterator it = this->cams.begin(); it<this->cams.end(); ++it)
            it->execute(trans);
    else
        this->cams[id-1].execute(trans);
}

void Manager::cam_yaw(size_t id, double angle)
{
    base_camera_transformations *trans = new camera_transform::yaw(angle);
    if(!id)
        for(QVector<camera>::iterator it = this->cams.begin(); it<this->cams.end(); ++it)
            it->execute(trans);
    else
        this->cams[id-1].execute(trans);
}

void Manager::cam_roll(size_t id, double angle)
{
    base_camera_transformations *trans = new camera_transform::roll(angle);
    if(!id)
        for(QVector<camera>::iterator it = this->cams.begin(); it<this->cams.end(); ++it)
            it->execute(trans);
    else
        this->cams[id-1].execute(trans);
}

void Manager::tesselate_up(size_t id)
{
    if(!id)
    {
        #pragma omp parallel for
        for(composit_object::iterator it = this->objects.begin(); it<this->objects.end(); ++it)
            ts->tesselate(base_tesselator::UP,(model*)it);
        #pragma omp barrier
    }
    else
        ts->tesselate(base_tesselator::UP,(model*)this->objects[id-1]);
}

void Manager::tesselate_down(size_t id)
{
    if(!id)
    {
        #pragma omp parallel for
        for(composit_object::iterator it = this->objects.begin(); it<this->objects.end(); ++it)
            ts->tesselate(base_tesselator::DOWN,(model*)it);
        #pragma omp barrier
    }
    else
        ts->tesselate(base_tesselator::DOWN,(model*)this->objects[id-1]);
}

void Manager::load_model(QString low, QString high, QColor clr)
{
    model *mdl = new model();
    model *h_mdl = new model();
    this->loader->Load(*mdl,low,clr);
    this->loader->Load(*h_mdl,high,clr);
    mdl->set_high_model(*h_mdl);
    this->objects.add(mdl);
}
