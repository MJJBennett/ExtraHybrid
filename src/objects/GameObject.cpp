#include "GameObject.h"

void GameObject::shift_position(int x, int y) {
    rect_.x(rect_.x()+x);
    rect_.y(rect_.y()+y);
    update_sprite();
}
