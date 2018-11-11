#include "GameObject.h"
#include "PhysicsManager.h"

void GameObject::shift_position(int x, int y) {
    rect_.x(rect_.x()+x);
    rect_.y(rect_.y()+y);
    update_sprite();
}

void GameObject::accelerate(float x, float y) {
    // First, make sure our position is up to date
    PhysicsManager::update_object(*this);
    // Now we can increase our velocity, the timer was just restarted
    rect_.x_velocity(rect_.x_velocity() + x);
    rect_.y_velocity(rect_.y_velocity() + y);
}