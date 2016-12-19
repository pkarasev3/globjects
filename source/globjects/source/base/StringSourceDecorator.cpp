
#include <globjects/base/StringSourceDecorator.h>

#include <cassert>


namespace globjects
{


StringSourceDecorator::StringSourceDecorator(std::shared_ptr<globjects::AbstractStringSource> source)
: m_internal(source)
{
}

StringSourceDecorator::~StringSourceDecorator()
{
    m_internal->deregisterListener(shared_this<ChangeListener>());
}

void StringSourceDecorator::onInitialize()
{
    Super::onInitialize();

    m_internal->registerListener(shared_this<ChangeListener>());

    update();
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
