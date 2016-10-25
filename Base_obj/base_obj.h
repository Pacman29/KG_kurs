#ifndef BASE_OBJ_H
#define BASE_OBJ_H
#include "Base_transform/base_transform.h"
#include <iostream>

class base_obj
{
public:
    virtual const char* type_object() {return NULL;}
    virtual void execute(base_transform *transform) = 0;
    virtual bool add(base_obj *)
    {
        return false;
    }
};

#endif // BASE_OBJ_H
