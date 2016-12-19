
#pragma once

#include <set>
#include <memory>

#include <globjects/globjects_api.h>

#include <globjects/base/AbstractChangeListener.h>
#include <globjects/base/SharedObject.h>


namespace globjects
{


/** \brief Allows listening to any Changeable.
    
    If a Changeable this ChangeListener is registered on signals a change, the 
    notifyChanged() method is called. This class implements the observer pattern.
    
    \see Changeable
 */
template <typename Superclass>
class ChangeListener : public AbstractChangeListener, public Superclass
{
public:
    template <typename... Args>
    ChangeListener(Args && ... args);

    virtual ~ChangeListener();

    virtual void notifyChanged(const AbstractChangeable * sender);

private:
    std::set<std::weak_ptr<AbstractChangeable>, std::owner_less<std::weak_ptr<AbstractChangeable>>> m_subjects;

    void addSubject(std::weak_ptr<AbstractChangeable> subject);
    void removeSubject(std::weak_ptr<AbstractChangeable> subject);
};


} // namespace globjects


#include <globjects/base/ChangeListener.inl>
