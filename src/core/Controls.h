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

    ActionType has(const sf::Keyboard::Key &key) {
        if (player_actions_.find(key) != player_actions_.end()) return ActionType::Player;
        return ActionType::Error;
    }

    void set(sf::Keyboard::Key key, Action<Player> *action) {
        if (player_actions_.find(key) != player_actions_.end()) player_actions_.erase(key);
        player_actions_.insert({key, action});
    }

    bool execute(sf::Keyboard::Key key);

    ~Controls() {
        for (auto &&ptr : player_actions_) delete ptr.second;
    }

private:
    Logger<std::ostream> &logger_;

    // Special states
    unsigned int config_mode_ = 0;
    sf::Keyboard::Key config_key_ = sf::Keyboard::Key::Unknown;

    // Special keys
    sf::Keyboard::Key config_ = sf::Keyboard::Key::J;

    std::map<sf::Keyboard::Key, Action<Player> *> player_actions_;
};


#endif //NOVEMBERGAMEJAM_CONTROLS_H
