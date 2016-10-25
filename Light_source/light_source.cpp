#include "light_source.h"

void Light_source::execute(base_transform *transform)
{
    if(transform->type_transform() == "light_source_trans")
        ((base_light_source_trans*)transform)->execute(this);
}
