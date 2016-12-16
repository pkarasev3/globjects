
#pragma once

#include <string>
#include <memory>

#include <glbinding/gl/types.h>

#include <globjects/globjects_api.h>


namespace globjects 
{


class AttachedTexture;
class AttachedRenderbuffer;
class Framebuffer;

/** \brief Wraps attachments to a FrameBufferObject.
    
    Normally, FrameBufferAttachments are created using the API of FrameBufferObject.
    
    \see FrameBufferObject
    \see TextureAttachment
    \see RenderBufferAttachment
*/
class GLOBJECTS_API FramebufferAttachment
{
public:
    FramebufferAttachment(std::weak_ptr<Framebuffer> fbo, gl::GLenum attachment);

	gl::GLenum attachment() const;

    gl::GLint getParameter(gl::GLenum pname) const;

	virtual bool isTextureAttachment() const;
	virtual bool isRenderBufferAttachment() const;

    AttachedTexture * asTextureAttachment();
    const AttachedTexture * asTextureAttachment() const;
    AttachedRenderbuffer * asRenderBufferAttachment();
    const AttachedRenderbuffer * asRenderBufferAttachment() const;

	std::string attachmentString() const;

protected:
    std::weak_ptr<Framebuffer> m_fbo;
	gl::GLenum m_attachment;
};


} // namespace globjects
