#include "AcceleratePlayer.h"

CallType AcceleratePlayer::operator()(bool released) {
    if (released) {
        if (vec_.x != 0) subject_->slow_x();
    }
    else subject_->accelerate(vec_.x, vec_.y);
    return CallType::None;
}