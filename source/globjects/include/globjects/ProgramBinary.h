
#pragma once

#include <vector>
#include <memory>

#include <glbinding/gl/types.h>

#include <globjects/globjects_api.h>

#include <globjects/base/ChangeListener.h>
#include <globjects/base/Changeable.h>

namespace globjects
{


class AbstractStringSource;

/**
 * \brief The ProgramBinary class is used for directly setting binary sources for a Program.
 *
 * \see Program
 * \see http://www.opengl.org/registry/specs/ARB/get_program_binary.txt
 */
class GLOBJECTS_API ProgramBinary : public Changeable<ChangeListener<SharedObject>>
{
    using Super = Changeable<ChangeListener<SharedObject>>;
public:
    ProgramBinary(gl::GLenum binaryFormat, const std::vector<char> & binaryData);
    ProgramBinary(gl::GLenum binaryFormat, std::shared_ptr<AbstractStringSource> dataSource);

    gl::GLenum format() const;
    const void * data() const;
    gl::GLsizei length() const;

    virtual void notifyChanged(const AbstractChangeable* sender) override;

protected:
    virtual ~ProgramBinary();

    void validate() const;
    virtual void onInitialize() override;

protected:
    gl::GLenum m_binaryFormat;
    std::shared_ptr<AbstractStringSource> m_dataSource;

    mutable bool m_valid;
    mutable std::vector<unsigned char> m_binaryData;
};


} // namespace globjects
