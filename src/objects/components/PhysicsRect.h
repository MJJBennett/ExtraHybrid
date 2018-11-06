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

    Rect rect_;
};


#endif //NOVEMBERGAMEJAM_PHYSICSRECT_H
