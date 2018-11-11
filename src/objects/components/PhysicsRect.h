#ifndef NOVEMBERGAMEJAM_PHYSICSRECT_H
#define NOVEMBERGAMEJAM_PHYSICSRECT_H


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

struct Rect {
    float x;
    float y;
    int w;
    int h;
};


class PhysicsRect {
public:
    explicit PhysicsRect(Rect r = Rect{0, 0, 0, 0}) : rect_(r) {}

    float x() { return rect_.x; }
    float y() { return rect_.y; }
    int x_int() { return (int)rect_.x; }
    int y_int() { return (int)rect_.y; }
    void x(float input) { rect_.x = input; }
    void y(float input) { rect_.y = input; }

    float x_velocity() { return x_velocity_; }
    float y_velocity() { return y_velocity_; }
    void x_velocity(float input) { x_velocity_ = input; }
    void y_velocity(float input) { y_velocity_ = input; }

    Rect rect_;
private:
    float x_velocity_ = 0;
    float y_velocity_ = 0;
};


#endif //NOVEMBERGAMEJAM_PHYSICSRECT_H
