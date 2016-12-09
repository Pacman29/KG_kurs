#ifndef CAMERA_TRANSFORMATIONS
#define CAMERA_TRANSFORMATIONS
#include "base_camera_transformations.h"
#include "camera.h"
#include "cmath"

namespace camera_transform
{
class yaw : public base_camera_transformations
{
public:
    yaw(double degree)
    {
        this->_angle = degree * M_PI/180.0;
    }

    void execute(camera* _camera) override
    {
        _camera->yaw(this->_angle);
    }
    QString type_transform() override final
    {
        return "camera_transform";
    }
private:
    double _angle;
};

class pitch : public base_camera_transformations
{
public:
    pitch(double degree)
    {
        this->_angle = degree * M_PI/180.0;
    }

    void execute(camera* _camera) override
    {
        _camera->pitch(this->_angle);
    }
    QString type_transform() override final
    {
        return "camera_transform";
    }
private:
    double _angle;
};

class roll : public base_camera_transformations
{
public:
    roll(double degree)
    {
        this->_angle = degree * M_PI/180.0;
    }

    void execute(camera* _camera) override
    {
        _camera->roll(this->_angle);
    }
    QString type_transform() override final
    {
        return "camera_transform";
    }
private:
    double _angle;
};

class position : public base_camera_transformations
{
public:
    position(Point3D pos)
    {
        this->_pos = pos;
    }

    void execute(camera* _camera) override
    {
        _camera->set_position(this->_pos);
    }
    QString type_transform() override final
    {
        return "camera_transform";
    }
private:
    Point3D _pos;
};

class target : public base_camera_transformations
{
public:
    target(Point3D target)
    {
        this->_target = target;
    }

    void execute(camera* _camera) override
    {
        _camera->set_target(this->_target);
    }
    QString type_transform() override final
    {
        return "camera_transform";
    }
private:
    Point3D _target;
};
}
#endif // CAMERA_TRANSFORMATIONS

