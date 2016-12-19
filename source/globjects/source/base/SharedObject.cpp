
#include <globjects/base/SharedObject.h>


namespace globjects
{


SharedObject::SharedObject()
{
}

SharedObject::~SharedObject()
{
}

AbstractSharedObject::AbstractSharedObject()
{
}

AbstractSharedObject::~AbstractSharedObject()
{
}

void AbstractSharedObject::initialize()
{
    onInitialize();
}

void AbstractSharedObject::onInitialize()
{
}


} // namespace globjects
