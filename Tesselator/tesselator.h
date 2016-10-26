#ifndef TESSELATOR_H
#define TESSELATOR_H
#include "Model/model.h"
#include "Point3D/point3d.h"
class model;

class tesselator
{
public:
    enum tess_state {UP,DOWN};
    tesselator();

    void tesselate(tess_state state, model *mdl, model high_model);
    friend class model;
private:
    void tesselate_up(model* mdl,model& high_model);
    void tesselate_down(model *mdl, model& high_model);
    void correct(Point3D &p1, Point3D &p2, Point3D &p3, model &high_model, int begin);
    float distance(Point3D p1, Point3D p2);

    Point3D get(Polygon p1, Polygon p2);
    bool check(Polygon p1, Polygon p2);
};

#endif // TESSELATOR_H
