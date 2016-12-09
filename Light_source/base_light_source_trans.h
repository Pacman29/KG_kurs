#ifndef BASE_LIGHT_SOURCE_TRANS_H
#define BASE_LIGHT_SOURCE_TRANS_H
#include "Invisible_trans/invisible_trans.h"
#include "light_source.h"
class base_light_source_trans : public Invisible_trans
{
public:
    virtual void execute(Light_source* _light_source) = 0;
    virtual QString type_transform()
    {
        return "base_light_source_transform";
    }
};
#endif // BASE_LIGHT_SOURCE_TRANS_H
