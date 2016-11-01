#ifndef CANVAS_H
#define CANVAS_H
#include "Model/polygon.h"
#include "Light_source/light_source.h"
#include <QPainter>
class base_painterImpl;

class base_painter
{
public:
    base_painter(base_painterImpl* pntr) : pntrImpl(pntr){}
    virtual ~base_painter()
    {
        delete pntrImpl;
    }

    virtual void draw_ligth_source(Light_source lgt) = 0;
    virtual void draw_polygon(Polygon plg) = 0;
    virtual void draw_centre(QVector3D centre) = 0;
    virtual void clear_scene() = 0;
protected:
    base_painterImpl* pntrImpl;
};

class base_painterImpl
{
public:
    virtual ~base_painterImpl(){}

    virtual void draw_ligth_source(QPixmap* pix,Light_source lgt) = 0;
    virtual void draw_polygon(QPixmap* pix, Polygon plg) = 0;
    virtual void clear_scene(QPixmap* pix) = 0;
    virtual void draw_centre(QPixmap* pix,QVector3D centre) = 0;
};

#endif // CANVAS_H
