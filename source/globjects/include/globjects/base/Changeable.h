
#pragma once

#include <set>
#include <memory>

#include <globjects/globjects_api.h>

#include <globjects/base/SharedObject.h>
#include <globjects/base/AbstractChangeable.h>


namespace globjects
{


/** \brief Superclass of all objects that want others to signal that they have changed.
    
    It implements the observer pattern. Listeners to the subclass change can be
    registered using registerListener() and deregistered using deregisterListener().
    
    \see ChangeListener
 */
template <typename Superclass>
class Changeable : public AbstractChangeable, public Superclass
{
public:
    template <typename... Args>
    Changeable(Args && ... args);

    void changed() const;

    void registerListener(std::weak_ptr<AbstractChangeListener> listener);
    void deregisterListener(std::weak_ptr<AbstractChangeListener> listener);

private:
    std::set<std::weak_ptr<AbstractChangeListener>, std::owner_less<std::weak_ptr<AbstractChangeListener>>> m_listeners;
};


} // namespace globjects


#include <globjects/base/Changeable.inl>
