#ifndef NOVEMBERGAMEJAM_CONTROLS_H
#define NOVEMBERGAMEJAM_CONTROLS_H

#include <objects/Player.h>
#include <functional>
#include "Logger.h"
#include "actions/Action.h"

class Controls {
public:
    explicit Controls(Logger<std::ostream> &l) : logger_(l) {}

    bool has(sf::Keyboard::Key key) {
        return actions_.find(key) != actions_.end();
    }

    void set(sf::Keyboard::Key key, Action *action) {
        if (actions_.find(key) != actions_.end()) actions_.erase(key);
        actions_.insert({key, action});
    }

    bool execute(sf::Keyboard::Key key) {
        if (!has(key)) return false;
        auto action = actions_.at(key);
        logger_.write(Message("Executing: ", action->get_name()));
        if (!action->can_execute()) {
            logger_.write(Message("Action could not be executed."));
            return false;
        }
        else {
            (*action)();
            return true;
        }
    }

private:
    Logger<std::ostream> &logger_;

    std::map<sf::Keyboard::Key, Action *> actions_;
};


#endif //NOVEMBERGAMEJAM_CONTROLS_H
