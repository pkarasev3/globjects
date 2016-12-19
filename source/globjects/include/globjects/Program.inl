
#pragma once


#include <cassert>

#include <globjects/base/baselogging.h>

#include <globjects/Uniform.h>


namespace globjects
{


template<typename T>
void Program::setUniformByIdentity(const LocationIdentity & identity, const T & value)
{
    Uniform<T> * uniform = getUniformByIdentity<T>(identity);
    if (!uniform)
    {
        warning() << "Uniform type mismatch on set uniform. Uniform will be replaced.";

        addUniform(identity.isName() ? create_shared<Uniform<T>>(identity.name(), value) : create_shared<Uniform<T>>(identity.location(), value));
        return;
    }
    uniform->set(value);
}

template<typename T>
Uniform<T> * Program::getUniformByIdentity(const LocationIdentity & identity)
{
    const auto it = m_uniforms.find(identity);
    if (it != m_uniforms.end())
        return it->second->as<T>();

    // create new uniform if none named <name> exists

    auto uniform = identity.isName() ? create_shared<Uniform<T>>(identity.name()) : create_shared<Uniform<T>>(identity.location());

    addUniform(uniform);

    return uniform.get();
}

template<typename T>
const Uniform<T> * Program::getUniformByIdentity(const LocationIdentity & identity) const
{
    const auto it = m_uniforms.find(identity);
    if (it != m_uniforms.end())
        return it->second->as<T>();

    // create new uniform if none named <name> exists

    auto uniform = identity.isName() ? create_shared<Uniform<T>>(identity.name()) : create_shared<Uniform<T>>(identity.location());

    const_cast<Program*>(this)->addUniform(uniform);

    return uniform;
}


template<typename T>
void Program::setUniform(const std::string & name, const T & value)
{
    setUniformByIdentity(name, value);
}

template<typename T>
void Program::setUniform(gl::GLint location, const T & value)
{
    setUniformByIdentity(location, value);
}

template<typename T>
Uniform<T> * Program::getUniform(const std::string & name)
{
    return getUniformByIdentity<T>(name);
}

template<typename T>
const Uniform<T> * Program::getUniform(const std::string & name) const
{
    return getUniformByIdentity<T>(name);
}

template<typename T>
Uniform<T> * Program::getUniform(gl::GLint location)
{
    return getUniformByIdentity<T>(location);
}

template<typename T>
const Uniform<T> * Program::getUniform(gl::GLint location) const
{
    return getUniformByIdentity<T>(location);
}

template <class ...Shaders>
void Program::attach(std::shared_ptr<Shader> shader, Shaders... shaders)
{
    attach(shader);

    attach(std::forward<Shaders>(shaders)...);
}


} // namespace globjects
