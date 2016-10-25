#include "loader.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "base_error/base_error.h"
using namespace std;

bool file_loaderImpl::Load(base_model &Unit, const char *Name)
{
    FILE* tmp = NULL;
    try
    {
        _Open_File(tmp, Name);
        while(!feof(tmp))
            Unit.add_poligon(get_polygon(tmp));
        Unit.set_name(Name);
        Unit.init_centre();
        _Close_File(tmp);
    }
    catch(base_error&)
    {
        _Close_File(tmp);
        return false;
    }
    return true;
}


void file_loaderImpl::_Open_File(FILE*& FileLoader, const char *Name)
{
    if(! (FileLoader = fopen(Name,"r")))
        throw loader_error::open_error();
}

void file_loaderImpl::_Close_File(FILE*& f)
{
    fclose(f);
}

Polygon file_loaderImpl::get_polygon(FILE *&f)
{
    QVector<Point3D> vec;
    for(size_t i=0; i!=3; ++i)
        vec.push_back(this->get_point(f));
    return Polygon(vec[0],vec[1],vec[2],this->get_color(f));
}

Point3D file_loaderImpl::get_point(FILE *&f)
{
    float x,y,z;
    if(feof(f))
        throw loader_error::file_error();
    if( fscanf(f,"%f %f %f",&x,&y,&z) != 3)
        throw loader_error::file_error();
    return Point3D(x,y,z);
}

QColor file_loaderImpl::get_color(FILE *&f)
{
    int r,g,b;
    if(feof(f))
        throw loader_error::file_error();
    if( fscanf(f,"%d.%d.%d",&r,&g,&b) != 3)
        throw loader_error::file_error();
    return QColor(r,g,b);
}

