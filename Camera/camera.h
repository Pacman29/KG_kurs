#ifndef CAMERA_H
#define CAMERA_H
#include "camera_error.h"
#include "base_camera.h"
#include "Invisible_obj/invisible_obj.h"
class camera : public base_camera, public invisible_obj
{
public:
    camera();
    camera(Point3D& pos, Point3D& target, double& pitch, double& yaw, double& roll);
    void set_position(Point3D pos) override;
    void set_target(Point3D target) override;
    QMatrix4x4 GetViewMatrix() override;
    void RotationUpDownSphere(double angle) override;
    void RotationRightLeftSphere(double angle) override;

    void execute(base_transform *transform) override;

    void pitch(double angle) override;
    void yaw(double angle) override;
    void roll(double angle) override;

    const char* type_object()
    {
        return "camera";
    }
};
#endif // CAMERA_H
