#ifndef VISIBLE_OBJ_H
#define VISIBLE_OBJ_H
#include "Base_obj/base_obj.h"

class visible_obj : public base_obj
{
public:
    virtual QString type_object()
    {
        return "visible_obj";
    }
    virtual void execute(base_transform *transform) = 0;
};

#endif // VISIBLE_OBJ_H
