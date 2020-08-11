#include "pch.h"
#include "ResourceManager.h"

namespace nc
{
    bool ResourceManager::Startup()
    {
        return false;
    }

    void ResourceManager::Shutdown()
    {
        removeAll();
    }

    void ResourceManager::Update()
    {    
    }

    void ResourceManager::removeAll()
    {
        for (auto resource : m_resources)
        {
            resource.second->Destroy();
            delete resource.second;
        }

        m_resources.clear();
    }
}
