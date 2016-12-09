#ifndef VISIBLE_TRANS_H
#define VISIBLE_TRANS_H
#include "Base_transform/base_transform.h"

class Visible_trans : public base_transform
{
public:
    virtual ~Visible_trans(){}
    virtual QString type_transform()
    {
        return "visible_transform";
    }
};

#endif // VISIBLE_TRANS_H
