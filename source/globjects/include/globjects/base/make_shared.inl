
#pragma once


namespace globjects
{


template <typename T, typename... Args>
std::shared_ptr<T> create_shared(Args && ... args)
{
    std::shared_ptr<T> object = std::make_shared<T>(std::forward<Args>(args)...);

    object->initialize();

    return std::move(object);
}


} // namespace globjects
