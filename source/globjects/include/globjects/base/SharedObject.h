
#pragma once


#include <memory>

#include <globjects/globjects_api.h>

#include <globjects/base/make_shared.h>


namespace globjects
{


class GLOBJECTS_API SharedObject : public virtual std::enable_shared_from_this<SharedObject>
{
    template <typename T, typename... Args>
    friend std::shared_ptr<T> create_shared(Args && ... args);
protected:
    SharedObject();
    virtual ~SharedObject();

    void initialize();

    template <typename T>
    std::shared_ptr<T> shared_from_this();

    template <typename T>
    std::shared_ptr<const T> shared_from_this() const;

protected:
    virtual void onInitialize() = 0;
};


} // namespace globjects


#include <globjects/base/SharedObject.inl>
