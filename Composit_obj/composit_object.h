#ifndef COMPOSIT_OBJECT_H
#define COMPOSIT_OBJECT_H
#include "Base_obj/base_obj.h"
#include "cstdlib"
#include "cstdio"
#include <QVector>

class composit_object: private base_obj
{
public:
    composit_object(){}
    bool add(base_obj* b_obj) override
    {
        return (b_obj) ? (objects.push_back(b_obj), true) : (false);
    }
    bool del(size_t index)
    {
        return index<(unsigned int)objects.size() ? (objects.remove(index), true) : (false);
    }
    bool dell_all()
    {
        objects.clear();
        return true;
    }
    void execute(base_transform *transform)
    {
        #pragma omp parallel for
        for(QVector<base_obj*>::iterator it = objects.begin(); it < objects.end(); ++it)
            (*it)->execute(transform);
        #pragma omp barrier
    }
    base_obj* operator[](size_t i)
    {
        return objects[i];
    }
    QString type_object()
    {
        return "composit object";
    }

    QVector<base_obj*>::iterator begin()
    {
        return objects.begin();
    }
    QVector<base_obj*>::iterator end()
    {
        return objects.end();
    }
    //typedef QVector<base_obj*>::const_iterator const_iterator;
    typedef QVector<base_obj*>::iterator iterator;
    bool isEmpty()
    {
        return this->objects.isEmpty();
    }
    int size() const
    {
        return this->objects.size();
    }

private:
    QVector<base_obj*> objects;
};

#endif // COMPOSIT_OBJECT_H
