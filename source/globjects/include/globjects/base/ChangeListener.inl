
#pragma once

#include <globjects/base/AbstractChangeable.h>


namespace globjects
{


template <typename Superclass>
template <typename... Args>
ChangeListener<Superclass>::ChangeListener(Args && ... args)
: Superclass(std::forward<Args>(args)...)
{

}

template <typename Superclass>
ChangeListener<Superclass>::~ChangeListener()
{
    while (!m_subjects.empty())
    {
        const auto ptr = m_subjects.begin()->lock();
        // calls removeSubject
        if (ptr)
        {
            ptr->deregisterListener(shared_this<AbstractChangeListener>());
        }
    }
}

template <typename Superclass>
void ChangeListener<Superclass>::notifyChanged(const AbstractChangeable *)
{
}

template <typename Superclass>
void ChangeListener<Superclass>::addSubject(std::weak_ptr<AbstractChangeable> subject)
{
    m_subjects.insert(subject);
}

template <typename Superclass>
void ChangeListener<Superclass>::removeSubject(std::weak_ptr<AbstractChangeable> subject)
{
    m_subjects.erase(subject);
}


} // namespace globjects
