#ifndef NOVEMBERGAMEJAM_PHYSICSRECT_H
#define NOVEMBERGAMEJAM_PHYSICSRECT_H


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

struct Rect {
    int x;
    int y;
    int w;
    int h;
};


class PhysicsRect {
public:
    explicit PhysicsRect(Rect r = Rect{0, 0, 0, 0}) : rect_(r) {}

    int x() { return rect_.x; }
    int y() { return rect_.y; }
    void x(int input) { rect_.x = input; }
    void y(int input) { rect_.y = input; }

    Rect rect_;
};


#endif //NOVEMBERGAMEJAM_PHYSICSRECT_H
