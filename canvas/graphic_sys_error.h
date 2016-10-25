#ifndef GRAPHIC_SYS_ERROR
#define GRAPHIC_SYS_ERROR
#include "base_error/base_error.h"
namespace graphic_sys_error
{
class model_empty : public base_error
{
public:
    model_empty(){}
    const char* what() override
    {
        return "graphic_sys_error::model is empty";
    }
};

}
#endif // GRAPHIC_SYS_ERROR

