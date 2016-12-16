
#pragma once

#include <memory>

#include <glbinding/gl/types.h>

#include <globjects/globjects_api.h>
#include <globjects/FramebufferAttachment.h>


namespace globjects 
{


class Renderbuffer;
class Framebuffer;

/** \brief Wrapper of render buffer attachments of a frame buffer object.
    
    This class is a link between a RenderBufferObject and the FrameBufferObject
    it is attached to. To get the attached render buffer, call renderBuffer().
    
    \see Renderbuffer
    \see Framebuffer
 */
class GLOBJECTS_API AttachedRenderbuffer : public FramebufferAttachment
{
public:
    AttachedRenderbuffer(std::weak_ptr<Framebuffer> fbo,  gl::GLenum attachment, std::shared_ptr<Renderbuffer> renderBuffer);

    virtual bool isRenderBufferAttachment() const override;

    std::shared_ptr<Renderbuffer> renderBuffer();
    std::shared_ptr<const Renderbuffer> renderBuffer() const;

protected:
    std::shared_ptr<Renderbuffer> m_renderBuffer;
};


} // namespace globjects
