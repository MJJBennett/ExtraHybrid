#ifndef NOVEMBERGAMEJAM_PLAYER_H
#define NOVEMBERGAMEJAM_PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    explicit Player(PhysicsRect rect = PhysicsRect()) : GameObject(rect) {}
};


#endif //NOVEMBERGAMEJAM_PLAYER_H
