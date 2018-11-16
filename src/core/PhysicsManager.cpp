#include "PhysicsManager.h"

void PhysicsManager::update_object(GameObject& obj) {
    // Sort of temporary until this interacts with the world properly.
    const struct {
        int x_min = 0;
        int x_max = 500;
        int y_min = 0;
        int y_max = 500;
        int y_max_vel = 100;
        int x_max_vel = 80;
    } bounds;
    const float y_acceleration = 25;

    auto time = obj.timer_.get().asSeconds(); // Get the amount of time since the last update
    obj.timer_.restart(); // Restart the timer

    // Calculate physics update information
    auto delta_x = time * obj.rect_.x_velocity();
    auto delta_y = time * obj.rect_.y_velocity();

    if (delta_x != 0 || delta_y != 0)
    {
        auto new_x = obj.rect_.x() + delta_x;
        auto new_y = obj.rect_.y() + delta_y;

        // Validate the new values
        if (new_x < bounds.x_min) {
            // We hit the boundary, stop the player & don't move him.
            new_x = bounds.x_min;
            obj.rect_.x_velocity(0);
        } else if (new_x + obj.rect_.rect_.w > bounds.x_max) {
            new_x = bounds.x_max - obj.rect_.rect_.w;
            obj.rect_.x_velocity(0);
        }

        if (new_y < bounds.y_min) {
            new_y = bounds.y_min;
            obj.rect_.y_velocity(0);
        } else if (new_y + obj.rect_.rect_.h > bounds.y_max) {
            new_y = bounds.y_max - obj.rect_.rect_.h;
            obj.rect_.y_velocity(0);
        }

        obj.rect_.x(new_x);
        obj.rect_.y(new_y);
        obj.update_sprite();
    }

    // Now we update the velocity based on gravity

    // First update the x velocity
    if (std::abs(obj.rect_.x_velocity()) > bounds.x_max_vel) {
        obj.rect_.x_velocity(obj.rect_.x_velocity()>0? bounds.x_max_vel : bounds.x_max_vel * -1);
    }

    // Now the y velocity
    auto new_y_vel = obj.rect_.y_velocity() + y_acceleration * time;
    if (std::abs(new_y_vel) > bounds.y_max_vel) {
        obj.rect_.y_velocity(new_y_vel > 0? bounds.y_max_vel : bounds.y_max_vel*-1);
    }
    else obj.rect_.y_velocity(new_y_vel);
}
