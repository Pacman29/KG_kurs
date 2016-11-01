#include "loader.h"
#include <cstdio>
#include <stdio.h>
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

bool file_loaderImpl::Load(base_model &Unit, const char *Name, QColor clr)
{
    FILE* tmp = NULL;
    try
    {
        _Open_File(tmp, Name);
        while(!feof(tmp))
            Unit.add_poligon(get_polygon(tmp,clr));
        Unit.set_name(Name);
        Unit.init_centre();
        _Close_File(tmp);
    }
    catch(base_error& er)
    {
        _Close_File(tmp);
        qDebug()<<er.what() ;
        qDebug()<<Name;
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
    if(f)
        fclose(f);
}

Polygon file_loaderImpl::get_polygon(FILE *&f)
{
    QVector<Point3D> vec;
    for(size_t i=0; i!=3; ++i)
        vec.push_back(this->get_point(f));
    return Polygon(vec[0],vec[1],vec[2],this->get_color(f));
}

Polygon file_loaderImpl::get_polygon(FILE *&f, QColor clr)
{
    QVector<Point3D> vec;
    for(size_t i=0; i!=3; ++i)
        vec.push_back(this->get_point(f));
    return Polygon(vec[0],vec[1],vec[2],clr);
}

Point3D file_loaderImpl::get_point(FILE *&f)
{
    float x,y,z;
    if(feof(f))
        throw loader_error::file_error();
    if( fscanf(f,"%f %f %f",&x,&y,&z) != 3)
        throw loader_error::file_error();
    qDebug()<<x<<y<<z;
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


bool file_loaderImpl_Qbjfile::Load(base_model &Unit, const char *Name)
{
    try
    {
        this->_Open_File(Name);
        this->_Read_Data(Unit);
        Unit.set_name(Name);
        Unit.init_centre();
        this->_Close_File();
    }
    catch(base_error&)
    {
        this->_Close_File();
        return false;
    }
    return true;
}

bool file_loaderImpl_Qbjfile::Load(base_model &Unit, const char *Name, QColor clr)
{
    try
    {
        this->_Open_File(Name);
        this->_Read_Data(Unit);
        Unit.set_name(Name);
        Unit.init_centre();
        Unit.set_color(clr);
        this->_Close_File();
    }
    catch(base_error&)
    {
        this->_Close_File();
        return false;
    }
    return true;
}

void file_loaderImpl_Qbjfile::_Read_Data(base_model &Unit)
{
    QVector<Point3D> pnts;
    for(QStringList::iterator it = this->file_data_list.begin();
            it != this->file_data_list.end(); ++it)
    {
        QTextStream tmp(&*it);
        tmp.seek(1);
        if((*it)[0] == 'v')
        {
            float x,y,z;
            tmp >> x >> y >> z;
            pnts.push_back(Point3D(x,y,z));
        }
        if((*it)[0] == 'f')
        {
            int x,y,z;
            tmp >> x >> y >> z;
            Unit.add_poligon(pnts[x-1],pnts[y-1],pnts[z-1]);
        }
    }
}

void file_loaderImpl_Qbjfile::_Open_File(const char *Name)
{
    this->file = new QFile(Name);
    if(!this->file->open(QFile::ReadOnly))
        throw loader_error::open_error();
    this->file_data_list = QString(this->file->readAll()).split("\n");
}

void file_loaderImpl_Qbjfile::_Close_File()
{
    delete this->file;
}
