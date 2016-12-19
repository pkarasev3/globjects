
#include <globjects/base/StringSourceDecorator.h>

#include <cassert>


namespace globjects
{


StringSourceDecorator::StringSourceDecorator(std::shared_ptr<globjects::AbstractStringSource> source)
: m_internal(source)
{
    m_internal->registerListener(ChangeListener::shared_from_this<ChangeListener>());

    update();
}

StringSourceDecorator::~StringSourceDecorator()
{
    m_internal->deregisterListener(ChangeListener::shared_from_this<ChangeListener>());
}

void StringSourceDecorator::notifyChanged(const AbstractChangeable *)
{
    update();
    changed();
}

void StringSourceDecorator::update()
{
}


} // namespace globjects
