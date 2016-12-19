
#pragma once


#include <memory>

#include <globjects/globjects_api.h>


namespace globjects
{


class AbstractChangeListener;


class GLOBJECTS_API AbstractChangeable
{
public:
    virtual void changed() const = 0;

    virtual void registerListener(std::weak_ptr<AbstractChangeListener> listener) = 0;
    virtual void deregisterListener(std::weak_ptr<AbstractChangeListener> listener) = 0;
};


} // namespace globjects
