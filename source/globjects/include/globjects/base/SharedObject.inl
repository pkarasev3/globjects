
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
std::shared_ptr<T> AbstractSharedObject::shared_this()
{
    return std::dynamic_pointer_cast<T>(shared_from_this());
}

template <typename T>
std::shared_ptr<const T> AbstractSharedObject::shared_this() const
{
    return std::dynamic_pointer_cast<const T>(shared_from_this());
}


} // namespace globjects
