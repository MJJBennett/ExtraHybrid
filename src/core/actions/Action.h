#ifndef NOVEMBERGAMEJAM_ACTION_H
#define NOVEMBERGAMEJAM_ACTION_H

#include "objects/Player.h"
#include "objects/ObjectWrapper.h"

template<typename Subject_T>
class Action {
public:
    explicit Action(ObjectWrapper<Subject_T>& subject, std::string name) : name_(std::move(name)),
                                                        subject_(subject) {}

    std::string get_name() { return name_; }

    virtual ~Action()=default;

    bool can_execute() { return subject_.get() != nullptr; }

    virtual bool operator()() =0;

protected:
    ObjectWrapper<Subject_T>& subject_; // This is really not that nice, but it's a 30-day game, so.
    std::string name_;
};


#endif //NOVEMBERGAMEJAM_ACTION_H
