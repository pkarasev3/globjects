
#pragma once

#include <set>
#include <memory>

#include <globjects/globjects_api.h>


namespace globjects
{


class ChangeListener;

/** \brief Superclass of all objects that want others to signal that they have changed.
    
    It implements the observer pattern. Listeners to the subclass change can be
    registered using registerListener() and deregistered using deregisterListener().
    
    \see ChangeListener
 */
class GLOBJECTS_API Changeable : public std::enable_shared_from_this<Changeable>
{
public:
    void changed() const;

    void registerListener(std::weak_ptr<ChangeListener> listener);
    void deregisterListener(std::weak_ptr<ChangeListener> listener);

private:
    std::set<std::weak_ptr<ChangeListener>, std::owner_less<std::weak_ptr<ChangeListener>>> m_listeners;
};


} // namespace globjects
