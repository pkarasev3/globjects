
#include <globjects/base/SharedObject.h>


namespace globjects
{


SharedObject::SharedObject()
{
}

SharedObject::~SharedObject()
{
}

void SharedObject::initialize()
{
    onInitialize();
}


} // namespace globjects
