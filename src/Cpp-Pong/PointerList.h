#pragma once

#include "BaseList.h"

template <class T> class PointerList : public BaseList<T>
{
public:
    PointerList()
    {

    };

    ~PointerList()
    {
        delete(_container);
    };

    void PointerList::Release()
    {
        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            delete(*it);
        }

        _container->clear();
    };
};

