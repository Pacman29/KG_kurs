#ifndef BASE_CAMERA_TRANSFORMATIONS
#define BASE_CAMERA_TRANSFORMATIONS
#include "Invisible_trans/invisible_trans.h"
#include "camera.h"
class base_camera_transformations : public Invisible_trans
{
public:
    virtual void execute(camera* _camera) = 0;
    virtual const char* type_transform()
    {
        return "base_camera_transform";
    }
};
#endif // BASE_CAMERA_TRANSFORMATIONS

