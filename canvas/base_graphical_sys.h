#ifndef BASE_GRAPHICAL_SYS
#define BASE_GRAPHICAL_SYS
#include "Model/base_model.h"
#include "Composit_obj/composit_object.h"
#include "painter.h"
#include "Camera/base_camera.h"
class base_Graphical_sys_Impl;

class Graphical_sys_base
{
public:
    Graphical_sys_base(base_Graphical_sys_Impl* Gr) : GrImpl(Gr){}
    virtual ~Graphical_sys_base()
    {
        delete GrImpl;
    }
    virtual void Draw_scene(composit_object& composit, base_camera& cam) = 0;
    virtual void clear_scene() = 0;
    virtual void set_scene(base_painter& pntr) = 0;
protected:
    base_Graphical_sys_Impl* GrImpl;
};

class base_Graphical_sys_Impl
{
public:
    virtual ~base_Graphical_sys_Impl(){}
    virtual void Draw_scene(base_painter *pntr, composit_object& composit, base_camera& cam) = 0;
    virtual void clear_scene(base_painter *pntr) = 0;
};

#endif // BASE_GRAPHICAL_SYS

