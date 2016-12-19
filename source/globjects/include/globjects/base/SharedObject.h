
#pragma once


#include <memory>

#include <globjects/globjects_api.h>

#include <globjects/base/make_shared.h>


namespace globjects
{


class GLOBJECTS_API AbstractSharedObject : public std::enable_shared_from_this<AbstractSharedObject>
{
public:
    AbstractSharedObject();
    ~AbstractSharedObject();

    template <typename T>
    std::shared_ptr<T> shared_this();

    template <typename T>
    std::shared_ptr<const T> shared_this() const;

    void initialize();
protected:
    virtual void onInitialize();
};


class GLOBJECTS_API SharedObject : public virtual AbstractSharedObject
{
    template <typename T, typename... Args>
    friend std::shared_ptr<T> create_shared(Args && ... args);
protected:
    SharedObject();
    virtual ~SharedObject();
};


} // namespace globjects


#include <globjects/base/SharedObject.inl>
