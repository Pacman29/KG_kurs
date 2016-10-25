#ifndef BASE_TRANSFORM_H
#define BASE_TRANSFORM_H
#include <iostream>
class base_transform
{
public:
    base_transform();
    virtual const char* type_transform(){return NULL;}
};

#endif // BASE_TRANSFORM_H
