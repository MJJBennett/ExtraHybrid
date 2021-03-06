#ifndef NOVEMBERGAMEJAM_RESOURCE_H
#define NOVEMBERGAMEJAM_RESOURCE_H

#include <string>
#include <SFML/Graphics.hpp>

class Resource {
public:
    enum class Type {
        Texture,
        None
    };
    static Type Parse_Type(std::string type) {
        if (type == "texture") return Type::Texture;
        else return Type::None;
    }
public:
    explicit Resource(sf::Texture* sprite) : data_(sprite), t_(Type::Texture) {}

    sf::Texture* get_texture() {
        if (t_ == Type::Texture) return static_cast<sf::Texture*>(data_);
        return nullptr;
    }
private:
    Type t_;
    void * data_;
};


#endif //NOVEMBERGAMEJAM_RESOURCE_H
