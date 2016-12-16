
#include <globjects/State.h>

#include <glbinding/gl/enum.h>
#include <glbinding/gl/extension.h>
#include <glbinding/Version.h>

#include <globjects/globjects.h>
#include <globjects/Capability.h>
#include <globjects/StateSetting.h>

using namespace gl;


namespace globjects 
{


State::State(const Mode mode)
: m_mode(mode)
{
}

State::~State()
{
}

std::shared_ptr<State> State::currentState()
{
    std::shared_ptr<State> state(new State(DeferredMode));

    std::vector<GLenum> capabilities = {
        GL_BLEND,
        GL_COLOR_LOGIC_OP,
        GL_CULL_FACE,
        GL_DEPTH_CLAMP,
        GL_DEPTH_TEST,
        GL_DITHER,
        GL_FRAMEBUFFER_SRGB,
        GL_LINE_SMOOTH,
        GL_MULTISAMPLE,
        GL_POLYGON_OFFSET_FILL,
        GL_POLYGON_OFFSET_LINE,
        GL_POLYGON_OFFSET_POINT,
        GL_POLYGON_SMOOTH,
        GL_PROGRAM_POINT_SIZE,
        GL_RASTERIZER_DISCARD,
        GL_SAMPLE_ALPHA_TO_COVERAGE,
        GL_SAMPLE_ALPHA_TO_ONE,
        GL_SAMPLE_COVERAGE,
        GL_SAMPLE_MASK,
        GL_SCISSOR_TEST,
        GL_STENCIL_TEST
    };

    if (globjects::version() >= glbinding::Version(3, 1))
    {
        capabilities.push_back(GL_PRIMITIVE_RESTART);
        if (hasExtension(GLextension::GL_ARB_ES3_compatibility))
        {
            capabilities.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);
        }
        state->primitiveRestartIndex(getInteger(GL_PRIMITIVE_RESTART_INDEX));

        if (hasExtension(GLextension::GL_ARB_sample_shading))
        {
            capabilities.push_back(GL_SAMPLE_SHADING);
        }
        if (hasExtension(GLextension::GL_ARB_seamless_cube_map))
        {
            capabilities.push_back(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        }
        if (hasExtension(GLextension::GL_ARB_provoking_vertex))
        {
            state->provokingVertex(getEnum(GL_PROVOKING_VERTEX));
        }
        // is this necessary here? should be controlled by debugmessageoutput
        if (hasExtension(GLextension::GL_KHR_debug))
        {
            capabilities.push_back(GL_DEBUG_OUTPUT);
            capabilities.push_back(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        }
    }

    for (GLenum capability : capabilities)
    {
        state->setEnabled(capability, globjects::isEnabled(capability));
    }

    state->blendColor(getFloats<4>(GL_BLEND_COLOR));
    state->blendFuncSeparate(getEnum(GL_BLEND_SRC_RGB), getEnum(GL_BLEND_DST_RGB), getEnum(GL_BLEND_SRC_ALPHA), getEnum(GL_BLEND_DST_ALPHA));
    state->clearColor(getFloats<4>(GL_COLOR_CLEAR_VALUE));
    state->clearDepth(getFloat(GL_DEPTH_CLEAR_VALUE));
    state->clearStencil(getInteger(GL_STENCIL_CLEAR_VALUE));
    state->colorMask(getBooleans<4>(GL_COLOR_WRITEMASK));
    state->cullFace(getEnum(GL_CULL_FACE_MODE));
    state->depthFunc(getEnum(GL_DEPTH_FUNC));
    state->depthMask(getBoolean(GL_DEPTH_WRITEMASK));
    state->depthRange(getFloats<2>(GL_DEPTH_RANGE));
    state->frontFace(getEnum(GL_FRONT_FACE));
    state->logicOp(getEnum(GL_LOGIC_OP_MODE));
    state->pointParameter(GL_POINT_FADE_THRESHOLD_SIZE, getEnum(GL_POINT_FADE_THRESHOLD_SIZE));
    state->pointParameter(GL_POINT_SPRITE_COORD_ORIGIN, getEnum(GL_POINT_SPRITE_COORD_ORIGIN));
    state->pointSize(getFloat(GL_POINT_SIZE));
    state->polygonMode(GL_FRONT, getEnums<2>(GL_POLYGON_MODE)[0]);
    state->polygonMode(GL_BACK, getEnums<2>(GL_POLYGON_MODE)[1]);
    state->polygonOffset(getFloat(GL_POLYGON_OFFSET_FACTOR), getFloat(GL_POLYGON_OFFSET_UNITS));
    state->sampleCoverage(getFloat(GL_SAMPLE_COVERAGE_VALUE), getBoolean(GL_SAMPLE_COVERAGE_INVERT));
    state->scissor(getIntegers<4>(GL_SCISSOR_BOX));
    state->stencilFuncSeparate(GL_FRONT, getEnum(GL_STENCIL_FUNC), getInteger(GL_STENCIL_REF), getInteger(GL_STENCIL_VALUE_MASK));
    state->stencilOpSeparate(GL_FRONT, getEnum(GL_STENCIL_FAIL), getEnum(GL_STENCIL_PASS_DEPTH_FAIL), getEnum(GL_STENCIL_PASS_DEPTH_PASS));
    state->stencilMaskSeparate(GL_FRONT, getInteger(GL_STENCIL_WRITEMASK));
    state->stencilFuncSeparate(GL_BACK, getEnum(GL_STENCIL_BACK_FUNC), getInteger(GL_STENCIL_BACK_REF), getInteger(GL_STENCIL_BACK_VALUE_MASK));
    state->stencilOpSeparate(GL_BACK, getEnum(GL_STENCIL_BACK_FAIL), getEnum(GL_STENCIL_BACK_PASS_DEPTH_FAIL), getEnum(GL_STENCIL_BACK_PASS_DEPTH_PASS));
    state->stencilMaskSeparate(GL_BACK, getInteger(GL_STENCIL_BACK_WRITEMASK));

    // pixel store
    std::vector<GLenum> pixelstoreParameters = {
        GL_PACK_SWAP_BYTES,
        GL_PACK_LSB_FIRST,
        GL_PACK_ROW_LENGTH,
        GL_PACK_IMAGE_HEIGHT,
        GL_PACK_SKIP_PIXELS,
        GL_PACK_SKIP_ROWS,
        GL_PACK_SKIP_IMAGES,
        GL_PACK_ALIGNMENT,
        GL_UNPACK_SWAP_BYTES,
        GL_UNPACK_LSB_FIRST,
        GL_UNPACK_ROW_LENGTH,
        GL_UNPACK_IMAGE_HEIGHT,
        GL_UNPACK_SKIP_PIXELS,
        GL_UNPACK_SKIP_ROWS,
        GL_UNPACK_SKIP_IMAGES,
        GL_UNPACK_ALIGNMENT
    };
    for (GLenum param : pixelstoreParameters)
    {
        state->pixelStore(param, getInteger(param));
    }

    return std::move(state);
}

void State::enable(const GLenum capability)
{
    Capability* cap = getCapability(capability);
    cap->enable();
    if (m_mode == ImmediateMode)
        cap->apply();
}

void State::disable(const GLenum capability)
{
    Capability* cap = getCapability(capability);
    cap->disable();
    if (m_mode == ImmediateMode)
        cap->apply();
}

bool State::isEnabled(const GLenum capability) const
{
    const auto it = m_capabilities.find(capability);

    if (it == m_capabilities.end())
        return false;

    return it->second->isEnabled();
}

void State::enable(const GLenum capability, const int index)
{   
    Capability* cap = getCapability(capability);
    cap->enable(index);
    if (m_mode == ImmediateMode)
        cap->apply();
}

void State::disable(const GLenum capability, const int index)
{
    Capability* cap = getCapability(capability);
    cap->disable(index);
    if (m_mode == ImmediateMode)
        cap->apply();
}

bool State::isEnabled(const GLenum capability, const int index) const
{
    const auto it = m_capabilities.find(capability);

    if (it == m_capabilities.end())
        return false;

    return it->second->isEnabled(index);
}

void State::setMode(const Mode mode)
{
    m_mode = mode;
}

State::Mode State::mode() const
{
    return m_mode;
}

void State::apply()
{
    for (const auto & capability : m_capabilities)
    {
        capability.second->apply();
    }
    for (const auto & setting : m_settings)
    {
        setting.second->apply();
    }
}

void State::addCapability(Capability * capability)
{
    const auto it = m_capabilities.find(capability->capability());
    if (it != m_capabilities.end())
    {
        it->second.reset(capability);

        return;
    }

    m_capabilities.emplace(capability->capability(), std::unique_ptr<Capability>(capability));
}

Capability* State::getCapability(GLenum capability)
{
    const auto it = m_capabilities.find(capability);
    if (it == m_capabilities.end())
    {
        const auto insertedIt = m_capabilities.emplace(capability, std::unique_ptr<Capability>(new Capability(capability)));

        return insertedIt.first->second.get();
    }

    return it->second.get();
}

std::vector<Capability*> State::capabilities() const
{
    std::vector<Capability*> caps;
    caps.reserve(m_capabilities.size());

    for (const auto & capability : m_capabilities)
    {
        caps.push_back(capability.second.get());
    }

    return caps;
}

Capability* State::capability(const GLenum capability)
{
    const auto it = m_capabilities.find(capability);

    if (it == m_capabilities.end())
    {
        return nullptr;
    }

    return it->second.get();
}

const Capability* State::capability(const GLenum capability) const
{
    const auto it = m_capabilities.find(capability);

    if (it == m_capabilities.end())
    {
        return nullptr;
    }

    return it->second.get();
}

std::vector<StateSetting*> State::settings()
{
    std::vector<StateSetting*> settings;
    settings.reserve(m_settings.size());

    for (const auto & setting : m_settings)
    {
        settings.push_back(setting.second.get());
    }

    return settings;
}

std::vector<const StateSetting*> State::settings() const
{
    std::vector<const StateSetting*> settings;
    settings.reserve(m_settings.size());

    for (const auto & setting : m_settings)
    {
        settings.push_back(setting.second.get());
    }

    return settings;
}

StateSetting * State::setting(const StateSettingType & type)
{
    const auto it = m_settings.find(type);

    if (it == m_settings.end())
    {
        return nullptr;
    }

    return it->second.get();
}

const StateSetting * State::setting(const StateSettingType & type) const
{
    const auto it = m_settings.find(type);

    if (it == m_settings.end())
    {
        return nullptr;
    }

    return it->second.get();
}

void State::add(std::unique_ptr<StateSetting> && setting)
{
    const auto type = setting->type();
    const auto it = m_settings.find(type);

    if (it != m_settings.end())
    {
        it->second = std::move(setting);
    }
    else
    {
        m_settings.emplace(type, std::move(setting));
    }

    if (m_mode == ImmediateMode)
    {
        setting->apply();
    }
}


} // namespace globjects
