#ifndef NOVEMBERGAMEJAM_ACTION_H
#define NOVEMBERGAMEJAM_ACTION_H

#include "objects/Player.h"
#include "objects/ObjectWrapper.h"

enum class CallType {
    None,
    Basic,
    Full,
    Error,
    Logger
};

class ResourceManager;

class ObjectManager;

template<typename T>
class Logger;

template<typename Subject_T>
class Action {
public:
    explicit Action(ObjectWrapper<Subject_T> &subject, std::string name) : name_(std::move(name)),
                                                                           subject_(subject) {}

    std::string get_name() { return name_; }

    virtual ~Action() = default;

    virtual bool can_execute() { return subject_.get() != nullptr; }

    virtual CallType operator()() = 0;

    virtual CallType operator()(ResourceManager *, ObjectManager *) { return CallType::Error; }

    virtual CallType operator()(Logger<std::ostream> *) { return CallType::Error; }

protected:
    ObjectWrapper<Subject_T> &subject_; // This is really not that nice, but it's a 30-day game, so.
    std::string name_;
};


#endif //NOVEMBERGAMEJAM_ACTION_H
