#ifndef NOVEMBERGAMEJAM_RESOURCEMANAGER_H
#define NOVEMBERGAMEJAM_RESOURCEMANAGER_H


#include <string>
#include <unordered_map>
#include "Resource.h"
#include "../core/Logger.h"

class GameObject;

/**
 * This class's function naming schemes are very simple.
 * Functions marked with _safe check for safety-related things.
 * Others do not.
 */
class ResourceManager {
public:
    struct Multi_Fail {
        int num_fails = 0;
        explicit operator bool() const {
            return num_fails == 0;
        }
    };
public:
    explicit ResourceManager(Logger<std::ostream>& logger) : logger_(logger) {}
    sf::Sprite get_sprite(std::string path);
    std::vector<sf::Sprite> sprites;
    // Returns true if the texture is loaded, false otherwise.
    bool load_texture_safe(std::string path);

    // Loads resources from a file. Assumes json format. Returns Multi_Fail object.
    // Is always safe. For... obvious reasons.
    // Paths are pre-pended with "../resources/"
    Multi_Fail load_from_file(std::string path);

    bool give_sprite(GameObject& object, std::string path);

    inline bool has_texture(const std::string path) {
        return loaded_resources.find(path) != loaded_resources.end();
    }


private:
    // Returns true if the texture is loaded, false otherwise.
    bool load_texture(std::string path);
    bool load_type_safe(std::string type, std::string path);
    bool load_type_safe(Resource::Type type, std::string path);
    // Returns a pointer to the texture.
    inline sf::Texture* get_texture(const std::string path) {
        return loaded_resources.at(path).get_texture();
    }
    Logger<std::ostream>& logger_;
    std::unordered_map<std::string, Resource> loaded_resources;
};


#endif //NOVEMBERGAMEJAM_RESOURCEMANAGER_H
