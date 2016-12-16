
#include <globjects/UniformBlock.h>

#include <globjects/Program.h>

#include <glbinding/gl/values.h>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>

using namespace gl;


namespace globjects 
{


UniformBlock::UniformBlock()
: m_bindingIndex(0)
{
}

UniformBlock::UniformBlock(std::weak_ptr<const Program> program, const LocationIdentity & identity)
: m_program(program)
, m_identity(identity)
, m_bindingIndex(0)
{
}

const LocationIdentity & UniformBlock::identity() const
{
    return m_identity;
}

void UniformBlock::setBinding(GLuint bindingIndex)
{
    m_bindingIndex = bindingIndex;

    updateBinding();
}

GLuint UniformBlock::blockIndex() const
{
    if (m_identity.isLocation())
        return m_identity.location();

    if (m_identity.isName())
    {
        const auto ptr = m_program.lock();

        if (ptr)
        {
            return ptr->getUniformBlockIndex(m_identity.name());
        }
    }

    return GL_INVALID_INDEX;
}

void UniformBlock::updateBinding() const
{
    const auto ptr = m_program.lock();

    if (ptr)
    {
        ptr->checkDirty();

        glUniformBlockBinding(ptr->id(), blockIndex(), m_bindingIndex);
    }

}
void UniformBlock::getActive(const GLenum pname, GLint * params) const
{
    const auto ptr = m_program.lock();

    if (ptr)
    {
        ptr->checkDirty();

        glGetActiveUniformBlockiv(ptr->id(), blockIndex(), pname, params);
    }
}

GLint UniformBlock::getActive(const GLenum pname) const
{
    GLint result = 0;
    getActive(pname, &result);
    return result;
}

std::vector<GLint> UniformBlock::getActive(const GLenum pname, const GLint paramCount) const
{
    std::vector<GLint> result(paramCount);
    getActive(pname, result.data());
    return result;
}

std::vector<GLint> UniformBlock::getActiveUniformIndices() const
{
    return getActive(GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, getActive(GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS));
}

std::string UniformBlock::getName() const
{
    if (m_identity.isName())
    {
        return m_identity.name();
    }

    const auto ptr = m_program.lock();

    if (ptr)
    {
        GLint length = getActive(GL_UNIFORM_BLOCK_NAME_LENGTH);
        std::vector<char> name(length);

        glGetActiveUniformBlockName(ptr->id(), blockIndex(), length, nullptr, name.data());

        return std::string(name.data(), length);
    }

    return std::string("");
}


} // namespace globjects
