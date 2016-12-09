#ifndef TESSELATOR_H
#define TESSELATOR_H
#include "Point3D/point3d.h"
#include "base_tesselator.h"
class model;

class tesselator : public base_tesselator
{
public:
    tesselator();
    void tesselate(base_tesselator::tess_state state, model *mdl);
    friend class model;
private:
    void tesselate_up(model* mdl);
    void tesselate_down(model *mdl);
    void correct(Point3D &p1, Point3D &p2, Point3D &p3, QVector<Polygon> &high_pol, int begin);
    float distance(Point3D p1, Point3D p2);

    Point3D get(Polygon p1, Polygon p2);
    bool check(Polygon p1, Polygon p2);
};
#include "Model/model.h"
#endif // TESSELATOR_H
