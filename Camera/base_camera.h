#ifndef BASE_CAMERA
#define BASE_CAMERA
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <Point3D/point3d.h>
#include "Base_transform/base_transform.h"
class base_camera
{
public:
    virtual void set_target(Point3D target) = 0;
    virtual void set_position(Point3D pos) = 0;
    virtual QMatrix4x4 GetViewMatrix() = 0;
    virtual void RotationUpDownSphere(double angle) = 0;
    virtual void RotationRightLeftSphere(double angle) = 0;
    virtual void pitch(double angle) = 0;
    virtual void yaw(double angle) = 0;
    virtual void roll(double angle) = 0;

protected:
    QVector3D look;
    QVector3D up;
    QVector3D right;

    QVector3D pos;
    QVector3D target;
};
#endif // BASE_CAMERA

