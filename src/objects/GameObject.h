#ifndef NOVEMBERGAMEJAM_GAMEOBJECT_H
#define NOVEMBERGAMEJAM_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "PhysicsRect.h"
#include "tools/Timer.h"

class GameObject : public sf::Drawable {
    friend class PhysicsManager;
public:
    explicit GameObject(PhysicsRect rect = PhysicsRect()) : rect_(rect) { update_sprite(); }
    void set_sprite_texture(sf::Texture* texture) { sprite_.setTexture(*texture); }

    // Positioning
    void shift_position(int x, int y);
    void accelerate(float x, float y);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite_, states);
    }
    void update_sprite() {
        sprite_.setPosition(rect_.x_int(), rect_.y_int());
    }
private:
    PhysicsRect rect_;
    sf::Sprite sprite_;
    Timer timer_;
};


#endif //NOVEMBERGAMEJAM_GAMEOBJECT_H
