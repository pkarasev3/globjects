
#pragma once

#include <unordered_map>
#include <vector>

#include <glbinding/gl/types.h>

#include <globjects/globjects_api.h>
#include <globjects/AbstractState.h>
#include <globjects/StateSetting.h>
#include <globjects/base/SharedObject.h>


namespace globjects
{


class StateSetting;
class Capability;

class GLOBJECTS_API State : public SharedObject, public AbstractState
{
    using Super = SharedObject;

public:
    enum Mode
    {
        DeferredMode,
        ImmediateMode
    };

public:
    State(Mode = ImmediateMode);
    virtual ~State();

    static std::shared_ptr<State> currentState();

    void setMode(Mode mode);
    Mode mode() const;

    void apply();

    virtual void enable(gl::GLenum capability) override;
    virtual void disable(gl::GLenum capability) override;
    virtual bool isEnabled(gl::GLenum capability) const override;
    virtual void enable(gl::GLenum capability, int index) override;
    virtual void disable(gl::GLenum capability, int index) override;
    virtual bool isEnabled(gl::GLenum capability, int index) const override;

    virtual void add(std::unique_ptr<StateSetting> && setting) override;

    Capability * capability(gl::GLenum capability);
    const Capability * capability(gl::GLenum capability) const;
    std::vector<Capability *> capabilities() const;

    StateSetting * setting(const StateSettingType & type);
    const StateSetting * setting(const StateSettingType & type) const;
    std::vector<StateSetting *> settings();
    std::vector<const StateSetting *> settings() const;

protected:
    void addCapability(Capability * capability);
    Capability * getCapability(gl::GLenum capability);
    const Capability * getCapability(gl::GLenum capability) const;

    virtual void onInitialize() override;

protected:
    Mode m_mode;
    std::unordered_map<gl::GLenum, std::unique_ptr<Capability>> m_capabilities;
    std::unordered_map<StateSettingType, std::unique_ptr<StateSetting>> m_settings;
};


} // namespace globjects
