#ifndef LOADER_H
#define LOADER_H
#include "base_loader.h"
#include "loader_error.h"
#include <iostream>
#include <QFile>
#include "Model/polygon.h"
class file_loaderImpl : public base_loaderImpl
{
public:
    bool Load(base_model &Unit, const char *Name);
    bool Load(base_model &Unit, const char *Name, QColor clr);
private:
    void _Open_File(FILE*& FileLoader, const char *Name);
    void _Close_File(FILE*& f);
    Polygon get_polygon(FILE*& f);
    Polygon get_polygon(FILE*& f, QColor clr);
    Point3D get_point(FILE*& f);
    QColor get_color(FILE*& f);  
};

class file_loaderImpl_Qbjfile : public base_loaderImpl
{
public:
    bool Load(base_model &Unit, QString Name);
    bool Load(base_model &Unit, QString Name, QColor clr);
private:
    QStringList file_data_list;
    QFile* file;
    void _Read_Data(base_model &Unit);
    void _Open_File(QString Name);
    void _Close_File(void);
};


class file_loader : public base_loader
{
public:
    //file_loader() : base_loader(new file_loaderImpl){}
    file_loader() : base_loader(new file_loaderImpl_Qbjfile){}
    bool Load(base_model &Unit, QString Name)
    {
        return this->ldImpl->Load(Unit,Name);
    }
    bool Load(base_model &Unit, QString Name, QColor clr)
    {
        return this->ldImpl->Load(Unit,Name,clr);
    }
};

#endif // LOADER_H
