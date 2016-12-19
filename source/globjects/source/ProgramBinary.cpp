
#include <globjects/ProgramBinary.h>

#include <globjects/base/StaticStringSource.h>
#include <globjects/base/AbstractStringSource.h>

using namespace gl;


namespace globjects
{


ProgramBinary::ProgramBinary(const GLenum binaryFormat, const std::vector<char> & binaryData)
: ProgramBinary(binaryFormat, create_shared<StaticStringSource>(binaryData.data(), binaryData.size()))
{
}

ProgramBinary::ProgramBinary(const GLenum binaryFormat, std::shared_ptr<AbstractStringSource> dataSource)
: m_binaryFormat(binaryFormat)
, m_dataSource(dataSource)
, m_valid(false)
{
}

ProgramBinary::~ProgramBinary()
{
    if (m_dataSource)
    {
        m_dataSource->deregisterListener(shared_from_this<ChangeListener>());
    }
}

void ProgramBinary::onInitialize()
{
    if (m_dataSource)
    {
        m_dataSource->registerListener(shared_from_this<ChangeListener>());
    }
}

GLenum ProgramBinary::format() const
{
    return m_binaryFormat;
}

const void * ProgramBinary::data() const
{
    validate();

    return reinterpret_cast<const void*>(m_binaryData.data());
}

GLsizei ProgramBinary::length() const
{
    validate();

    return static_cast<GLsizei>(m_binaryData.size());
}

void ProgramBinary::notifyChanged(const AbstractChangeable *)
{
    m_valid = false;
    changed();
}

void ProgramBinary::validate() const
{
    if (m_valid)
        return;

    if (!m_dataSource)
        return;

    std::string stringData = m_dataSource->string();
    size_t length = stringData.size();
    const unsigned char* data = reinterpret_cast<const unsigned char*>(stringData.c_str());

    m_binaryData = std::vector<unsigned char>(data, data+length);

    m_valid = true;
}


} // namespace globjects
