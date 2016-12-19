
#pragma once


#include <memory>


namespace globjects
{


template <typename T, typename... Args>
std::shared_ptr<T> create_shared(Args && ... args);


} // namespace globjects


#include <globjects/base/make_shared.inl>
