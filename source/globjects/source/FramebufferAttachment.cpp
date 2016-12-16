
#include <globjects/FramebufferAttachment.h>

#include <string>

#include <glbinding/Meta.h>

#include <globjects/Framebuffer.h>
#include <globjects/AttachedRenderbuffer.h>
#include <globjects/AttachedTexture.h>

using namespace gl;


namespace globjects
{


FramebufferAttachment::FramebufferAttachment(std::weak_ptr<Framebuffer> fbo, GLenum attachment)
: m_fbo(fbo)
, m_attachment(attachment)
{
}

GLenum FramebufferAttachment::attachment() const
{
	return m_attachment;
}

GLint FramebufferAttachment::getParameter(GLenum pname) const
{
    const auto ptr = m_fbo.lock();

    if (ptr)
    {
        return ptr->getAttachmentParameter(m_attachment, pname);
    }

    return 0;
}

bool FramebufferAttachment::isTextureAttachment() const
{
	return false;
}

bool FramebufferAttachment::isRenderBufferAttachment() const
{
	return false;
}

std::string FramebufferAttachment::attachmentString() const
{
    return glbinding::Meta::getString(m_attachment);
}

AttachedTexture * FramebufferAttachment::asTextureAttachment()
{
    return isTextureAttachment() ? static_cast<AttachedTexture*>(this) : nullptr;
}

const AttachedTexture * FramebufferAttachment::asTextureAttachment() const
{
    return isTextureAttachment() ? static_cast<const AttachedTexture*>(this) : nullptr;
}

AttachedRenderbuffer * FramebufferAttachment::asRenderBufferAttachment()
{
    return isRenderBufferAttachment() ? static_cast<AttachedRenderbuffer*>(this) : nullptr;
}

const AttachedRenderbuffer * FramebufferAttachment::asRenderBufferAttachment() const
{
    return isRenderBufferAttachment() ? static_cast<const AttachedRenderbuffer*>(this) : nullptr;
}


} // namespace globjects
