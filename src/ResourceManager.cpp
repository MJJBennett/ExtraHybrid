#include "ResourceManager.h"

sf::Sprite ResourceManager::get_sprite(std::string path) {
    sf::Texture * texture;
    if (loaded_resources.find(path) != loaded_resources.end()) {
        texture = loaded_resources.at(path).get_texture();
    }
    else {
        texture = new sf::Texture;
        if (!texture->loadFromFile(path)) logger_.write(Message("Could not load texture: ", path));
        else loaded_resources.insert({path, Resource(texture)});
    }
    sf::Sprite sprite;
    if (texture) sprite.setTexture(*texture);
    return std::move(sprite);
}
