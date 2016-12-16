#pragma once

#include <memory>


namespace globjects
{

class VertexArray;
class Program;
class Buffer;
class Texture;
class Shader;

}


class ScreenAlignedQuad
{
public:
    ScreenAlignedQuad(std::shared_ptr<globjects::Shader> fragmentShader, std::shared_ptr<globjects::Texture> texture);

    ScreenAlignedQuad(std::shared_ptr<globjects::Texture> texture);
    ScreenAlignedQuad(std::shared_ptr<globjects::Shader> fragmentShader);
    ScreenAlignedQuad(std::shared_ptr<globjects::Program> program);

	void draw();

    globjects::Program * program();

    globjects::Shader * vertexShader();
    globjects::Shader * fragmentShader();

    void setTexture(std::shared_ptr<globjects::Texture> texture);

	void setSamplerUniform(int index);

protected:
    void initialize();

protected:
    std::shared_ptr<globjects::VertexArray> m_vao;

    std::shared_ptr<globjects::Buffer> m_buffer;

    std::shared_ptr<globjects::Shader> m_vertexShader;
    std::shared_ptr<globjects::Shader> m_fragmentShader;

    std::shared_ptr<globjects::Program> m_program;
    std::shared_ptr<globjects::Texture> m_texture;

    int m_samplerIndex;

protected:
	static const char * s_defaultVertexShaderSource;
    static const char * s_defaultFragmentShaderSource;
};
