#ifndef NOVEMBERGAMEJAM_CONTROLS_H
#define NOVEMBERGAMEJAM_CONTROLS_H

#include <objects/Player.h>
#include <functional>
#include "Logger.h"
#include "actions/Action.h"

class Controls {
public:
    explicit Controls(Logger<std::ostream> &l, ResourceManager *r, ObjectManager *o) : logger_(l), r(r), o(o) {}

    // Functions that need to know about the special keys
    // ================================================== actually let's just remove the special keys

    // Executes a function for each action.
    template<class UnaryFunction>
    void for_each_key(UnaryFunction f) {
        for (auto &&ptr : actions_) f(ptr.first);
    }

    std::string nameAt(sf::Keyboard::Key key) {
        if (actions_.find(key) != actions_.end()) return actions_.at(key)->get_name();
        return "Key has no action.";
    }

    bool has(const sf::Keyboard::Key &key) {
        return actions_.find(key) != actions_.end();
    }

    void set(sf::Keyboard::Key key, Action *action) {
        maybe_erase(actions_, key);
        actions_.insert({key, action});
    }

    void rebind(sf::Keyboard::Key original, sf::Keyboard::Key updated);

    bool execute(const sf::Event& event);

    CallType execute_action(Action &action, CallType call_type = CallType::Basic);

    ~Controls() {
        // TODO - Please make these unique_ptrs so that this isn't quite as awful.
        for (auto &&ptr : actions_) delete ptr.second;
    }

    bool give_next_key_to(KeyConsumer* consumer) {
        if (key_consumer_ != nullptr) return false;
        key_consumer_ = consumer;
        return true;
    }

private:
    void maybe_erase(std::map<sf::Keyboard::Key, Action *> &map, sf::Keyboard::Key key) const;

private:
    bool key_released = false;

    Logger<std::ostream> &logger_;

    ResourceManager *r;
    ObjectManager *o;

    std::map<sf::Keyboard::Key, Action *> actions_;

    KeyConsumer* key_consumer_ = nullptr;
};

#endif //NOVEMBERGAMEJAM_CONTROLS_H
