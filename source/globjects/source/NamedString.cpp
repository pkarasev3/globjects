
#include <globjects/NamedString.h>

#include <glbinding/gl/functions.h>
#include <glbinding/gl/boolean.h>
#include <glbinding/gl/enum.h>

#include <globjects/base/AbstractStringSource.h>
#include <globjects/base/StaticStringSource.h>

#include "registry/NamedStringRegistry.h"

using namespace gl;


namespace globjects 
{


std::shared_ptr<NamedString> NamedString::create(const std::string & name, std::shared_ptr<AbstractStringSource> source)
{
    return create(name, source, GL_SHADER_INCLUDE_ARB);
}

std::shared_ptr<NamedString> NamedString::create(const std::string & name, const std::string & string)
{
    return create(name, string, GL_SHADER_INCLUDE_ARB);
}

std::shared_ptr<NamedString> NamedString::create(const std::string & name, std::shared_ptr<AbstractStringSource> source, const GLenum type)
{
    if (isNamedString(name))
    {
        return std::shared_ptr<NamedString>(nullptr);
    }

    return std::shared_ptr<NamedString>(new NamedString(name, source, type));
}

std::shared_ptr<NamedString> NamedString::create(const std::string & name, const std::string & string, const GLenum type)
{
    if (isNamedString(name))
    {
        return std::shared_ptr<NamedString>(nullptr);
    }

    return std::shared_ptr<NamedString>(new NamedString(name, std::shared_ptr<AbstractStringSource>(new StaticStringSource(string)), type));
}

NamedString::NamedString(const std::string & name, std::shared_ptr<AbstractStringSource> source, const GLenum type)
: m_name(name)
, m_source(source)
, m_type(type)
{
    createNamedString();
    registerNamedString();

    m_source->registerListener(ChangeListener::shared_from_this());
}

NamedString::~NamedString()
{
    m_source->deregisterListener(ChangeListener::shared_from_this());

    deregisterNamedString();
    deleteNamedString();
}

void NamedString::createNamedString()
{
    if (!hasNativeSupport())
        return;

    std::string str = string();

    glNamedStringARB(m_type, static_cast<GLint>(m_name.size()), m_name.c_str(), static_cast<GLint>(str.size()), str.c_str());
}

void NamedString::deleteNamedString()
{
    if (!hasNativeSupport())
        return;

    glDeleteNamedStringARB(static_cast<GLint>(m_name.size()), m_name.c_str());
}

void NamedString::registerNamedString()
{
    NamedStringRegistry::current().registerNamedString(std::enable_shared_from_this<NamedString>::shared_from_this());
}

void NamedString::deregisterNamedString()
{
    NamedStringRegistry::current().deregisterNamedString(std::enable_shared_from_this<NamedString>::shared_from_this());
}

bool NamedString::isNamedString(const std::string & name)
{
    if (NamedStringRegistry::current().hasNamedString(name))
    {
        return true;
    }

    if (hasNativeSupport())
    {
        return glIsNamedStringARB(static_cast<GLint>(name.size()), name.c_str()) == GL_TRUE;
    }

    return false;
}

GLint NamedString::getParameter(const GLenum pname) const
{
    if (hasNativeSupport())
    {
        GLint result = 0;

        glGetNamedStringivARB(static_cast<GLint>(m_name.size()), m_name.c_str(), pname, &result);

        return result;
    }

    switch (pname)
    {
        case GL_NAMED_STRING_LENGTH_ARB:
            return static_cast<GLint>(string().size());
        case GL_NAMED_STRING_TYPE_ARB:
            return static_cast<GLint>(m_type);
        default:
            return -1;
    }
}

std::shared_ptr<NamedString> NamedString::obtain(const std::string & name)
{
    auto namedString = NamedStringRegistry::current().namedString(name);
    const auto ptr = namedString.lock();

    if (!ptr && hasNativeSupport() && isNamedString(name))
    {
        GLint type;
        GLint length;

        glGetNamedStringivARB(static_cast<GLint>(name.size()), name.c_str(), GL_NAMED_STRING_TYPE_ARB, &type);
        glGetNamedStringivARB(static_cast<GLint>(name.size()), name.c_str(), GL_NAMED_STRING_LENGTH_ARB, &length);

        std::vector<char> string(length);

        glGetNamedStringARB(static_cast<GLint>(name.size()), name.c_str(), length, nullptr, string.data());

        namedString = create(name, std::string(string.data(), string.size()), static_cast<GLenum>(type));
    }

    return ptr;
}

const std::string & NamedString::name() const
{
    return m_name;
}

std::string NamedString::string() const
{
    return m_source->string();
}

GLenum NamedString::type() const
{
    return m_type;
}

std::shared_ptr<AbstractStringSource> NamedString::stringSource() const
{
    return m_source;
}

bool NamedString::hasNativeSupport()
{
    return NamedStringRegistry::current().hasNativeSupport();
}

void NamedString::updateString()
{
    createNamedString();
}

void NamedString::notifyChanged(const Changeable *)
{
    updateString();
}


} // namespace globjects
