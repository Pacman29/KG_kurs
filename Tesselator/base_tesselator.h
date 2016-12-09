#ifndef BASE_TESSELATOR_H
#define BASE_TESSELATOR_H
class model;

class base_tesselator
{
public:
    enum tess_state {UP,DOWN};
    base_tesselator();

    virtual void tesselate(tess_state state, model *mdl) = 0;
};
#include "Model/model.h"
#endif // BASE_TESSELATOR_H
