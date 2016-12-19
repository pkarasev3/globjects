
#pragma once


#include <type_traits>


namespace
{


template <typename U, typename T>
std::shared_ptr<U> reinterpret_pointer_cast(const std::shared_ptr<T> & ptr)
{
    return std::shared_ptr<U>(reinterpret_cast<U*>(ptr.get()));
}


} // namespace


namespace globjects
{


template <typename T>
std::shared_ptr<T> SharedObject::shared_from_this()
{
    return reinterpret_pointer_cast<T>(std::enable_shared_from_this<SharedObject>::shared_from_this());
}

template <typename T>
std::shared_ptr<const T> SharedObject::shared_from_this() const
{
    return reinterpret_pointer_cast<const T>(std::enable_shared_from_this<SharedObject>::shared_from_this());
}


} // namespace globjects
