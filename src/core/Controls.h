#ifndef NOVEMBERGAMEJAM_CONTROLS_H
#define NOVEMBERGAMEJAM_CONTROLS_H

#include <objects/Player.h>
#include <functional>
#include "Logger.h"

class Controls {
public:
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

        // Next step: Make operator() pure virtual, then implement actions based on this.

    private:
        void *subject_; // This is really not that nice, but it's a 30-day game, so.
        Type type_;
        std::string name_;
    };

public:
    explicit Controls(Logger<std::ostream>& l) : logger_(l) {}

    bool has(sf::Keyboard::Key key) {
        return actions_.find(key) != actions_.end();
    }

    void set(sf::Keyboard::Key key, Action* action) {
        if (actions_.find(key) != actions_.end()) actions_.erase(key);
        actions_.insert({key, action});
    }

    bool execute(sf::Keyboard::Key key) {
        if (!has(key)) return false;
        logger_.write(Message(actions_.at(key)->get_name()));
        return true;
    }

private:
    Logger<std::ostream>& logger_;

    std::map<sf::Keyboard::Key, Action*> actions_;
};


#endif //NOVEMBERGAMEJAM_CONTROLS_H
