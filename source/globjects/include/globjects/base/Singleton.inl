
#pragma once


#include <cassert>


namespace globjects 
{


template<class T>
std::unique_ptr<T> Singleton<T>::s_instance(nullptr);

template<class T>
T * Singleton<T>::instance()
{
    if (!s_instance)
    {
        s_instance.reset(new T());
    }

    return s_instance.get();
}

template<class T>
Singleton<T>::Singleton()
{
    assert(!s_instance);
}

template<class T>
Singleton<T>::~Singleton()
{
}


} // namespace globjects
