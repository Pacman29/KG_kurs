#ifndef INVISIBLE_OBJ_H
#define INVISIBLE_OBJ_H
#include "Base_obj/base_obj.h"

class invisible_obj : public base_obj
{
public:
    virtual QString type_object()
    {
        return "invisible_obj";
    }
    virtual void execute(base_transform *transform) = 0;
};

#endif // INVISIBLE_OBJ_H
