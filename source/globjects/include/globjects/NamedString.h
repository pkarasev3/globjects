
#pragma once

#include <string>
#include <memory>

#include <glbinding/gl/types.h>

#include <globjects/base/ChangeListener.h>

#include <globjects/globjects_api.h>


namespace globjects 
{


class AbstractStringSource;

class GLOBJECTS_API NamedString : protected ChangeListener, std::enable_shared_from_this<NamedString>
{
public:
    virtual ~NamedString();

    static std::shared_ptr<NamedString> create(const std::string & name, std::shared_ptr<AbstractStringSource> string);
    static std::shared_ptr<NamedString> create(const std::string & name, const std::string & string);

    static bool isNamedString(const std::string & name);
    static std::shared_ptr<NamedString> obtain(const std::string & name);

public:
    const std::string & name() const;
    std::string string() const;
    gl::GLenum type() const;

    std::shared_ptr<AbstractStringSource> stringSource() const;

    gl::GLint getParameter(gl::GLenum pname) const;

    virtual void notifyChanged(const Changeable * changeable) override;

protected:
    static bool hasNativeSupport();

    static std::shared_ptr<NamedString> create(const std::string & name, std::shared_ptr<AbstractStringSource> string, gl::GLenum type);
    static std::shared_ptr<NamedString> create(const std::string & name, const std::string & string, gl::GLenum type);

protected:
    void updateString();

    void createNamedString();
    void deleteNamedString();

    NamedString(const std::string & name, std::shared_ptr<AbstractStringSource> source, gl::GLenum type);

    void registerNamedString();
    void deregisterNamedString();

protected:
    std::string m_name;

    std::shared_ptr<AbstractStringSource> m_source;
    gl::GLenum m_type;
};


} // namespace globjects
