#ifndef NOVEMBERGAMEJAM_RESOURCEMANAGER_H
#define NOVEMBERGAMEJAM_RESOURCEMANAGER_H


#include <string>
#include <unordered_map>
#include "Resource.h"

class ResourceManager {
public:

private:
    std::unordered_map<std::string, Resource> loaded_resources;
};


#endif //NOVEMBERGAMEJAM_RESOURCEMANAGER_H
