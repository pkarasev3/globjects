
#include <globjects/AttachedTexture.h>

#include <cassert>

#include <globjects/Texture.h>

using namespace gl;


namespace globjects
{


AttachedTexture::AttachedTexture(std::weak_ptr<Framebuffer> fbo, const GLenum attachment, std::shared_ptr<Texture> texture, GLint level, GLint layer)
: FramebufferAttachment(fbo, attachment)
, m_texture(texture)
, m_level(level)
, m_layer(layer)
{
}

bool AttachedTexture::isTextureAttachment() const
{
	return true;
}

std::shared_ptr<Texture> AttachedTexture::texture()
{
	return m_texture;
}

std::shared_ptr<const Texture> AttachedTexture::texture() const
{
    return m_texture;
}

GLint AttachedTexture::level() const
{
    return m_level;
}

bool AttachedTexture::hasLayer() const
{
    return m_layer >= 0;
}

GLint AttachedTexture::layer() const
{
    return m_layer;
}


} // namespace globjects
