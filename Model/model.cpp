#include "model.h"

model::model()
{
    this->k_tes = 0;
}

model::~model()
{
    this->polygons.clear();
}

void model::add_poligon(Point3D p1, Point3D p2, Point3D p3, QColor color)
{
    this->polygons.push_back(Polygon(p1,p2,p3,color));
}

void model::execute(base_transform *transform)
{
    if(transform->type_transform() == "model_trans")
        ((base_model_trans*)transform)->execute(this);
}

void model::init_centre()
{
    float max_x,max_y,max_z,
            min_x,min_y,min_z;
    max_x = max_y = max_z = -std::numeric_limits<float>::max();
    min_x = min_y = min_z = std::numeric_limits<float>::max();

    float tmp;
    for(QVector<Polygon>::iterator it = polygons.begin(); it != polygons.end(); ++it)
    {
        if ((tmp = it->get_max(Point3D::X)) > max_x)
            max_x = tmp;
        if ((tmp = it->get_max(Point3D::Y)) > max_y)
            max_y = tmp;
        if ((tmp = it->get_max(Point3D::Z)) > max_z)
            max_z = tmp;

        if ((tmp = it->get_min(Point3D::X)) < min_x)
            min_x = tmp;
        if ((tmp = it->get_min(Point3D::Y)) < min_y)
            min_y = tmp;
        if ((tmp = it->get_min(Point3D::Z)) < min_z)
            min_z = tmp;
    }

    this->_centre.setX((max_x+min_x)/2.);
    this->_centre.setY((max_y+min_y)/2.);
    this->_centre.setZ((max_z+min_z)/2.);
}

void model::set_centre(Point3D centre)
{
    this->_centre = centre;
}

void model::set_centre(float x, float y, float z)
{
    this->_centre.setX(x);
    this->_centre.setY(y);
    this->_centre.setZ(z);
}

model model::get_high_model()
{
    return *(this->high_model);
}

void model::set_high_model(model &md)
{
    this->high_model = &md;
}

void model::move(float posX, float posY, float posZ)
{
    QMatrix4x4 tmp;
    tmp.translate(this->_centre);
    tmp.translate(posX,posY,posZ);
    tmp.translate(-this->_centre);

    for(QVector<Polygon>::iterator it = polygons.begin(); it != polygons.end(); ++it)
        it->change_point(tmp);

    this->_centre = tmp * this->_centre;
}

void model::rotate(float angle, float X, float Y, float Z)
{
    QMatrix4x4 tmp;
    tmp.translate(this->_centre);
    tmp.rotate(angle,X,Y,Z);
    tmp.translate(-this->_centre);

    for(QVector<Polygon>::iterator it = polygons.begin(); it != polygons.end(); ++it)
        it->change_point(tmp);
/*
 *     QMatrix4x4 tmp1;
    QMatrix4x4 tmp2;
    QMatrix4x4 tmp3;
    tmp1.translate(-this->_centre);
    for(QVector<Polygon>::iterator it = polygons.begin(); it != polygons.end(); ++it)
        it->change_point(tmp1);
    //tmp.fill(1);
    tmp2.rotate(angle,X,Y,Z);

    for(QVector<Polygon>::iterator it = polygons.begin(); it != polygons.end(); ++it)
        it->change_point(tmp2);
    //tmp.fill(1);
    tmp3.translate(this->_centre);

    for(QVector<Polygon>::iterator it = polygons.begin(); it != polygons.end(); ++it)
        it->change_point(tmp3);
 */
}

void model::scale(float factor)
{
    QMatrix4x4 tmp;
    tmp.translate(this->_centre);
    tmp.scale(factor);
    tmp.translate(-this->_centre);

    for(QVector<Polygon>::iterator it = polygons.begin(); it != polygons.end(); ++it)
        it->change_point(tmp);
    this->_centre = tmp * this->_centre;
}

int model::get_k_ts()
{
    return this->k_tes;
}

void model::inc_k_ts()
{
    this->k_tes++;
}

void model::dec_k_ts()
{
    this->k_tes--;
}

void model::quick_sort()
{
    qSort(this->polygons.begin(),this->polygons.end(),compare_polygons);
}

bool model::isEmpty()
{
    return polygons.isEmpty();
}

void model::set_color(QColor clr)
{
    for(QVector<Polygon>::iterator it = polygons.begin(); it != polygons.end(); ++it)
        it->set_color(clr);
}

