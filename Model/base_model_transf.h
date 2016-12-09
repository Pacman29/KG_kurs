#ifndef BASE_MODEL_TRANSF_H
#define BASE_MODEL_TRANSF_H
#include "Visible_trans/visible_trans.h"
#include "model.h"
class base_model_trans : public Visible_trans
{
public:
    virtual void execute(model* _model) = 0;
    virtual QString type_transform()
    {
        return "base_model_transform";
    }
};
#endif // BASE_MODEL_TRANSF_H
