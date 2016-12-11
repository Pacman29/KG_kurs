#include "polygon.h"

Polygon::Polygon()
{
    points.push_back(Point3D());
    points.push_back(Point3D());
    points.push_back(Point3D());
    midle_z = 0;
    for(size_t i = 0; i<3; ++i)
        midle_z += points[i].z();
    this->color = Qt::black;
    this->_centre = this->__centre();
}

Polygon::Polygon(Point3D p1, Point3D p2, Point3D p3, QColor color)
{
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    midle_z = 0;
    for(size_t i = 0; i<3; ++i)
        midle_z += points[i].z();
    this->color = color;
    this->_centre = this->__centre();
}

QVector3D Polygon::normal()
{
    return QVector3D::normal(points[2],points[0],points[1]);
}

double Polygon::get_max(Point3D::coord_type type)
{
    float max = points.first().get(type);
    float tmp;
    for(QVector<Point3D>::iterator it = points.begin(); it != points.end(); ++it)
        if((tmp = (*it).get(type)) > max)
            max = tmp;
    return max;
}

double Polygon::get_min(Point3D::coord_type type)
{
    double min = points.first().get(type);
    double tmp;
    for(QVector<Point3D>::iterator it = points.begin(); it != points.end(); ++it)
        if((tmp = (*it).get(type)) < min)
            min = tmp;
    return min;
}

Point3D Polygon::get_centre()
{
    return this->_centre;
}

void Polygon::set_centre(Point3D cnt)
{
    this->_centre = cnt;
}

void Polygon::set_centre(float x, float y, float z)
{
    this->_centre = Point3D(x,y,z);
}

Point3D Polygon::get_middle_side(unsigned int vertex1, unsigned int vertex2)
{
    return Point3D( (points[vertex1].x()+points[vertex2].x()) / 2.,
                    (points[vertex1].y()+points[vertex2].y()) / 2.,
                    (points[vertex1].z()+points[vertex2].z()) / 2.);
}

void Polygon::set_vertexes(Point3D p1,Point3D p2,Point3D p3)
{
    this->points[0]=p1;
    this->points[1]=p2;
    this->points[2]=p3;
    midle_z = 0;
    for(size_t i = 0; i<3; ++i)
        midle_z += points[i].z();
    this->_centre = this->__centre();
}

void Polygon::set_color(QColor clr)
{
    this->color = clr;
}

QColor Polygon::get_color()
{
    return this->color;
}

void Polygon::set_color(qreal h, qreal s, qreal l)
{
    this->color.setHslF(h,s,l);
}

void Polygon::change_point(QMatrix4x4 ch_matrix)
{
    this->midle_z = 0;
    for(QVector<Point3D>::iterator it = points.begin(); it < points.end(); ++it)
    {
        (*it) =  ch_matrix * (*it);
        this->midle_z += it->z();
    }
}

Point3D& Polygon::operator[](size_t index)
{
    return this->points[index];
}

Point3D Polygon::__centre()
{
    return Point3D((this->get_max(Point3D::X)+this->get_min(Point3D::X))/2.,
                   (this->get_max(Point3D::Y)+this->get_min(Point3D::Y))/2.,
                   (this->get_max(Point3D::Z)+this->get_min(Point3D::Z))/2.);
}

bool compare_polygons(Polygon a, Polygon b)
{
    return ( a.midle_z < b.midle_z);
}
