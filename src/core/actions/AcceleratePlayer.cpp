#include "AcceleratePlayer.h"

CallType AcceleratePlayer::operator()() {
    subject_->accelerate(5, 0);
    return CallType::None;
}
