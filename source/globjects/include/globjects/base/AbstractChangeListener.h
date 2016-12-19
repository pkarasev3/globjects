
#pragma once


#include <memory>

#include <globjects/globjects_api.h>


namespace globjects
{


class AbstractChangeable;


class GLOBJECTS_API AbstractChangeListener
{
public:
    virtual void notifyChanged(const AbstractChangeable * sender) = 0;

    virtual void addSubject(std::weak_ptr<AbstractChangeable> subject) = 0;
    virtual void removeSubject(std::weak_ptr<AbstractChangeable> subject) = 0;
};


} // namespace globjects
