#ifndef NOVEMBERGAMEJAM_ACTION_H
#define NOVEMBERGAMEJAM_ACTION_H

#include "objects/Player.h"
#include "objects/ObjectWrapper.h"

enum class CallType {
    None,
    Basic,
    Full,
    Error,
    Logger,
    Controls
};

class ResourceManager;

class ObjectManager;

class Controls;

template<typename T>
class Logger;

class Action {
public:
    explicit Action(std::string name) : name_(std::move(name)) {}

    std::string get_name() const { return name_; }

    virtual ~Action() = default;

    virtual bool can_execute() { return true; }

    virtual CallType operator()() = 0;

    virtual CallType operator()(ResourceManager *, ObjectManager *) { return CallType::Error; }

    virtual CallType operator()(Logger<std::ostream> *) { return CallType::Error; }

    virtual CallType operator()(Controls *) { return CallType::Error; }

protected:
    std::string name_;
};

template<typename Subject_T>
class SubjectAction : public Action {
public:
    explicit SubjectAction(ObjectWrapper<Subject_T> &subject, std::string name) : Action(std::move(name)),
                                                                                  subject_(subject) {}

    bool can_execute() override { return subject_.get() != nullptr; }

protected:
    ObjectWrapper<Subject_T> &subject_; // This is really not that nice, but it's a 30-day game, so.
};


#endif //NOVEMBERGAMEJAM_ACTION_H
