#include "AcceleratePlayer.h"

bool AcceleratePlayer::operator()() {
    subject_->shift_position(5, 0);
    return false;
}
