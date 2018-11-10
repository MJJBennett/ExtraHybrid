#ifndef NOVEMBERGAMEJAM_ACCELERATEPLAYER_H
#define NOVEMBERGAMEJAM_ACCELERATEPLAYER_H

#include "Action.h"

class AcceleratePlayer : public Action<Player> {
public:
    AcceleratePlayer() = delete;

    explicit AcceleratePlayer(ObjectWrapper<Player>& player) : Action(player, "AcceleratePlayer") {}

    bool operator()() override;
};

#endif //NOVEMBERGAMEJAM_ACCELERATEPLAYER_H
