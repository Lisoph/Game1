#pragma once
#include <string>
// #include <map>
#include <vector>

template <typename T>
struct CppDefaultDeleter
{
  void operator () (T *foo)
  {
    delete foo;
  }
};

template <typename ResourceType, typename Deleter = CppDefaultDeleter<ResourceType>>
class ResourceManager
{
  public:
    typedef std::vector<std::pair<size_t, ResourceType*>> MapType;
    static std::hash<std::string> strHash;
  protected:
    MapType resources;
    std::vector<std::string> resourceNames;
  public:
    ResourceManager(void);
    ~ResourceManager(void);
    
    inline bool AddResource(const std::string &name, ResourceType *resource);
    void RemoveResource(const std::string &name);
    ResourceType *Resource(const std::string &name);
    ResourceType *Resource(size_t index);
    bool DoesResourceExist(const std::string &name) { return Resource(name) != nullptr; }
    size_t NumResources(void) { return resources.size(); }
};

#include "resource_manager.impl"