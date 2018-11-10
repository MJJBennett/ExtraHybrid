#ifndef NOVEMBERGAMEJAM_CONTROLS_H
#define NOVEMBERGAMEJAM_CONTROLS_H

#include <objects/Player.h>
#include <functional>
#include "Logger.h"
#include "actions/Action.h"

class Controls {
public:
    enum class ActionType {
        Error,
        Player
    };
public:
    explicit Controls(Logger<std::ostream> &l) : logger_(l) {}

    ActionType has(const sf::Keyboard::Key& key) {
        if (player_actions_.find(key) != player_actions_.end()) return ActionType::Player;
        return ActionType::Error;
    }

    void set(sf::Keyboard::Key key, Action<Player>* action) {
        if (player_actions_.find(key) != player_actions_.end()) player_actions_.erase(key);
        player_actions_.insert({key, action});
    }

    bool execute(sf::Keyboard::Key key) {
        ActionType t = has(key);
        switch (t) {
            case ActionType ::Error: return false;
            case ActionType :: Player:
            {
                Action<Player>& action = *(player_actions_.at(key));
                logger_.write(Message("Executing: ", action.get_name()));
                if (!action.can_execute()) {
                    logger_.write(Message("Action could not be executed."));
                    return false;
                }
                else {
                    action();
                    return true;
                }
            }
        }
    }

    ~Controls() {
        for (auto&& ptr : player_actions_) delete ptr.second;
    }

private:
    Logger<std::ostream> &logger_;

    std::map<sf::Keyboard::Key, Action<Player>*> player_actions_;
};


#endif //NOVEMBERGAMEJAM_CONTROLS_H
