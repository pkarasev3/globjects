
#pragma once

#include <glbinding/gl/types.h>

#include <globjects/globjects_api.h>
#include <globjects/AbstractUniform.h>


namespace globjects
{


/** \brief Wraps access to typed global GLSL variables.
 *
 * The Uniform class wraps access to typed global GLSL variables (uniforms).
 * These are stored in the OpenGL program objects itself.
 *
 * Supported OpenGL uniform setters are wrapped via specialized template set
 * implementations. Note that unsupported uniform types result in compile time
 * errors due to the default implementation of set.
 *
 * Simple usage of an Uniform:
 * \code{.cpp}
 * auto u = create_shared<Uniform<float>>("u_ratio");
 * u->set(1.618f);
 *
 * program->addUniform(u);
 * \endcode
 *
 * \see AbstractUniform
 * \see Program
 * \see http://www.opengl.org/wiki/Uniform
 */
template<typename T>
class Uniform : public AbstractUniform
{
public:
    Uniform(gl::GLint location);
    Uniform(gl::GLint location, const T & value);
    Uniform(const std::string & name);
    Uniform(const std::string & name, const T & value);
    virtual ~Uniform();

    void set(const T & value);

    const T & value() const;

protected:
    virtual void updateAt(std::weak_ptr<const Program> program, gl::GLint location) const override;
    virtual void onInitialize() override;

protected:
    T m_value; ///< The uniforms value, explictly required when relinking programs.
};


} // namespace globjects


#include <globjects/Uniform.inl>
