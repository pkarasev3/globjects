
#include <globjects/AttachedRenderbuffer.h>

#include <cassert>

#include <globjects/Renderbuffer.h>

using namespace gl;


namespace globjects
{


AttachedRenderbuffer::AttachedRenderbuffer(std::weak_ptr<Framebuffer> fbo,  const GLenum attachment, std::shared_ptr<Renderbuffer> renderBuffer)
: FramebufferAttachment(fbo, attachment)
, m_renderBuffer(renderBuffer)
{
}

bool AttachedRenderbuffer::isRenderBufferAttachment() const
{
	return true;
}

std::shared_ptr<Renderbuffer> AttachedRenderbuffer::renderBuffer()
{
	return m_renderBuffer;
}

std::shared_ptr<const Renderbuffer> AttachedRenderbuffer::renderBuffer() const
{
    return m_renderBuffer;
}


} // namespace globjects
