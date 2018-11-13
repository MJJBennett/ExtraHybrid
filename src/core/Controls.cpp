#include "Controls.h"
#include "tools/Keyboard.h"
#include "tools/MapUtils.h"

bool Controls::execute(sf::Keyboard::Key key) {
    if (config_mode_ == 1) {
        auto t = has(key);
        if (t == ActionType::Error) {
            config_mode_ = 0;
            logger_.write(Message("[Key pressed: ", keyToString(key), "] No action bound to this key."));
            return false; // Can't change the value of this key
        }
        logger_.write(Message("[Key pressed: ", keyToString(key), "] Changing this key, for: ", nameAt(key)));
        config_mode_ = 2;
        config_key_ = key;
        return true;
    }
    if (config_mode_ == 2) {
        auto t = has(config_key_);
        if (t == ActionType::Error) {
            config_mode_ = 0;
            logger_.write(Message("[Key being updated: ", keyToString(config_key_),
                                  "] No action bound to this key anymore."));
            return false; // We lost that key
        }
        if (has(key) != ActionType::Error) {
            logger_.write(Message("[Key pressed: ", keyToString(key), "] This key is already bound to: ", nameAt(key),
                                  ". This action must be rebound first."));
            config_mode_ = 0;
            return false;
        }
        if (key == config_key_) return true; // Did nothing (intentionally)
        logger_.write(Message("[Key pressed: ", keyToString(key), "] This is the new keybind for: ",
                              nameAt(config_key_)));
        config_mode_ = 0;
        switch (t) {
            case ActionType::Player: {
                change_key(player_actions_, config_key_, key);
                return true;
            }
            case ActionType::Window: {
                change_key(window_actions_, config_key_, key);
                return true;
            }
            case ActionType::Special: {
                // Changes the key that changes keys.
                if (config_key_ == config_) config_ = key;
                return true;
            }
            default:
                logger_.write(Message("[Key pressed: ", keyToString(key), "] ...something went wrong."));
                return false; // Not sure what happened here
        }
    }
    if (key == config_) {
        // This will allow rebinding of keys.
        logger_.write(Message("[Key pressed: ", keyToString(key), "] Entering configuration mode.\n",
                              "Enter the key you would like to change."));
        config_mode_ = 1;
        return true;
    }

    ActionType t = has(key);
    logger_.prepend("[Key pressed: " + keyToString(key) + "] ");
    switch (t) {
        case ActionType::Error:
            logger_.clear_prepend();
            return false;
        case ActionType::Player: {
            Action<Player> &action = *(player_actions_.at(key));
            return execute_action(action) != CallType::Error;
        }
        case ActionType::Window: {
            Action<sf::RenderWindow> &action = *(window_actions_.at(key));
            return execute_action(action) != CallType::Error;
        }
    }
}

template<typename T>
CallType Controls::execute_action(Action<T> &action, CallType call_type) {
    // If we want to do nothing, just return.
    if (call_type == CallType::None || call_type == CallType::Error) return call_type;
    // Check if we can execute this action.
    if (!action.can_execute()) {
        logger_.write(Message("Action could not be executed."));
        return CallType::Error;
    }
    // Recursive switch statement.
    switch (call_type) {
        case CallType::Basic:
            logger_.write(Message("Executing: ", action.get_name()));
            return execute_action(action, action());
        case CallType::Full:
            return execute_action(action, action(r, o));
        case CallType::Logger:
            return execute_action(action, action(&logger_));
        default:
            return CallType::Error;
    }
}
