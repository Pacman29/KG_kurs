#include "model.h"

model::model()
{
    this->k_tes = 0;
    this->high_model = NULL;
    this->_scale = 1;
    this->_pos = Point3D();
    this->_coord_rotate = Point3D();
    this->_rotate = 0;

}

model::~model()
{
    this->polygons.clear();
    if(this->high_model)
        delete this->high_model;
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


//void model::sort()
//{
//    QStack<Polygon> stack;
//    QVector<Polygon> read = this->polygons;
//    QVector<Polygon> sorted(this->polygons.size());
//    stack.push(*(read.begin()));
//    read.erase(read.begin());
//    while(!stack.isEmpty())
//    {
//        sorted.push_back(stack.pop());
//        Point3D p1 = sorted.last()[0],
//                p2 = sorted.last()[1],
//                p3 = sorted.last()[2];
//        Polygon tmp2,tmp3,tmp4;
//        for(QVector::iterator it = read.begin(); it != read.end(); ++it)
//        {
//            if()
//        }

//    }
//}

model model::get_high_model()
{
    return *(this->high_model);
}

void model::set_high_model(model &md)
{
    this->high_model = &md;
    this->_centre = this->high_model->_centre;
}

void model::move(float posX, float posY, float posZ)
{
    this->_pos.inc(posX,posY,posZ);

    QMatrix4x4 tmp;
    tmp.translate(this->_centre);
    tmp.translate(posX,posY,posZ);
    tmp.translate(-this->_centre);

    #pragma omp parallel for
    for(QVector<Polygon>::iterator it = polygons.begin(); it < polygons.end(); ++it)
        it->change_point(tmp);
    #pragma omp barrier

    this->_centre = tmp * this->_centre;

    if(this->high_model)
        this->high_model->move(posX,posY,posZ);
}

void model::move_to_position(float posX, float posY, float posZ)
{
    QMatrix4x4 tmp;
    tmp.translate(-this->_centre);
    tmp.translate(posX,posY,posZ);

    #pragma omp parallel for
    for(QVector<Polygon>::iterator it = polygons.begin(); it < polygons.end(); ++it)
        it->change_point(tmp);
    #pragma omp barrier

    this->_centre = tmp * this->_centre;

    if(this->high_model)
        this->high_model->move_to_position(posX,posY,posZ);
}

void model::rotate(float angle, float X, float Y, float Z)
{

    this->_rotate += angle;
    this->_coord_rotate = Point3D(X,Y,Z);

    QMatrix4x4 tmp;
    tmp.translate(this->_centre);
    tmp.rotate(angle,X,Y,Z);
    tmp.translate(-this->_centre);

    #pragma omp parallel for
    for(QVector<Polygon>::iterator it = polygons.begin(); it < polygons.end(); ++it)
        it->change_point(tmp);
    #pragma omp barrier
    if(this->high_model)
        this->high_model->rotate(angle,X,Y,Z);
}

void model::scale(float factor)
{
    this->_scale *= factor;
    QMatrix4x4 tmp;
    tmp.translate(this->_centre);
    tmp.scale(factor);
    tmp.translate(-this->_centre);

    #pragma omp parallel for
    for(QVector<Polygon>::iterator it = polygons.begin(); it < polygons.end(); ++it)
        it->change_point(tmp);
    #pragma omp barrier
    this->_centre = tmp * this->_centre;
    if(this->high_model)
        this->high_model->scale(factor);
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

