#ifndef POLYGON_H
#define POLYGON_H
#include "Visible_obj/visible_obj.h"
#include <QVector>
#include "Point3D/point3d.h"
#include <QVector3D>
#include <QColor>
#include <QMatrix4x4>
#include "Base_transform/base_transform.h"

/* Лицевая сторона полигона определяется по расположению
 * координат вершин (против часовой стрелке)
 *      p3
 *      /\
 *     /  \
 *    /    \
 *   /______\
 *  p1       p2   [(p1-p3)x(p2-p3)] = norm к нам
*/


class Polygon
{
public:
    Polygon();

    Polygon(Point3D p1,Point3D p2,Point3D p3, QColor color = Qt::white);

    QVector3D normal();

    double get_max(Point3D::coord_type type);
    double get_min(Point3D::coord_type type);

    Point3D get_centre();
    void set_centre(Point3D cnt);
    void set_centre(float x,float y,float z);

    Point3D get_middle_side(unsigned int vertex1,unsigned int vertex2);

    void set_vertexes(Point3D p1,Point3D p2,Point3D p3);

    void set_color(QColor clr);
    void set_color(qreal h, qreal s, qreal l);
    QColor get_color();

    bool operator <(const Polygon value) const
    {
        return ( (points[0].z() + points[1].z() + points[2].z()) < (value.points[0].z() + value.points[1].z() + value.points[2].z()));
    }

    bool operator == (const Polygon value) const
    {
        return ( (points[0].z() + points[1].z() + points[2].z()) == (value.points[0].z() + value.points[1].z() + value.points[2].z()));
    }

    bool operator > (const Polygon value) const
    {
        return ( (points[0].z() + points[1].z() + points[2].z()) > (value.points[0].z() + value.points[1].z() + value.points[2].z()));
    }

    bool operator != (const Polygon value) const
    {
        return ( (points[0].z() + points[1].z() + points[2].z()) != (value.points[0].z() + value.points[1].z() + value.points[2].z()));
    }

    bool operator >= (const Polygon value) const
    {
        return ( (points[0].z() + points[1].z() + points[2].z()) >= (value.points[0].z() + value.points[1].z() + value.points[2].z()));
    }

    bool operator <= (const Polygon value) const
    {
        return ( (points[0].z() + points[1].z() + points[2].z()) == (value.points[0].z() + value.points[1].z() + value.points[2].z()));
    }

    void change_point(QMatrix4x4 ch_matrix);

    Point3D& operator[] (size_t index);
private:
    Point3D __centre();
    QVector<Point3D> points;
    Point3D _centre;
    QColor color;
};

bool compare_polygons(Polygon a, Polygon b);
#endif // POLYGON_H
