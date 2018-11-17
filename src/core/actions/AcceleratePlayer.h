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

    //This is the best solution I can think of for now
    CallType operator()() override { return CallType::Error; }

    CallType operator()(bool released) override;

private:
    phys::vec2 vec_;
};

#endif //NOVEMBERGAMEJAM_ACCELERATEPLAYER_H
