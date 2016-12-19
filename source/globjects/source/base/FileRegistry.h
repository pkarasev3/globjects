
#pragma once


#include <set>

#include <globjects/base/Singleton.h>


namespace globjects
{


class File;

class FileRegistry : public Singleton<FileRegistry>
{
public:
    static void registerFile(File * file);
    static void deregisterFile(File * file);

    static void reloadAll();
protected:

    std::set<File*> m_registeredFiles;
};


} // namespace globjects
