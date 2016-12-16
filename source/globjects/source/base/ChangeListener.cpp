
#include <globjects/base/ChangeListener.h>

#include <globjects/base/Changeable.h>


namespace globjects
{


ChangeListener::~ChangeListener()
{
    while (!m_subjects.empty())
    {
        const auto ptr = m_subjects.begin()->lock();
        // calls removeSubject
        if (ptr)
        {
            ptr->deregisterListener(shared_from_this());
        }
    }
}

void ChangeListener::notifyChanged(const Changeable *)
{
}

void ChangeListener::addSubject(std::weak_ptr<Changeable> subject)
{
    m_subjects.insert(subject);
}

void ChangeListener::removeSubject(std::weak_ptr<Changeable> subject)
{
    m_subjects.erase(subject);
}


} // namespace globjects
