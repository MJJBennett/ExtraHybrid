#ifndef NOVEMBERGAMEJAM_CONTROLS_H
#define NOVEMBERGAMEJAM_CONTROLS_H

#include <objects/Player.h>
#include <functional>
#include "Logger.h"
#include "actions/Action.h"

class Controls {
public:
    enum class ActionType {
        Error, // The action doesn't exist or some other error
        Normal, // The action is contained in player_actions_
        Special, // The action is not in storage at all
    };
public:
    explicit Controls(Logger<std::ostream> &l, ResourceManager *r, ObjectManager *o) : logger_(l), r(r), o(o) {}

    ActionType has(const sf::Keyboard::Key &key) {
        if (actions_.find(key) != actions_.end()) return ActionType::Normal;
        if (config_ == key) return ActionType::Special;
        return ActionType::Error;
    }

    // Executes a function for each action
    // Doesn't seem to work for some reason so I'm leaving it for now
    template<class UnaryFunction>
    static void for_each(Controls* c, UnaryFunction f) {
        for (auto &&ptr : c->actions_) f(ptr.first);
    }


    void set(sf::Keyboard::Key key, Action *action) {
        maybe_erase(actions_, key);
        actions_.insert({key, action});
    }

    void set_config_key(sf::Keyboard::Key key) { config_ = key; }

    std::string nameAt(sf::Keyboard::Key key) {
        if (actions_.find(key) != actions_.end()) return actions_.at(key)->get_name();
        if (key == config_) return "KeybindConfiguration";
        return "Key has no action.";
    }

    bool execute(sf::Keyboard::Key key);

    CallType execute_action(Action &action, CallType call_type = CallType::Basic);

    ~Controls() {
        // TODO - Please make these unique_ptrs so that this isn't quite as awful.
        for (auto &&ptr : actions_) delete ptr.second;
    }

private:
    void maybe_erase(std::map<sf::Keyboard::Key, Action *> &map, sf::Keyboard::Key key) const;

private:

    Logger<std::ostream> &logger_;

    ResourceManager *r;
    ObjectManager *o;

    // Special states
    unsigned int config_mode_ = 0;
    sf::Keyboard::Key config_key_ = sf::Keyboard::Key::Unknown;

    // Special keys
    sf::Keyboard::Key config_ = sf::Keyboard::Key::J;

    std::map<sf::Keyboard::Key, Action *> actions_;
};

#endif //NOVEMBERGAMEJAM_CONTROLS_H
