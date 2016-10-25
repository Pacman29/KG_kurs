#ifndef BASE_ERROR_H
#define BASE_ERROR_H
#include  <iostream>

class base_error: public std::exception
{
public:
    virtual const char* what() = 0;
};

#endif // BASE_ERROR_H
