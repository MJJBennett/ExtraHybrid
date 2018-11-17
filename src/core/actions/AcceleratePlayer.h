#ifndef NOVEMBERGAMEJAM_ACCELERATEPLAYER_H
#define NOVEMBERGAMEJAM_ACCELERATEPLAYER_H

#include "Action.h"
#include "tools/PhysUtil.h"

class AcceleratePlayer : public SubjectAction<Player> {
public:
    AcceleratePlayer() = delete;

    explicit AcceleratePlayer(ObjectWrapper<Player> &player, phys::vec2 vec) : SubjectAction(player,
                                                                                             "AcceleratePlayer"),
                                                                               vec_(vec) {}

   CallType release() override;

    CallType operator()() override;

    CallType operator()(ResourceManager *, ObjectManager *) override { return CallType::Error; }

private:
    phys::vec2 vec_;
};

#endif //NOVEMBERGAMEJAM_ACCELERATEPLAYER_H
