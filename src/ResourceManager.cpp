#include "ResourceManager.h"
#include <nlohmann/json.hpp>
#include <fstream>

sf::Sprite ResourceManager::get_sprite(std::string path) {
    sf::Texture *texture = nullptr;
    // This is also beautiful.
    if (loaded_resources.find(path) != loaded_resources.end() || load_texture(path)) {
        texture = loaded_resources.at(path).get_texture();
    }
    sf::Sprite sprite;
    if (texture) sprite.setTexture(*texture);
    return std::move(sprite);
}

bool ResourceManager::load_texture(std::string path) {
    auto texture = new sf::Texture;
    bool success = texture->loadFromFile(path);
    if (!success) logger_.write(Message("Could not load texture: ", path, '.'));
    else loaded_resources.insert({path, Resource(texture)});
    return success;
}

bool ResourceManager::load_texture_safe(std::string path) {
    if (loaded_resources.find(path) != loaded_resources.end()) return true;
    else return load_texture(path);
}

ResourceManager::Multi_Fail ResourceManager::load_from_file(std::string path) {
    std::ifstream file(path);
    nlohmann::json json;
    file >> json;
    Multi_Fail fails;
    for (auto &&key : json) {
        if (key.find("type") != key.end() && key.find("path") != key.end()) {
            if (!load_type_safe(std::string(key.at("type")), key.at("path"))) {
                fails.num_fails++;
                logger_.write(Message("Could not load texture ", key.at("path"),
                                      " listed in file ", path, '.'));
            }
        } else logger_.write(Message("Could not find type/path for key ", std::string(key), " in file ", path, '.'));
    }
    return fails;
}

bool ResourceManager::load_type_safe(std::string type, std::string path) {
    return load_type_safe(Resource::Parse_Type(std::move(type)), std::move(path));
}

bool ResourceManager::load_type_safe(Resource::Type type, std::string path) {
    switch (type) {
        case Resource::Type::Texture:
            return load_texture_safe(std::move(path));
        default:
            return false;
    }
}
