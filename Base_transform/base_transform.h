#ifndef BASE_TRANSFORM_H
#define BASE_TRANSFORM_H
#include <QString>
class base_transform
{
public:
    base_transform(){}
    virtual QString type_transform(){return NULL;}
};

#endif // BASE_TRANSFORM_H
