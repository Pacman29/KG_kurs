#ifndef LOADER_H
#define LOADER_H
#include "base_loader.h"
#include "loader_error.h"
#include <iostream>
#include "Model/polygon.h"
class file_loaderImpl : public base_loaderImpl
{
public:
    bool Load(base_model &Unit, const char *Name);
private:
    void _Open_File(FILE*& FileLoader, const char *Name);
    void _Close_File(FILE*& f);
    Polygon get_polygon(FILE*& f);
    Point3D get_point(FILE*& f);
    QColor get_color(FILE*& f);
    
};

class file_loader : public base_loader
{
public:
    file_loader() : base_loader(new file_loaderImpl){}
    bool Load(base_model &Unit, const char *Name)
    {
        return this->ldImpl->Load(Unit,Name);
    }
};

#endif // LOADER_H
