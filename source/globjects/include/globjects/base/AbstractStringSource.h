
#pragma once

#include <string>
#include <vector>
#include <memory>

#include <globjects/globjects_api.h>

#include <globjects/base/Changeable.h>


namespace globjects
{


class CompositeStringSource;

/** \brief Superclass for all types of static and dynamic strings, e.g. for the use as Shader code.
 *
 * The current string can be queried using string().
 *
 * \see Shader
 */
class GLOBJECTS_API AbstractStringSource : public Changeable, std::enable_shared_from_this<AbstractStringSource>
{
public:
    virtual std::string string() const = 0;
    virtual std::vector<std::string> strings() const;

    std::vector<std::shared_ptr<const AbstractStringSource>> flatten() const;
    virtual void flattenInto(std::vector<std::shared_ptr<const AbstractStringSource>> & vector) const;

    virtual std::string shortInfo() const;
};


} // namespace globjects
