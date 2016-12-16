
#include "ObjectRegistry.h"

#include <cassert>

#include <globjects/Object.h>
#include <globjects/Framebuffer.h>
#include <globjects/VertexArray.h>

#include "Registry.h"


namespace globjects 
{


ObjectRegistry::ObjectRegistry()
: m_defaultFBO(nullptr)
, m_defaultVAO(nullptr)
{
}

ObjectRegistry & ObjectRegistry::current()
{
    return Registry::current().objects();
}

std::set<Object*> ObjectRegistry::objects() const
{
    return m_objects;
}

std::set<Object *>::iterator ObjectRegistry::begin()
{
    return m_objects.begin();
}

std::set<Object *>::iterator ObjectRegistry::end()
{
    return m_objects.end();
}

void ObjectRegistry::registerObject(Object * object)
{
    assert(object != nullptr);

	if (object->id() == 0)
        return;

    m_objects.insert(object);
}

void ObjectRegistry::deregisterObject(Object * object)
{
    assert(object != nullptr);

    if (object->id() == 0)
        return;

    m_objects.erase(object);
}

std::shared_ptr<Framebuffer> ObjectRegistry::defaultFBO()
{
    if (m_defaultFBO == nullptr)
    {
        m_defaultFBO = Framebuffer::fromId(0);
    }

    return m_defaultFBO;
}

std::shared_ptr<VertexArray> ObjectRegistry::defaultVAO()
{
    if (m_defaultVAO == nullptr)
    {
        m_defaultVAO = VertexArray::fromId(0);
    }

    return m_defaultVAO;
}


} // namespace globjects
