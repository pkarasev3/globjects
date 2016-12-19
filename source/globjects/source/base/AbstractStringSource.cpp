
#include <globjects/base/AbstractStringSource.h>


namespace globjects
{


std::vector<std::string> AbstractStringSource::strings() const
{
    std::vector<std::string> stringList;
    stringList.push_back(string());
    return stringList;
}

std::vector<std::shared_ptr<const AbstractStringSource>> AbstractStringSource::flatten() const
{
    std::vector<std::shared_ptr<const AbstractStringSource>> list;

    flattenInto(list);

    return list;
}

std::string AbstractStringSource::shortInfo() const
{
    return "";
}

void AbstractStringSource::flattenInto(std::vector<std::shared_ptr<const AbstractStringSource>> & vector) const
{
    vector.push_back(shared_from_this<AbstractStringSource>());
}


} // namespace globjects
