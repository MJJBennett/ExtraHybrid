#ifndef NOVEMBERGAMEJAM_LOGPLAYER_H
#define NOVEMBERGAMEJAM_LOGPLAYER_H

#include "Action.h"

class LogPlayer : public Action<Player> {
public:
    LogPlayer() = delete;
    explicit LogPlayer(ObjectWrapper<Player>& player) : Action(player, "LogPlayer") {}

    // We can always execute this.
    //...for now.
    bool can_execute() override { return true; }

    CallType operator()() override { return CallType::Logger; }
    // This should never be called
    CallType operator()(ResourceManager* r, ObjectManager* o) override { return CallType::Error; }
    CallType operator()(Logger<std::ostream>* l) override;
private:

};


#endif //NOVEMBERGAMEJAM_LOGPLAYER_H
