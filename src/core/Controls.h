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
        Player,
        Window
    };
public:
    explicit Controls(Logger<std::ostream> &l, ResourceManager* r, ObjectManager* o) : logger_(l), r(r), o(o) {}

    ActionType has(const sf::Keyboard::Key &key) {
        if (player_actions_.find(key) != player_actions_.end()) return ActionType::Player;
        if (window_actions_.find(key) != window_actions_.end()) return ActionType::Window;
        return ActionType::Error;
    }

    void set(sf::Keyboard::Key key, Action<Player> *action) {
        if (player_actions_.find(key) != player_actions_.end()) player_actions_.erase(key);
        player_actions_.insert({key, action});
    }

    void set(sf::Keyboard::Key key, Action<sf::RenderWindow> *action) {
        if (window_actions_.find(key) != window_actions_.end()) player_actions_.erase(key);
        window_actions_.insert({key, action});
    }

    void set_config_key(sf::Keyboard::Key key) { config_ = key; }

    std::string nameAt(sf::Keyboard::Key key) {
        if (window_actions_.find(key) != window_actions_.end()) return window_actions_.at(key)->get_name();
        if (player_actions_.find(key) != player_actions_.end()) return player_actions_.at(key)->get_name();
        return "Key has no action.";
    }

    bool execute(sf::Keyboard::Key key);

    template<typename T>
    CallType execute_action(Action<T>& action, CallType call_type = CallType::Basic);

    ~Controls() {
        for (auto &&ptr : player_actions_) delete ptr.second;
        for (auto &&ptr : window_actions_) delete ptr.second;
    }

private:
    Logger<std::ostream> &logger_;

    ResourceManager* r;
    ObjectManager* o;

    // Special states
    unsigned int config_mode_ = 0;
    sf::Keyboard::Key config_key_ = sf::Keyboard::Key::Unknown;

    // Special keys
    sf::Keyboard::Key config_ = sf::Keyboard::Key::J;

    std::map<sf::Keyboard::Key, Action<Player> *> player_actions_;
    std::map<sf::Keyboard::Key, Action<sf::RenderWindow> *> window_actions_;
};


#endif //NOVEMBERGAMEJAM_CONTROLS_H
