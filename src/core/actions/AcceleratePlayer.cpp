#include "AcceleratePlayer.h"

CallType AcceleratePlayer::operator()() {
    subject_->accelerate(vec_.x, vec_.y);
    return CallType::None;
}

CallType AcceleratePlayer::release() {
    if (vec_.x != 0) subject_->slow_x();
    return CallType::None;
}
