#include "AcceleratePlayer.h"

bool AcceleratePlayer::operator()() {
    ((Player*)subject_)->shift_position(5, 0);
    return false;
}
