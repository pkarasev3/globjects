
#pragma once

#include <set>
#include <memory>

#include <globjects/globjects_api.h>


namespace globjects
{


class Changeable;

/** \brief Allows listening to any Changeable.
    
    If a Changeable this ChangeListener is registered on signals a change, the 
    notifyChanged() method is called. This class implements the observer pattern.
    
    \see Changeable
 */
class GLOBJECTS_API ChangeListener : public std::enable_shared_from_this<ChangeListener>
{
    friend class Changeable;
public:
    virtual ~ChangeListener();

    virtual void notifyChanged(const Changeable * sender);

private:
    std::set<std::weak_ptr<Changeable>, std::owner_less<std::weak_ptr<Changeable>>> m_subjects;

    void addSubject(std::weak_ptr<Changeable> subject);
    void removeSubject(std::weak_ptr<Changeable> subject);
};


} // namespace globjects
