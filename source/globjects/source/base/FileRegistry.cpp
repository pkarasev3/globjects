
#include "FileRegistry.h"

#include <cassert>

#include <globjects/base/File.h>


namespace globjects
{


void FileRegistry::registerFile(File * file)
{
    assert(file != nullptr);

    instance()->m_registeredFiles.insert(file);
}

void FileRegistry::deregisterFile(File * file)
{
    assert(file != nullptr);
    assert(instance()->m_registeredFiles.find(file) != instance()->m_registeredFiles.end());

    instance()->m_registeredFiles.erase(file);
}

void FileRegistry::reloadAll()
{
    for (File* file : instance()->m_registeredFiles)
    {
        file->reload();
    }
}


} // namespace globjects
