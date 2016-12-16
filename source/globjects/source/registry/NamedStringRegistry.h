
#pragma once

#include <string>
#include <unordered_map>
#include <memory>


namespace globjects 
{


class NamedString;

class NamedStringRegistry
{
public:
    NamedStringRegistry();
    static NamedStringRegistry & current();

    void registerNamedString(std::shared_ptr<NamedString> namedString);
    void deregisterNamedString(std::shared_ptr<NamedString> namedString);

    bool hasNamedString(const std::string & name);
    std::weak_ptr<NamedString> namedString(const std::string & name);

    bool hasNativeSupport();
protected:
    std::unordered_map<std::string, std::shared_ptr<NamedString>> m_namedStrings;
};


} // namespace globjects
