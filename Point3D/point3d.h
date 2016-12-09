#ifndef POINT3D_H
#define POINT3D_H
#include "Visible_obj/visible_obj.h"
#include <QVector3D>
#include "Base_transform/base_transform.h"

class Point3D : public visible_obj, public QVector3D
{
public:
    enum coord_type {X,Y,Z};
    Point3D(float x = 0,float y = 0,float z = 0) : QVector3D(x,y,z){}

    Point3D(const Point3D& other);
    Point3D(Point3D&& other);

    Point3D& operator= (const Point3D& other);
    Point3D& operator= (Point3D&& other);

    Point3D& operator= (QVector3D vec);

    Point3D  operator- (const Point3D& other);

    void inc(float x = 0,float y = 0,float z = 0);
    
    float get(coord_type type);
    void set(coord_type type, float value);
    void set(float x = 0,float y = 0,float z = 0);
    void execute(base_transform *transform){}
};

#endif // POINT3D_H
