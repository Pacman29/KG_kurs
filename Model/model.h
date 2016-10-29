#ifndef MODEL_H
#define MODEL_H
#include "Visible_obj/visible_obj.h"
#include "Composit_obj/composit_object.h"
#include "base_model.h"
#include "polygon.h"
#include "Base_transform/base_transform.h"
#include <QMatrix4x4>
#include "Tesselator/tesselator.h"

class model : public visible_obj, public base_model
{
public:
    model();
    ~model();
    void add_poligon(Polygon p){ this->polygons.push_back(p);}
    void add_poligon(Point3D p1, Point3D p2, Point3D p3, QColor color = Qt::white);
    void execute(base_transform *transform);
    void init_centre() override final;
    void set_centre(Point3D centre);
    void set_centre(float x,float y,float z);

    int get_size()
    {
        return this->polygons.size();
    }

    const char* type_object()
    {
        return "model";
    }

    model get_high_model(void);
    void set_high_model(model &md);

    void move(float posX = 0, float posY = 0, float posZ = 0);
    void rotate(float angle, float X,float Y ,float Z);
    void scale(float factor);

    int get_k_ts();
    void inc_k_ts();
    void dec_k_ts();

    void quick_sort();

    bool isEmpty() override final;


    QVector<Polygon>::const_iterator begin()
    {
        return polygons.begin();
    }
    QVector<Polygon>::const_iterator end()
    {
        return polygons.end();
    }

    int size() const
    {
        return polygons.size();
    }

    friend class tesselator;
private:
    QVector<Polygon> polygons;
    QVector3D _centre;
    int k_tes;
    model* high_model;
};
#include "base_model_transf.h"
#endif // MODEL_H
