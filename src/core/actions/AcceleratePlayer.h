#ifndef NOVEMBERGAMEJAM_ACCELERATEPLAYER_H
#define NOVEMBERGAMEJAM_ACCELERATEPLAYER_H

#include "Action.h"

class AcceleratePlayer : public Action<Player> {
public:
    AcceleratePlayer() = delete;

    explicit AcceleratePlayer(ObjectWrapper<Player>& player) : Action(player, "AcceleratePlayer") {}

    CallType operator()() override;
    CallType operator()(ResourceManager*, ObjectManager*) override { return CallType::Error; }
};

#endif //NOVEMBERGAMEJAM_ACCELERATEPLAYER_H
