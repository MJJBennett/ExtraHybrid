#include "PhysicsManager.h"

void PhysicsManager::update_object(GameObject& obj) {
    auto time = obj.timer_.get().asSeconds(); // Get the amount of time since the last update
    obj.timer_.restart(); // Restart the timer
    auto delta_x = time * obj.rect_.x_velocity();
    auto delta_y = time * obj.rect_.y_velocity();
    if (delta_x != 0 || delta_y != 0)
    {
        obj.rect_.x(obj.rect_.x() + delta_x);
        obj.rect_.y(obj.rect_.y() + delta_y);
        obj.update_sprite();
    }
}
