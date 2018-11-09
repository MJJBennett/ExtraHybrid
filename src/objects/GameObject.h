#ifndef NOVEMBERGAMEJAM_GAMEOBJECT_H
#define NOVEMBERGAMEJAM_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "PhysicsRect.h"

class GameObject : public sf::Drawable {
public:
    explicit GameObject(PhysicsRect rect = PhysicsRect()) : rect_(rect) {}
    void set_sprite_texture(sf::Texture* texture) { sprite_.setTexture(*texture); }

    // Positioning
    void shift_position(int x, int y);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite_, states);
    }
    void update_sprite() {
        sprite_.setPosition(rect_.x(), rect_.y());
    }
private:
    PhysicsRect rect_;
    sf::Sprite sprite_;
};


#endif //NOVEMBERGAMEJAM_GAMEOBJECT_H
