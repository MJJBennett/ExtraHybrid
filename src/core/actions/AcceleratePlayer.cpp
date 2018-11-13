#include "AcceleratePlayer.h"

CallType AcceleratePlayer::operator()() {
    subject_->accelerate(vec_.x, vec_.y);
    return CallType::None;
}
