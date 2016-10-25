#ifndef GRAPHICAL_SYS_H
#define GRAPHICAL_SYS_H
#include "base_graphical_sys.h"
#include "graphic_sys_error.h"
#include "Model/base_model.h"
#include "Light_source/light_source.h"
class Graphical_sysImpl : public base_Graphical_sys_Impl
{
public:
    void Draw_scene(base_painter *pntr,composit_object& composit, base_camera& cam) override;
    void clear_scene(base_painter* pntr) override;
};

class Graphical_sys : public Graphical_sys_base
{
public:
    Graphical_sys() : Graphical_sys_base(new Graphical_sysImpl){}
    void Draw_scene(composit_object& composit, base_camera& cam) override
    {
        this->GrImpl->Draw_scene(this->_painter,composit,cam);
    }
    void clear_scene() override
    {
        this->GrImpl->clear_scene(this->_painter);
    }
    void set_scene(base_painter &pntr) override
    {
        this->_painter = &pntr;
    }
private:
    base_painter *_painter;
};

#endif // GRAPHICAL_SYS_H
