
#pragma once


#include <memory>

#include <globjects/globjects_api.h>

#include <globjects/base/SharedObject.h>


namespace globjects
{


class AbstractChangeListener;


class GLOBJECTS_API AbstractChangeable : public SharedObject
{
public:
    AbstractChangeable();
    virtual ~AbstractChangeable();

    virtual void changed() const = 0;

    virtual void registerListener(std::weak_ptr<AbstractChangeListener> listener) = 0;
    virtual void deregisterListener(std::weak_ptr<AbstractChangeListener> listener) = 0;
};


} // namespace globjects
