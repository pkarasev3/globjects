
#include <globjects/base/CompositeStringSource.h>

#include <sstream>
#include <cassert>


namespace globjects
{


CompositeStringSource::CompositeStringSource()
: m_dirty(true)
{
}

CompositeStringSource::CompositeStringSource(const std::vector<std::shared_ptr<AbstractStringSource>> & sources)
: m_sources(sources)
, m_dirty(true)
{
}

CompositeStringSource::~CompositeStringSource()
{
    for (const auto & source : m_sources)
    {
        source->deregisterListener(ChangeListener::shared_this<ChangeListener>());
    }
}

void CompositeStringSource::onInitialize()
{
    Super::onInitialize();

    for (const auto & source : m_sources)
    {
        source->registerListener(ChangeListener::shared_this<ChangeListener>());
    }
}

void CompositeStringSource::appendSource(std::shared_ptr<AbstractStringSource> source)
{
    assert(source != nullptr);

    m_sources.push_back(source);
    source->registerListener(ChangeListener::shared_this<ChangeListener>());
    changed();
}

void CompositeStringSource::notifyChanged(const AbstractChangeable *)
{
    m_dirty = true;
    changed();
}

std::string CompositeStringSource::string() const
{
    std::stringstream source;

    for (const std::string & str : strings())
    {
        source << str << std::endl;
    }

    return source.str();
}

std::vector<std::string> CompositeStringSource::strings() const
{
    if (m_dirty)
        update();

    return m_strings;
}

void CompositeStringSource::flattenInto(std::vector<std::shared_ptr<const AbstractStringSource>> & vector) const
{
    for (const auto & source : m_sources)
    {
        source->flattenInto(vector);
    }
}

void CompositeStringSource::update() const
{
    m_strings.clear();

    for (const std::shared_ptr<AbstractStringSource>& source : m_sources)
    {
        for (const std::string & str : source->strings())
        {
            m_strings.push_back(str);
        }
    }

    m_dirty = false;
}

std::string CompositeStringSource::shortInfo() const
{
    std::stringstream info;

    for (const auto & source : m_sources)
    {
        info << source->shortInfo() << std::endl;
    }

    return info.str();
}


} // namespace globjects
