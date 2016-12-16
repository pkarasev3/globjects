
#include "IncludeProcessor.h"

#include <sstream>
#include <algorithm>
#include <cctype>

#include <globjects/base/AbstractStringSource.h>
#include <globjects/base/StaticStringSource.h>
#include <globjects/base/CompositeStringSource.h>

#include <globjects/logging.h>
#include <globjects/globjects.h>
#include <globjects/NamedString.h>


namespace
{


// From http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
inline std::string trim(const std::string &s)
{
   auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
   auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
   return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}

inline bool contains(const std::string& string, const std::string& search)
{
    return string.find(search) != std::string::npos;
}

inline bool startsWith(const std::string& string, char firstChar)
{
    return !string.empty() && string.front() == firstChar;
}

inline bool endsWith(const std::string& string, char firstChar)
{
    return !string.empty() && string.back() == firstChar;
}


} // namespace


namespace globjects
{


IncludeProcessor::IncludeProcessor()
{
}

IncludeProcessor::~IncludeProcessor()
{
}

std::shared_ptr<AbstractStringSource> IncludeProcessor::resolveIncludes(const AbstractStringSource* source, const std::vector<std::string>& includePaths)
{
    IncludeProcessor processor;
    processor.m_includePaths = includePaths;

    return processor.processComposite(source);
}

std::shared_ptr<CompositeStringSource> IncludeProcessor::processComposite(const AbstractStringSource* source)
{
    std::shared_ptr<CompositeStringSource> composite(new CompositeStringSource());

    for (const auto & innerSource : source->flatten())
    {
        composite->appendSource(process(innerSource.get()));
    }

    return composite;
}

std::shared_ptr<CompositeStringSource> IncludeProcessor::process(const AbstractStringSource* source)
{
    std::shared_ptr<CompositeStringSource> compositeSource(new CompositeStringSource());

    std::istringstream sourcestream(source->string());
    std::stringstream destinationstream;

    bool inMultiLineComment = false;

    do
    {
        std::string line;

        std::getline(sourcestream, line);

        std::string trimmedLine = trim(line);

        if (trimmedLine.size() > 0)
        {
            if (contains(trimmedLine, "/*"))
            {
                inMultiLineComment = true;
            }

            if (contains(trimmedLine, "*/"))
            {
                inMultiLineComment = false;
            }

            if (!inMultiLineComment)
            {
                if (trimmedLine[0] == '#')
                {
                    if (contains(trimmedLine, "#extension"))
                    {
                        // #extension GL_ARB_shading_language_include : require
                        if (contains(trimmedLine, "GL_ARB_shading_language_include"))
                        {
                            destinationstream << "//" << trimmedLine << '\n';
                        }
                        else
                        {
                            destinationstream << line << '\n';
                        }
                    }
                    else if (contains(trimmedLine, "#include"))
                    {
                        parseInclude(trimmedLine, compositeSource.get(), destinationstream);
                    }
                    else
                    {
                        // other macro
                        destinationstream << line << '\n';
                    }
                }
                else
                {
                    // normal line
                    destinationstream << line << '\n';
                }
            }
            else
            {
                // commented line
                destinationstream << line << '\n';
            }
        }
        else
        {
            // empty line
            destinationstream << line << '\n';
        }
    }
    while (sourcestream.good());

    if (!destinationstream.str().empty())
    {
        compositeSource->appendSource(std::shared_ptr<AbstractStringSource>(new StaticStringSource(destinationstream.str())));
    }

    return compositeSource;
}

void IncludeProcessor::parseInclude(std::string & trimmedLine, CompositeStringSource * compositeSource, std::stringstream & destinationstream)
{
    size_t leftBracketPosition = trimmedLine.find_first_of('<');
    size_t rightBracketPosition = trimmedLine.find_last_of('>');
    size_t leftQuotePosition = trimmedLine.find_first_of('"');
    size_t rightQuotePosition = trimmedLine.find_last_of('"');

    size_t leftDelimiter = std::string::npos;
    size_t rightDelimiter = std::string::npos;

    if (leftBracketPosition != std::string::npos && rightBracketPosition != std::string::npos)
    {
        leftDelimiter = leftBracketPosition;
        rightDelimiter = rightBracketPosition;
    }
    else if (leftQuotePosition != std::string::npos && rightQuotePosition != std::string::npos && leftQuotePosition < rightQuotePosition)
    {
        leftDelimiter = leftQuotePosition;
        rightDelimiter = rightQuotePosition;
    }

    if (leftDelimiter != std::string::npos && rightDelimiter != std::string::npos)
    {
        std::string include = trimmedLine.substr(leftDelimiter+1, rightDelimiter - leftDelimiter - 1);

        if (include.size() != 0 && !endsWith(include, '/'))
        {
            processInclude(include, compositeSource, destinationstream);
        }
        else
        {
            warning() << "Malformed #include " << include;
        }
    }
    else
    {
        warning() << "Malformed #include " << trimmedLine;
    }
}

void IncludeProcessor::processInclude(std::string & include, CompositeStringSource * compositeSource, std::stringstream & destinationstream)
{
    if (m_includes.count(include) > 0)
    {
        return;
    }

    m_includes.insert(include);
    compositeSource->appendSource(std::shared_ptr<AbstractStringSource>(new StaticStringSource(destinationstream.str())));

    std::shared_ptr<NamedString> namedString = nullptr;
    if (startsWith(include, '/'))
    {
        namedString = NamedString::obtain(include);
    }
    else
    {
        for (const std::string & prefix : m_includePaths)
        {
            namedString = NamedString::obtain(expandPath(include, prefix));
            if (namedString)
            {
                break;
            }
        }
    }

    if (namedString)
    {
        compositeSource->appendSource(processComposite(namedString->stringSource().get()));
    }
    else
    {
        warning() << "Did not find include " << include;
    }

    destinationstream.str("");
}

std::string IncludeProcessor::expandPath(const std::string& include, const std::string & includePath)
{
    return endsWith(includePath, '/') ? includePath + include : includePath + "/" + include;
}


} // namespace globjects
