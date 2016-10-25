#include "point3d.h"

Point3D::Point3D(const Point3D &other) : QVector3D()
{
    this->setX(other.x());
    this->setY(other.y());
    this->setZ(other.z());
}

Point3D::Point3D(Point3D &&other)
{
    this->setX(other.x());
    this->setY(other.y());
    this->setZ(other.z());
}

Point3D& Point3D::operator= (const Point3D& other)
{
    this->setX(other.x());
    this->setY(other.y());
    this->setZ(other.z());
    return *this;
}

Point3D& Point3D::operator= (Point3D&& other)
{
    this->setX(other.x());
    this->setY(other.y());
    this->setZ(other.z());
    return *this;
}

Point3D &Point3D::operator=(QVector3D vec)
{
    this->set(vec.x(),vec.y(),vec.z());
    return *this;
}

Point3D Point3D::operator-(const Point3D &other)
{
    return Point3D(this->x() - other.x(),
                this->y() - other.y(),
                this->z() - other.z());
}


float Point3D::get(Point3D::coord_type type)
{
    switch (type) {
    case X:
        return this->x();
    case Y:
        return this->y();
    case Z:
        return this->z();
    }
    return 0;
}

void Point3D::set(Point3D::coord_type type, float value)
{
    switch (type) {
    case X:
        this->setX(value);
    case Y:
        this->setY(value);
    case Z:
        this->setZ(value);
    }
}

void Point3D::set(float x, float y, float z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}
