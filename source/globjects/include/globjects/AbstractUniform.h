
#pragma once

#include <string>
#include <set>
#include <vector>
#include <array>
#include <unordered_map>

#include <glm/fwd.hpp>

#include <globjects/globjects_api.h>

#include <globjects/LocationIdentity.h>


namespace globjects
{


class TextureHandle;
class Program;
template<typename T> class Uniform;
enum class UniformType : unsigned char;

/** \brief Abstract base class for templated Uniforms.
 *
 * Unifies the specialized Uniforms in order to be able to store them in a list or a vector.
 *
 * \see Uniform
 * \see Program
 */
class GLOBJECTS_API AbstractUniform
{
    friend class Program; ///< Programs (de)register themselves.

public:
    enum BindlessImplementation
    {
        SeparateShaderObjectsARB
    ,   Legacy
    };

    static void hintBindlessImplementation(const BindlessImplementation impl);

public:
    AbstractUniform(const Program * program, gl::GLint location, UniformType type);
    AbstractUniform(const Program * program, const std::string & name, UniformType type);
    virtual ~AbstractUniform();

    const std::string & name() const;
    gl::GLint location() const;

    const LocationIdentity & identity() const;

    UniformType type() const;

protected:
    /** Iterates over all programs attached to and calls update.
        Should be called on every value change (i.e., in Uniform).
    */
    void changed();

    /** Sets the uniform's value on the program.
    */
    void update(bool invalidateLocation) const;

    /** This function requires knowledge of the unifom's value.
    */
    virtual void updateAt(gl::GLint location) const = 0;

protected:
    void setValue(gl::GLint location, const float & value) const;
    void setValue(gl::GLint location, const int & value) const;
    void setValue(gl::GLint location, const unsigned int & value) const;
    void setValue(gl::GLint location, const bool & value) const;

    void setValue(gl::GLint location, const glm::vec2 & value) const;
    void setValue(gl::GLint location, const glm::vec3 & value) const;
    void setValue(gl::GLint location, const glm::vec4 & value) const;

    void setValue(gl::GLint location, const glm::ivec2 & value) const;
    void setValue(gl::GLint location, const glm::ivec3 & value) const;
    void setValue(gl::GLint location, const glm::ivec4 & value) const;

    void setValue(gl::GLint location, const glm::uvec2 & value) const;
    void setValue(gl::GLint location, const glm::uvec3 & value) const;
    void setValue(gl::GLint location, const glm::uvec4 & value) const;

    void setValue(gl::GLint location, const glm::mat2 & value) const;
    void setValue(gl::GLint location, const glm::mat3 & value) const;
    void setValue(gl::GLint location, const glm::mat4 & value) const;

    void setValue(gl::GLint location, const glm::mat2x3 & value) const;
    void setValue(gl::GLint location, const glm::mat3x2 & value) const;
    void setValue(gl::GLint location, const glm::mat2x4 & value) const;
    void setValue(gl::GLint location, const glm::mat4x2 & value) const;
    void setValue(gl::GLint location, const glm::mat3x4 & value) const;
    void setValue(gl::GLint location, const glm::mat4x3 & value) const;

    void setValue(gl::GLint location, const gl::GLuint64 & value) const;
    void setValue(gl::GLint location, const TextureHandle & value) const;

    void setValue(gl::GLint location, const std::vector<float> & value) const;
    void setValue(gl::GLint location, const std::vector<int> & value) const;
    void setValue(gl::GLint location, const std::vector<unsigned int> & value) const;
    void setValue(gl::GLint location, const std::vector<bool> & value) const;

    void setValue(gl::GLint location, const std::vector<glm::vec2> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::vec3> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::vec4> & value) const;

    void setValue(gl::GLint location, const std::vector<glm::ivec2> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::ivec3> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::ivec4> & value) const;

    void setValue(gl::GLint location, const std::vector<glm::uvec2> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::uvec3> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::uvec4> & value) const;

    void setValue(gl::GLint location, const std::vector<glm::mat2> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::mat3> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::mat4> & value) const;

    void setValue(gl::GLint location, const std::vector<glm::mat2x3> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::mat3x2> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::mat2x4> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::mat4x2> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::mat3x4> & value) const;
    void setValue(gl::GLint location, const std::vector<glm::mat4x3> & value) const;

    void setValue(gl::GLint location, const std::vector<gl::GLuint64> & value) const;
    void setValue(gl::GLint location, const std::vector<TextureHandle> & value) const;

    template <typename T, std::size_t Count>
    void setValue(gl::GLint location, const std::array<T, Count> & value) const;

protected:
    LocationIdentity m_identity;
    const Program * m_program;
    const UniformType m_type;
    mutable gl::GLint m_location;
};


} // namespace globjects


#include <globjects/AbstractUniform.inl>
