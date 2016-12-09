#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H
#include "Light_source/base_light_source.h"
#include "Invisible_obj/invisible_obj.h"
#include "Base_transform/base_transform.h"

#include <QMatrix4x4>

class Light_source : public base_light_source, public invisible_obj
{
public:
    Light_source(float x = 0,float y = 0,float z = 0){this->position = Point3D(x,y,z);}
    Light_source(Point3D pos){this->position = pos;}
    void move(float posX,float posY,float posZ)
    {
        QMatrix4x4 tmp;
        tmp.translate(posX,posY,posZ);
        this->position = this->position * tmp; 
    }

    void execute(base_transform *transform);

    QString type_object()
    {
        return "light_source";
    }
    Point3D get_position()
    {
        return this->position;
    }
};
#include "base_light_source_trans.h"
#endif // LIGHT_SOURCE_H
