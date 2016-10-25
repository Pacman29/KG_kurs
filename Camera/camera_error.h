#ifndef CAMERA_ERROR
#define CAMERA_ERROR
#include <iostream>
using namespace std;
namespace camera_error
{
class empty_error : public std::exception
{
public:
    empty_error(){}
    const char* what()
    {
        return "camera_error::camera array is empty";
    }
};
}
#endif // CAMERA_ERROR

