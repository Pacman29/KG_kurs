#ifndef BASE_MODEL_H
#define BASE_MODEL_H
#include "Point3D/point3d.h"
#include "polygon.h"

class base_model
{
public:  
    virtual void add_poligon(Polygon p) = 0;
    virtual void add_poligon(Point3D p1, Point3D p2, Point3D p3, QColor color = Qt::white) = 0;
    void set_name(const char* name) {this->_name = name;}
    const char* get_name() {return this->_name;}
    virtual void init_centre() = 0;
    virtual bool isEmpty() = 0;

    virtual QVector<Polygon>::const_iterator begin() = 0;
    virtual QVector<Polygon>::const_iterator end() = 0;
    typedef QVector<Polygon>::const_iterator const_iterator;

protected:
    const char* _name;

};

#endif // BASE_MODEL_H
