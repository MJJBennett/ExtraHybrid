#ifndef NOVEMBERGAMEJAM_RESOURCEMANAGER_H
#define NOVEMBERGAMEJAM_RESOURCEMANAGER_H


#include <string>
#include <unordered_map>
#include "Resource.h"
#include "Logger.h"

class ResourceManager {
public:
    explicit ResourceManager(Logger<std::ostream>& logger) : logger_(logger) {}
    sf::Sprite get_sprite(std::string path);
    std::vector<sf::Sprite> sprites;
private:
    Logger<std::ostream>& logger_;
    std::unordered_map<std::string, Resource> loaded_resources;
};


#endif //NOVEMBERGAMEJAM_RESOURCEMANAGER_H
