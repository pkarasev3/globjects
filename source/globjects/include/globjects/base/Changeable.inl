
#pragma once

#include <cassert>

#include <globjects/base/AbstractChangeListener.h>


namespace globjects
{


template <typename Superclass>
template <typename... Args>
Changeable<Superclass>::Changeable(Args && ... args)
: Superclass(std::forward<Args>(args)...)
{
}

template <typename Superclass>
void Changeable<Superclass>::changed() const
{
    for (const auto & listener: m_listeners)
    {
        auto ptr = listener.lock();

        if (ptr)
        {
            ptr->notifyChanged(this);
        }
    }
}

template <typename Superclass>
void Changeable<Superclass>::registerListener(std::weak_ptr<AbstractChangeListener> listener)
{
    const auto ptr = listener.lock();

    if (ptr)
    {
        m_listeners.insert(listener);
        ptr->addSubject(this->template shared_from_this<AbstractChangeable>());
    }
}

template <typename Superclass>
void Changeable<Superclass>::deregisterListener(std::weak_ptr<AbstractChangeListener> listener)
{
    if (m_listeners.find(listener) == m_listeners.end())
        return;

	m_listeners.erase(listener);

    const auto ptr = listener.lock();

    if (ptr)
    {
        ptr->removeSubject(this->template shared_from_this<AbstractChangeable>());
    }
}


} // namespace globjects
