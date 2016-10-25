#ifndef PAINTER_H
#define PAINTER_H
#include "base_painter.h"
#include "painter_error.h"
#include <QPixmap>
class painterImpl : public base_painterImpl
{
public:
    void draw_ligth_source(QPixmap* pix, Light_source lgt) override;
    void draw_polygon(QPixmap* pix,Polygon plg) override;
    void clear_scene(QPixmap* pix) override;
private:
};

class painter :public base_painter
{
public:
    painter(QPixmap* pix) : base_painter(new painterImpl), _pix(pix){}

    void draw_ligth_source(Light_source lgt) override
    {
        this->pntrImpl->draw_ligth_source(_pix,lgt);
    }
    
    void draw_polygon(Polygon plg) override
    {
        this->pntrImpl->draw_polygon(_pix,plg);
    }
    void clear_scene() override
    {
        this->pntrImpl->clear_scene(_pix);
    }
private:
    QPixmap* _pix;
};

#endif // PAINTER_H
