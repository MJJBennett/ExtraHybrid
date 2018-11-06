#ifndef NOVEMBERGAMEJAM_GAMEOBJECT_H
#define NOVEMBERGAMEJAM_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "PhysicsRect.h"

class GameObject : public sf::Drawable {
public:
    explicit GameObject(PhysicsRect rect = PhysicsRect()) : rect_(rect) {}
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite_, states);
    }
private:
    PhysicsRect rect_;
    sf::Sprite sprite_;
};


#endif //NOVEMBERGAMEJAM_GAMEOBJECT_H
