#ifndef INVISIBLE_TRANS_H
#define INVISIBLE_TRANS_H
#include "Base_transform/base_transform.h"

class Invisible_trans : public base_transform
{
public:
    virtual ~Invisible_trans(){}
    virtual const char* type_transform()
    {
        return "invisible_transform";
    }
};

#endif // INVISIBLE_TRANS_H
