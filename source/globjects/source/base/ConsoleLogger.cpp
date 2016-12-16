
#include <globjects/base/ConsoleLogger.h>

#include <iostream>

#include <globjects/base/LogMessage.h>
#include <globjects/base/LogMessageLevel.h>


namespace
{


const std::string fatal = "#fatal: ";
const std::string critical = "#critical: ";
const std::string warning = "#warning: ";
const std::string empty = "";


} // namespace


namespace globjects
{


void ConsoleLogger::handle(const LogMessage& message)
{
    if (LogMessageLevel::Info > message.level())
        std::cerr << levelString(message.level()) << message.message() << std::endl;
    else
        std::cout << levelString(message.level()) << message.message() << std::endl;
}

const std::string & ConsoleLogger::levelString(const LogMessageLevel level)
{
    switch (level)
    {
    case LogMessageLevel::Fatal:
        return fatal;
    case LogMessageLevel::Critical:
        return critical;
    case LogMessageLevel::Warning:
        return warning;
    default:
        return empty;
    }
}


} // namespace globjects
