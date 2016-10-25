#ifndef LOADER_ERROR
#define LOADER_ERROR
#include "base_error/base_error.h"
namespace loader_error {

class open_error : public base_error
{
public:
    open_error(){}
    const char* what() override
    {
        return "loader_error::file not open";
    }
};

class file_error : public base_error
{
public:
    file_error(){}
    const char* what() override
    {
        return "loader_error::incorrect input file";
    }
};
}

#endif // LOADER_ERROR

