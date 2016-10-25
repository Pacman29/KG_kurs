#include "base_transform.h"

class base_transformations
{
public:
    virtual ~base_transformations(){}
    virtual bool is_visible() = 0;
};
