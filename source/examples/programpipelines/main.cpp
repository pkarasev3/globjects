
#include <iostream>

#include <glm/vec2.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/ContextInfo.h>
#include <glbinding/Version.h>

#include <GLFW/glfw3.h>

#include <globjects/globjects.h>
#include <globjects/base/File.h>
#include <globjects/logging.h>

#include <globjects/Buffer.h>
#include <globjects/Program.h>
#include <globjects/ProgramPipeline.h>
#include <globjects/Shader.h>
#include <globjects/VertexArray.h>
#include <globjects/VertexAttributeBinding.h>
#include <globjects/base/StaticStringSource.h>


using namespace gl;


namespace 
{
    const auto vertexShaderCode = R"(
#version 140
#extension GL_ARB_explicit_attrib_location : require

layout (location = 0) in vec2 corner;

out vec4 color;

void main()
{
    gl_Position = vec4(corner * 2.0 - 1.0, 0.0, 1.0);
    color = vec4(corner, 0.0, 1.0);
}

)";
    const auto fragmentShaderCode = R"(
#version 140
#extension GL_ARB_explicit_attrib_location : require

layout (location = 0) out vec4 fragColor;

in vec4 color;

void main()
{
    fragColor = color;
}

)";

    std::shared_ptr<globjects::Buffer> g_cornerBuffer;
    std::shared_ptr<globjects::Program> g_vertexProgram;
    std::shared_ptr<globjects::Program> g_fragmentProgram;
    std::shared_ptr<globjects::ProgramPipeline> g_programPipeline;
    std::shared_ptr<globjects::VertexArray> g_vao;

    auto g_size = glm::ivec2{ };
}


void initialize()
{
    g_cornerBuffer = std::shared_ptr<globjects::Buffer>(new globjects::Buffer());
    g_vertexProgram = std::shared_ptr<globjects::Program>(new globjects::Program());
    g_fragmentProgram = std::shared_ptr<globjects::Program>(new globjects::Program());
    g_programPipeline = std::shared_ptr<globjects::ProgramPipeline>(new globjects::ProgramPipeline());
    g_vao = std::shared_ptr<globjects::VertexArray>(new globjects::VertexArray());

    g_vertexProgram->attach(globjects::Shader::fromString(GL_VERTEX_SHADER,  vertexShaderCode));
    g_fragmentProgram->attach(globjects::Shader::fromString(GL_FRAGMENT_SHADER, fragmentShaderCode));

    g_programPipeline->useStages(g_vertexProgram, gl::GL_VERTEX_SHADER_BIT);
    g_programPipeline->useStages(g_fragmentProgram, gl::GL_FRAGMENT_SHADER_BIT);

    g_cornerBuffer->setData(std::array<glm::vec2, 4>{ {
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(0, 1), glm::vec2(1, 1) } }, GL_STATIC_DRAW);

    g_vao->binding(0)->setAttribute(0);
    g_vao->binding(0)->setBuffer(g_cornerBuffer, 0, sizeof(glm::vec2));
    g_vao->binding(0)->setFormat(2, GL_FLOAT);
    g_vao->enable(0);
}

void deinitialize()
{
    globjects::detachAllObjects();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, g_size.x, g_size.y);

    g_programPipeline->use();
    g_vao->drawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void error(int errnum, const char * errmsg)
{
    globjects::critical() << errnum << ": " << errmsg << std::endl;
}

void framebuffer_size_callback(GLFWwindow * /*window*/, int width, int height)
{
    g_size = glm::ivec2{ width, height };
}

void key_callback(GLFWwindow * window, int key, int /*scancode*/, int action, int /*modes*/)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);
}


int main(int /*argc*/, char * /*argv*/[])
{
    // Initialize GLFW
    if (!glfwInit())
        return 1;

    glfwSetErrorCallback(error);
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

    // Create a context and, if valid, make it current
    GLFWwindow * window = glfwCreateWindow(640, 480, "globjects Progam Pipelines", NULL, NULL);
    if (window == nullptr)
    {
        globjects::critical() << "Context creation failed. Terminate execution.";

        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwMakeContextCurrent(window);

    // Initialize globjects (internally initializes glbinding, and registers the current context)
    globjects::init();

    std::cout << std::endl
        << "OpenGL Version:  " << glbinding::ContextInfo::version() << std::endl
        << "OpenGL Vendor:   " << glbinding::ContextInfo::vendor() << std::endl
        << "OpenGL Renderer: " << glbinding::ContextInfo::renderer() << std::endl << std::endl;

    glfwGetFramebufferSize(window, &g_size[0], &g_size[1]);
    initialize();

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        draw();
        glfwSwapBuffers(window);
    }
    deinitialize();

    // Properly shutdown GLFW
    glfwTerminate();

    return 0;
}
