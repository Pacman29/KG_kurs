#ifndef BASE_MODEL_H
#define BASE_MODEL_H
#include "Point3D/point3d.h"
#include "polygon.h"

class base_model
{
public:  
    virtual void add_poligon(Polygon p) = 0;
    virtual void add_poligon(Point3D p1, Point3D p2, Point3D p3, QColor color = Qt::white) = 0;
    void set_name(QString name) {this->_name = name;}
    QString get_name() {return this->_name;}
    virtual QVector<Polygon> get_polygons() {return this->polygons;}
//    virtual void sort(void) = 0;
    virtual void set_color(QColor clr) = 0;
    virtual void init_centre() = 0;
    virtual bool isEmpty() = 0;
    void set_low_size(void){this->low_size = this->polygons.size();}
    size_t get_low_size(void){return this->low_size;}


    virtual QVector<Polygon>::iterator begin() {return this->polygons.begin();}
    virtual QVector<Polygon>::iterator end() {return this->polygons.end();}
    typedef QVector<Polygon>::iterator iterator;

protected:
    size_t low_size;
    QVector<Polygon> polygons;
    QString _name;

};

#endif // BASE_MODEL_H
