#ifndef PAINTER_ERROR
#define PAINTER_ERROR
#include "base_error/base_error.h"
namespace painter_error
{
class pix_null : public base_error
{
public:
    pix_null(){}
    const char* what() override
    {
        return "painer_error::pixmap is NULL";
    }
};

}
#endif // PAINTER_ERROR

