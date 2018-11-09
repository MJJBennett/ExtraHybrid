#ifndef NOVEMBERGAMEJAM_ACTION_H
#define NOVEMBERGAMEJAM_ACTION_H

#include "objects/Player.h"

class Action {
public:
    enum class Type {
        GameObject,
        Player,
        ObjectManager,
        None
    };
public:
    explicit Action(Player *player, std::string name) : type_(Type::Player), name_(std::move(name)),
                                                        subject_(player) {}
    explicit Action(nullptr_t, std::string name) : type_(Type::None), name_(std::move(name)),
                                                   subject_(nullptr) {}

    std::string get_name() { return name_; }

    bool can_execute() { return subject_ != nullptr; }

    virtual bool operator()() =0;

    // Next step: Make operator() pure virtual, then implement actions based on this.

protected:
    void *subject_; // This is really not that nice, but it's a 30-day game, so.
    Type type_;
    std::string name_;
};


#endif //NOVEMBERGAMEJAM_ACTION_H
