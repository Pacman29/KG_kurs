#include "painter.h"
#include "QDebug"
void painterImpl::draw_ligth_source(QPixmap *pix, Light_source lgt)
{
    QPainter pntr(pix);
    pntr.setBrush(QBrush(Qt::yellow));
    pntr.setPen(Qt::yellow);
    Point3D tmp = lgt.get_position();
    pntr.drawEllipse(QPointF(tmp.x()+pix->width()/2,tmp.y()+pix->height()/2),2,2);
}

void painterImpl::draw_polygon(QPixmap* pix,Polygon plg)
{
    if(pix->isNull())
        throw painter_error::pix_null();

    size_t _centre_x = pix->width()/2;
    size_t _centre_y = pix->height()/2;
    QPainter pntr(pix);
    pntr.setPen(Qt::black);
    pntr.setBrush(QBrush(plg.get_color()));

    QPointF pnts[3] = {
        QPointF(plg[0].x()+_centre_x,plg[0].y()+_centre_y),
        QPointF(plg[1].x()+_centre_x,plg[1].y()+_centre_y),
        QPointF(plg[2].x()+_centre_x,plg[2].y()+_centre_y)
    };
    pntr.drawPolygon(pnts,3);
}

void painterImpl::clear_scene(QPixmap* pix)
{
    pix->fill();
}

void painterImpl::draw_centre(QPixmap *pix, QVector3D centre)
{
    QPainter pntr(pix);
    pntr.setPen(Qt::black);
    pntr.setBrush(QBrush(Qt::red));
    float x = centre.x()+pix->width()/2,
          y = centre.y()+pix->height()/2;

    pntr.drawEllipse(QPointF(x,y),3,3);
}

