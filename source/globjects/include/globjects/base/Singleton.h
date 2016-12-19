
#pragma once


#include <memory>


namespace globjects
{


template<class T>
class Singleton
{
public:
    static T * instance();

protected:
    explicit Singleton();
    virtual ~Singleton();

protected:
    static std::unique_ptr<T> s_instance;
};


} // namespace globjects


#include <globjects/base/Singleton.inl>
