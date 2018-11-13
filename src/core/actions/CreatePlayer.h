#ifndef NOVEMBERGAMEJAM_CREATEPLAYER_H
#define NOVEMBERGAMEJAM_CREATEPLAYER_H

#include "Action.h"

class CreatePlayer : public SubjectAction<Player> {
public:
    CreatePlayer() = delete;
    explicit CreatePlayer(ObjectWrapper<Player>& player) : SubjectAction(player, "CreatePlayer") {}

    // We can always execute this.
    //...for now.
    bool can_execute() override { return true; }

    CallType operator()() override;
    CallType operator()(ResourceManager* r, ObjectManager* o) override;
};


#endif //NOVEMBERGAMEJAM_CREATEPLAYER_H
