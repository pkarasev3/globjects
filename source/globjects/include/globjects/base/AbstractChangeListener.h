
#pragma once


#include <memory>

#include <globjects/globjects_api.h>

#include <globjects/base/SharedObject.h>


namespace globjects
{


class AbstractChangeable;


class GLOBJECTS_API AbstractChangeListener : public SharedObject
{
public:
    AbstractChangeListener();
    ~AbstractChangeListener();

    virtual void notifyChanged(const AbstractChangeable * sender) = 0;

    virtual void addSubject(std::weak_ptr<AbstractChangeable> subject) = 0;
    virtual void removeSubject(std::weak_ptr<AbstractChangeable> subject) = 0;
};


} // namespace globjects
