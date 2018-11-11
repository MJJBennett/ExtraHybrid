#include "AcceleratePlayer.h"

bool AcceleratePlayer::operator()() {
    subject_->accelerate(5, 0);
    return false;
}
