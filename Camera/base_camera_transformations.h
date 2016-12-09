#ifndef BASE_CAMERA_TRANSFORMATIONS
#define BASE_CAMERA_TRANSFORMATIONS
#include "Invisible_trans/invisible_trans.h"
class camera;
class base_camera_transformations : public Invisible_trans
{
public:
    virtual void execute(camera* _camera) = 0;
    virtual QString type_transform()
    {
        return "base_camera_transform";
    }
};
#include "camera.h"
#endif // BASE_CAMERA_TRANSFORMATIONS

