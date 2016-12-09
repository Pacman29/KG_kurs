#ifndef BASE_LOADER
#define BASE_LOADER
#include "Model/base_model.h"
class base_loaderImpl;

class base_loader
{
public:
    base_loader(base_loaderImpl* ld) : ldImpl(ld){}
    virtual ~base_loader()
    {
        delete ldImpl;
    }
    virtual bool Load(base_model &Unit, QString Name) = 0;
    virtual bool Load(base_model &Unit, QString Name, QColor clr) = 0;
protected:
    base_loaderImpl* ldImpl;
};

class base_loaderImpl
{
public:
    virtual ~base_loaderImpl(){}
    virtual bool Load(base_model &Unit, QString Name) = 0;
    virtual bool Load(base_model &Unit, QString Name, QColor clr) = 0;
};

#endif // BASE_LOADER

