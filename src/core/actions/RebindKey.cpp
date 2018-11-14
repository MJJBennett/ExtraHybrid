#include "RebindKey.h"
#include "Controls.h"
#include "Logger.h"
#include "tools/MapUtils.h"
#include "tools/Keyboard.h"

CallType RebindKey::operator()() {
    if (status_ == Status::None) {// This should always be the case unless something very strange happened.
        logger_->write(Message("Entering configuration mode.\n",
                               "Enter the key you would like to change."), true);
        status_ = Status::GetKeyToRebind;
        if (!subject_->give_next_key_to(this)) {
            logger_->write(Message::warning("Potential problem: Can't give the next key to the RebindKey action."));
        }
    } else {
        logger_->write(
                Message::warning("Potential trouble occurred; RebindKey() called while already in key rebind mode."));
    }
    return CallType::None;
}

bool RebindKey::consume_key(sf::Keyboard::Key key) {
    switch (status_) {
        case Status::None: {
            // Error
            return false; // Don't want the next key, believe it or not
        }
        case Status::GetKeyToRebind: {
            if (!(subject_->has(key))) {
                status_ = Status::None;
                logger_->write(Message("[Key pressed: ", keyToString(key), "] No action bound to this key."), true);
                return false; // Can't change the value of this key
            }
            logger_->write(
                    Message("[Key pressed: ", keyToString(key), "] Changing this key, for: ", subject_->nameAt(key)),
                    true);
            status_ = Status::GetNewKey;
            old_key_ = key;
            return true; // We want the next key!
        }
        case Status::GetNewKey: {
            // We always want to reset here
            status_ = Status::None;

            // If the old key somehow doesn't have an action, we don't want to rebind it
            if (!(subject_->has(old_key_))) {
                logger_->write(Message("[Key being updated: ", keyToString(old_key_),
                                       "] No action bound to this key anymore."), true);
                return false; // We lost that key
            }
            // If the new key is already bound, we don't want to risk 'losing' an action (for now)
            if (subject_->has(key)) {
                logger_->write(Message("[Key pressed: ", keyToString(key), "] This key is already bound to: ",
                                       subject_->nameAt(key),
                                       ". This action must be rebound first."), true);
                return false;
            }
            // If the keys are the same, we don't have to do anything
            if (key == old_key_) return false;
            logger_->write(Message("[Key pressed: ", keyToString(key), "] This is the new keybind for: ",
                                   subject_->nameAt(old_key_)), true);
            subject_->rebind(old_key_, key);
            return false;
        }
    }
}
