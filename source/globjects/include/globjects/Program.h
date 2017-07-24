
#pragma once

#include <set>
#include <unordered_map>
#include <vector>
#include <memory>

#include <glm/fwd.hpp>

#include <globjects/base/ChangeListener.h>
#include <globjects/base/Changeable.h>

#include <globjects/globjects_api.h>

#include <globjects/Object.h>
#include <globjects/LocationIdentity.h>
#include <globjects/UniformBlock.h>
#include <globjects/base/Instantiator.h>


namespace globjects
{


class AbstractUniform;
class ProgramBinary;
class Shader;

template <typename T>
class Uniform;

/** \brief Wraps an OpenGL program.
    
    Therefor it suclasses Object. Programs get attached a set of shaders with 
    attach(). It inherits ChangeListener to react to changes to attached 
    shaders. To use a program for rendering, call use(). During use() the 
    program ensure that all attached shaders are compiled and linked. After 
    that, the program is registered in OpenGL to be used during the upcoming 
    rendering pileline calls.

    Shaders can be detached using detach() and queried with shaders().

    To use a program as a compute program, dispatchCompute() can be used to 
    start the kernel.

    Example code for setting up a program and use it for rendering
    
    [TODO]: Adjust examples
    \code{.cpp}

        Program * program = new Program();
        program->attach(
            Shader::fromString(gl::GL_VERTEX_SHADER, "...")
          , Shader::fromString(gl::GL_FRAGMENT_SHADER, "...")
          , ...);
        program->use();
    
        // draw calls
    
        program->release();

    \endcode
    
    Example code for using a program as compute program
    [TODO]: Adjust examples
    \code{.cpp}

        Program * program = new Program();
        program->attach(Shader::fromString(gl::GL_COMPUTE_SHADER, "..."));
    
        program->dispatchCompute(128, 1, 1);
    
        program->release();

        \endcode
    
    \see http://www.opengl.org/wiki/Program_Object
    \see Shader
 */
class GLOBJECTS_API Program : public Object, protected ChangeListener, public Changeable, public Instantiator<Program>
{
    friend class UniformBlock;
    friend class ProgramBinaryImplementation_GetProgramBinaryARB;
    friend class ProgramBinaryImplementation_None;

public:
    enum class BinaryImplementation
    {
        GetProgramBinaryARB
    ,   None
    };

    static void hintBinaryImplementation(BinaryImplementation impl);

public:
    Program();
    Program(std::unique_ptr<ProgramBinary> && binary);

    virtual ~Program();

    virtual void accept(ObjectVisitor & visitor) override;

    void use() const;
    static void release();

    bool isUsed() const;
    bool isLinked() const;

    void attach(Shader * shader);
    template <class ...Shaders> 
    void attach(Shader * shader, Shaders... shaders);

    void detach(Shader * shader);

    const std::set<Shader*> & shaders() const;

    void link() const;
    void invalidate() const;

    void setBinary(std::unique_ptr<ProgramBinary> && binary);
    ProgramBinary * binary() const;

    static std::unique_ptr<ProgramBinary> obtainBinary(Program * program);

    std::string infoLog() const;
    gl::GLint get(gl::GLenum pname) const;

    bool isValid() const;
    void validate();

    void setParameter(gl::GLenum pname, gl::GLint value) const;
    void setParameter(gl::GLenum pname, gl::GLboolean value) const;

    void getActiveAttrib(gl::GLuint index, gl::GLsizei bufSize, gl::GLsizei * length, gl::GLint * size, gl::GLenum * type, gl::GLchar * name) const;

    gl::GLint getAttributeLocation(const std::string & name) const;
    gl::GLint getUniformLocation(const std::string & name) const;

    std::vector<gl::GLint> getAttributeLocations(const std::vector<std::string> & names) const;
    std::vector<gl::GLint> getUniformLocations(const std::vector<std::string> & names) const;

    void bindAttributeLocation(gl::GLuint index, const std::string & name) const;
    void bindFragDataLocation(gl::GLuint index, const std::string & name) const;

    gl::GLint getFragDataLocation(const std::string & name) const;
    gl::GLint getFragDataIndex(const std::string & name) const;

    void getInterface(gl::GLenum programInterface, gl::GLenum pname, gl::GLint * params) const;
    gl::GLuint getResourceIndex(gl::GLenum programInterface, const std::string & name) const;
    void getResourceName(gl::GLenum programInterface, gl::GLuint index, gl::GLsizei bufSize, gl::GLsizei * length, char * name) const;
    void getResource(gl::GLenum programInterface, gl::GLuint index, gl::GLsizei propCount, const gl::GLenum * props, gl::GLsizei bufSize, gl::GLsizei * length, gl::GLint * params) const;
    gl::GLint getResourceLocation(gl::GLenum programInterface, const std::string & name) const;
    gl::GLint getResourceLocationIndex(gl::GLenum programInterface, const std::string & name) const;

    /** Convenience methods for getInterface()
    */
    gl::GLint getInterface(gl::GLenum programInterface, gl::GLenum pname) const;


    /** Convenience methods for getResource()
    */
    gl::GLint getResource(gl::GLenum programInterface, gl::GLuint index, gl::GLenum prop, gl::GLsizei * length = nullptr) const;
    std::vector<gl::GLint> getResource(gl::GLenum programInterface, gl::GLuint index, const std::vector<gl::GLenum> & props, gl::GLsizei * length = nullptr) const;
    void getResource(gl::GLenum programInterface, gl::GLuint index, const std::vector<gl::GLenum> & props, gl::GLsizei bufSize, gl::GLsizei * length, gl::GLint * params) const;

    gl::GLuint getUniformBlockIndex(const std::string& name) const;
    UniformBlock * uniformBlock(gl::GLuint uniformBlockIndex);
    const UniformBlock * uniformBlock(gl::GLuint uniformBlockIndex) const;
    UniformBlock * uniformBlock(const std::string& name);
    const UniformBlock * uniformBlock(const std::string& name) const;
    void getActiveUniforms(gl::GLsizei uniformCount, const gl::GLuint * uniformIndices, gl::GLenum pname, gl::GLint * params) const;
    std::vector<gl::GLint> getActiveUniforms(const std::vector<gl::GLuint> & uniformIndices, gl::GLenum pname) const;
    std::vector<gl::GLint> getActiveUniforms(const std::vector<gl::GLint> & uniformIndices, gl::GLenum pname) const;
    gl::GLint getActiveUniform(gl::GLuint uniformIndex, gl::GLenum pname) const;
    std::string getActiveUniformName(gl::GLuint uniformIndex) const;

    template<typename T>
    void setUniform(const std::string & name, const T & value);
    template<typename T>
    void setUniform(gl::GLint location, const T & value);

    /** Retrieves the existing or creates a new typed uniform, named <name>.
    */
    template<typename T>
    Uniform<T> * getUniform(const std::string & name);
    template<typename T>
    const Uniform<T> * getUniform(const std::string & name) const;
    template<typename T>
    Uniform<T> * getUniform(gl::GLint location);
    template<typename T>
    const Uniform<T> * getUniform(gl::GLint location) const;

    void setShaderStorageBlockBinding(gl::GLuint storageBlockIndex, gl::GLuint storageBlockBinding) const;

    void dispatchCompute(gl::GLuint numGroupsX, gl::GLuint numGroupsY, gl::GLuint numGroupsZ);
    void dispatchCompute(const glm::uvec3 & numGroups);
    void dispatchComputeGroupSize(gl::GLuint numGroupsX, gl::GLuint numGroupsY, gl::GLuint numGroupsZ, gl::GLuint groupSizeX, gl::GLuint groupSizeY, gl::GLuint groupSizeZ);
    void dispatchComputeGroupSize(const glm::uvec3 & numGroups, const glm::uvec3 & groupSizes);

    virtual gl::GLenum objectType() const override;

protected:
    bool checkLinkStatus() const;
    void checkDirty() const;

    bool compileAttachedShaders() const;
    void updateUniforms() const;
    void updateUniformBlockBindings() const;

    void addUniform(std::unique_ptr<AbstractUniform> && uniform);

    // ChangeListener Interface

    virtual void notifyChanged(const Changeable * sender) override;

protected:
    static gl::GLuint createProgram();

    template<typename T>
    void setUniformByIdentity(const LocationIdentity & identity, const T & value);
    template<typename T>
    Uniform<T> * getUniformByIdentity(const LocationIdentity & identity);
    template<typename T>
    const Uniform<T> * getUniformByIdentity(const LocationIdentity & identity) const;

    UniformBlock * getUniformBlockByIdentity(const LocationIdentity & identity);
    const UniformBlock * getUniformBlockByIdentity(const LocationIdentity & identity) const;

protected:
    std::set<Shader *> m_shaders;
    std::unique_ptr<ProgramBinary> m_binary;

    std::unordered_map<LocationIdentity, std::unique_ptr<AbstractUniform>> m_uniforms;
    std::unordered_map<LocationIdentity, UniformBlock> m_uniformBlocks;

    mutable bool m_linked;
    mutable bool m_dirty;
};


} // namespace globjects


#include <globjects/Program.inl>
