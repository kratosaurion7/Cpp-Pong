#pragma once

#include <list>

template <class T> class BaseList
{
public:
    BaseList()
    {
        _container = new std::list<T>();
    };

    ~BaseList()
    {
        delete(_container);
    };

    void BaseList::Add(T item)
    {
        _container->push_back(item);
    };

    T BaseList::Get(int index)
    {
        int i = 0;

        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {

            if (index == i)
            {
                return *it;
            }

            i++;
        }

        return NULL;
    };

    void BaseList::Remove(int index)
    {
        _container->erase(index);
    };

    int BaseList::Count()
    {
        return _container->size();
    };

    std::list<T>* GetContainer() // Temp function to give outsiders a possibility to iterate on the container
    {
        return _container;
    };


protected:
    std::list<T> *_container;
};

