#ifndef NOVEMBERGAMEJAM_PLAYER_H
#define NOVEMBERGAMEJAM_PLAYER_H

#include <objects/components/Health.h>
#include "GameObject.h"

class Player : public GameObject {
public:
    using Health_T = int;
public:
    explicit Player(PhysicsRect rect = PhysicsRect()) : GameObject(rect) {}
    std::optional<Health<Health_T>&> get_health() const override;
private:
    friend class LogPlayer;
    Health<Health_T> health_;
};


#endif //NOVEMBERGAMEJAM_PLAYER_H
