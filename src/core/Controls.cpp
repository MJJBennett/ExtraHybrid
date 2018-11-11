#include "Controls.h"
#include "tools/Keyboard.h"

bool Controls::execute(sf::Keyboard::Key key) {
    if (config_mode_ == 1) {
        if (has(key) == ActionType::Error) return false; // Can't change the value of this key
        logger_.write(Message(Message::key_pressed(keyToString(key)).string(), ". Changing this key, for: ",
                              player_actions_.at(key)->get_name()));
        config_mode_ = 2;
        config_key_ = key;
        return true;
    }
    if (config_mode_ == 2) {
        auto t = has(config_key_);
        if (t == ActionType::Error) return false; // We lost that key
        if (key == config_key_) return true; // Did nothing (intentionally)
        logger_.write(Message(Message::key_pressed(keyToString(key)).string(), ". This is the new keybind for: ",
                              player_actions_.at(config_key_)->get_name()));
        config_mode_ = 0;
        switch (t) {
            case ActionType::Player: {
                // https://en.cppreference.com/w/cpp/container/map/extract
                auto action = player_actions_.extract(config_key_); // Get the value for the original key
                action.key() = key; // Set the new key
                player_actions_.insert(std::move(action));
                return true;
            }
            default:
                return false; // Not sure what happened here
        }
    }
    if (key == config_) {
        // This will allow rebinding of keys.
        logger_.write(Message(Message::key_pressed(keyToString(key)).string(), ": Entering configuration mode.\n",
                              "Enter the key you would like to change."));
        config_mode_ = 1;
        return true;
    }

    ActionType t = has(key);
    switch (t) {
        case ActionType::Error:
            return false;
        case ActionType::Player: {
            Action<Player> &action = *(player_actions_.at(key));
            logger_.write(Message("Executing: ", action.get_name()));
            if (!action.can_execute()) {
                logger_.write(Message("Action could not be executed."));
                return false;
            } else {
                action();
                return true;
            }
        }
    }
}