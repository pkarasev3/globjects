
#include <globjects/base/Changeable.h>

#include <cassert>

#include <globjects/base/ChangeListener.h>


namespace globjects
{


void Changeable::changed() const
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

void Changeable::registerListener(std::weak_ptr<ChangeListener> listener)
{
    const auto ptr = listener.lock();

    if (ptr)
    {
        m_listeners.insert(listener);
        ptr->addSubject(shared_from_this());
    }
}

void Changeable::deregisterListener(std::weak_ptr<ChangeListener> listener)
{
    if (m_listeners.find(listener) == m_listeners.end())
        return;

	m_listeners.erase(listener);

    const auto ptr = listener.lock();

    if (ptr)
    {
        ptr->removeSubject(shared_from_this());
    }
}


} // namespace globjects
