#include <tools/Keyboard.h>
#include "Controls.h"
#include "tools/MapUtils.h"

bool Controls::execute(sf::Keyboard::Key key) {
    if (key_consumer_ != nullptr) {
        // consume_key returns true if they want to consume the next key, too
        // so greedy!
        if (!(key_consumer_->consume_key(key))) {
            // Reset the consumer. We don't need to delete it, we don't own it.
            key_consumer_ = nullptr;
        }
        return true;
    }

    if (has(key)) {
        logger_.prepend("[Key pressed: " + keyToString(key) + "] ");
        auto &action = *(actions_.at(key));
        return execute_action(action) != CallType::Error;
    }
    else {
        return false;
    }
}

CallType Controls::execute_action(Action &action, CallType call_type) {
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
        case CallType::Controls:
            return execute_action(action, action(this));
        default:
            return CallType::Error;
    }
}

void Controls::maybe_erase(std::map<sf::Keyboard::Key, Action *>& map, sf::Keyboard::Key key) const {
    if (map.find(key) != map.end()) {
        // This function is a utility function used for setting keys
        // If this code executes, something very wrong is going on
        logger_.write(Message::warning("Deleting action named " + map.at(key)->get_name() + " due to overwrite."));
        delete map.at(key);
        map.erase(key);
    }
}

void Controls::rebind(sf::Keyboard::Key original, sf::Keyboard::Key updated) {
    change_key(actions_, original, updated);
}

