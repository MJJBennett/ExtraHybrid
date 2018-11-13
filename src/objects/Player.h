#ifndef NOVEMBERGAMEJAM_PLAYER_H
#define NOVEMBERGAMEJAM_PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    explicit Player(PhysicsRect rect = PhysicsRect()) : GameObject(rect) {}
private:
    friend class LogPlayer;
};


#endif //NOVEMBERGAMEJAM_PLAYER_H
