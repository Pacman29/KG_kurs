#include "camera.h"
#include "base_camera_transformations.h"

camera::camera()
{
    this->right[0] = 1;
    this->up[1] = 1;
    this->look[2] = 1;
    this ->change_flag = 1;
}

camera::camera(Point3D &pos, Point3D &target, double &pitch, double &yaw, double &roll)
{
    this->pos = pos;
    this->target = target;
    this->right[0] = 1;
    this->up[1] = 1;
    this->look[2] = 1;
    this->pitch(pitch);
    this->yaw(yaw);
    this->roll(roll);
    this ->change_flag = 1;
    this->len = distance_centre();
}

void camera::set_position(Point3D pos)
{
    this->pos = pos;
    this ->change_flag = 1;
    this->len = distance_centre();
}

void camera::set_target(Point3D target)
{
    this->target = target;
    this ->change_flag = 1;
    this->len = distance_centre();
}

void camera::RotationUpDownSphere(double angle)
{
    QMatrix4x4 tr;
    tr.rotate(angle,this->up);
    this->right = this->right * tr;
    this->look = this->look * tr;
    QMatrix4x4 move;
    move.translate(-(this->target));
    move.rotate(angle,this->up);
    move.translate(this->target);

    this->pos = this->pos * move;

    this ->change_flag = 1;
}

void camera::RotationRightLeftSphere(double angle)
{
    QMatrix4x4 tr;
    tr.rotate(angle,this->right);
    this->up = this->up * tr;
    this->look = this->look * tr;
    QMatrix4x4 move;
    move.translate(-(this->target));
    move.rotate(angle,this->right);
    move.translate(this->target);

    this->pos = this->pos * move;
    this ->change_flag = 1;
}

void camera::execute(base_transform *transform)
{
    if(transform->type_transform() == "camera_transform")
        ((base_camera_transformations*)transform)->execute(this);
    this ->change_flag = 1;
}

bool camera::is_Change()
{
    return this->change_flag;
}

void camera::inc_range(size_t value)
{
    this->len+=value;
}

void camera::dec_range(size_t value)
{
    this->len-=value;
}

void camera::pitch(double angle)
{
    QMatrix4x4 tr;
    tr.rotate(angle,this->right);

    this->up = this->up * tr;
    this->look = this->look * tr;
    this ->change_flag = 1;
}

void camera::yaw(double angle)
{
    QMatrix4x4 tr;
    tr.rotate(angle,this->up);

    this->right = this->right * tr;
    this->look = this->look * tr;
    this ->change_flag = 1;
}

void camera::roll(double angle)
{
    QMatrix4x4 tr;
    tr.rotate(angle,this->look);

    this->right = this->right * tr;
    this->up = this->up * tr;
    this ->change_flag = 1;
}

float camera::distance_centre()
{
    return (this->target-this->pos).length();
}



QMatrix4x4 camera::GetViewMatrix()
{
    this->look.normalize();
    this->up = QVector3D::crossProduct(this->look,this->right);
    this->up.normalize();

    this->right = QVector3D::crossProduct(this->up,this->look);
    this->right.normalize();

    float x = -QVector3D::dotProduct(this->right,this->pos);
    float y = -QVector3D::dotProduct(this->up,this->pos);
    float z = -QVector3D::dotProduct(this->look,this->pos);

    QMatrix4x4 tmp;
    tmp.setColumn(0,this->right);
    tmp.setColumn(1,this->up);
    tmp.setColumn(2,this->look);
    tmp.setColumn(3,QVector4D(x,y,z,1));
    float dc = this->len;
    float factor = (dc) ? (500/dc) : (1);
    tmp.scale(factor);
    this ->change_flag = 0;
    return tmp;
}


