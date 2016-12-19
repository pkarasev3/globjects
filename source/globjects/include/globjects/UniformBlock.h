
#pragma once

#include <vector>
#include <memory>

#include <globjects/globjects_api.h>
#include <globjects/LocationIdentity.h>
#include <globjects/base/SharedObject.h>


namespace globjects 
{


class Program;

class GLOBJECTS_API UniformBlock : public SharedObject
{
    friend class Program;
public:
    UniformBlock();
    UniformBlock(std::weak_ptr<const Program> program, const LocationIdentity & m_identity);

    const LocationIdentity & identity() const;

    void setBinding(gl::GLuint bindingIndex);

    void getActive(gl::GLenum pname, gl::GLint * params) const;
    gl::GLint getActive(gl::GLenum pname) const;
    std::vector<gl::GLint> getActive(gl::GLenum pname, gl::GLint paramCount) const;

    std::vector<gl::GLint> getActiveUniformIndices() const;

    std::string getName() const;

protected:
    std::weak_ptr<const Program> m_program;
    LocationIdentity m_identity;
    gl::GLuint m_bindingIndex;

    gl::GLuint blockIndex() const;
    void updateBinding() const;

    virtual void onInitialize() override;
};


} // namespace globjects
