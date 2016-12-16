
#include <globjects/AbstractUniform.h>

#include <cassert>

#include <globjects/Program.h>
#include <globjects/globjects.h>

#include "registry/ImplementationRegistry.h"

#include "implementations/AbstractUniformImplementation.h"

using namespace gl;


namespace 
{


const globjects::AbstractUniformImplementation & implementation()
{
    return globjects::ImplementationRegistry::current().uniformImplementation();
}

}

namespace globjects
{

void AbstractUniform::hintBindlessImplementation(BindlessImplementation impl)
{
    ImplementationRegistry::current().initialize(impl);
}


AbstractUniform::AbstractUniform(const GLint location)
: m_identity(location)
{
}

AbstractUniform::AbstractUniform(const std::string & name)
: m_identity(name)
{
}

AbstractUniform::~AbstractUniform()
{
}

const std::string & AbstractUniform::name() const
{
    return m_identity.name();
}

GLint AbstractUniform::location() const
{
    return m_identity.location();
}

const LocationIdentity & AbstractUniform::identity() const
{
    return m_identity;
}

void AbstractUniform::registerProgram(std::weak_ptr<Program> program)
{
    m_programs.insert(program);
}

void AbstractUniform::deregisterProgram(std::weak_ptr<Program> program)
{
    m_programs.erase(program);
}

void AbstractUniform::changed()
{
    for (const auto & program : m_programs)
    {
        const auto ptr = program.lock();

        if (ptr)
        {
            update(program, false);
        }
    }
}

GLint AbstractUniform::locationFor(std::weak_ptr<const Program> program) const
{
    if (m_identity.isLocation())
        return m_identity.location();

    auto it = m_locations.find(program);

    if (it != m_locations.end())
    {
        return it->second;
    }

    const auto ptr = program.lock();

    if (ptr)
    {
        gl::GLint location = ptr->getUniformLocation(m_identity.name());

        m_locations.emplace(program, location);

        return location;
    }

    return -1;
}

void AbstractUniform::update(std::weak_ptr<const Program> program, bool invalidateLocation) const
{
    if (invalidateLocation)
    {
        m_locations.erase(program);
    }

    const auto ptr = program.lock();

    if (ptr)
    {
        if (!ptr->isLinked())
        {
            return;
        }

        updateAt(program, locationFor(program));
    }
}

void AbstractUniform::setValue(const Program * program, const GLint location, const float & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const int & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const unsigned int & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const bool & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::vec2 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::vec3 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::vec4 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::ivec2 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::ivec3 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::ivec4 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::uvec2 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::uvec3 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::uvec4 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::mat2 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::mat3 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::mat4 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::mat2x3 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::mat3x2 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::mat2x4 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::mat4x2 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::mat3x4 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const glm::mat4x3 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const GLuint64 & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const TextureHandle & value) const
{
    setValue(program, location, value.handle());
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<float> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<int> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<unsigned int> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<bool> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::vec2> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::vec3> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::vec4> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::ivec2> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::ivec3> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::ivec4> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::uvec2> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::uvec3> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::uvec4> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::mat2> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::mat3> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::mat4> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::mat2x3> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::mat3x2> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::mat2x4> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::mat4x2> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::mat3x4> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<glm::mat4x3> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program* program, const GLint location, const std::vector<GLuint64> & value) const
{
    implementation().set(program, location, value);
}

void AbstractUniform::setValue(const Program * program, const GLint location, const std::vector<TextureHandle> & value) const
{
    implementation().set(program, location, value);
}


} // namespace globjects
