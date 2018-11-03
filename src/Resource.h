#ifndef NOVEMBERGAMEJAM_RESOURCE_H
#define NOVEMBERGAMEJAM_RESOURCE_H


#include <string>
#include <SFML/Graphics/Sprite.hpp>


class Resource {
public:
    enum class Type {
        Sprite
    };
public:
    explicit Resource(sf::Sprite* sprite) : data_(sprite), t_(Type::Sprite) {}
private:
    Type t_;
    void * data_;
};


#endif //NOVEMBERGAMEJAM_RESOURCE_H
