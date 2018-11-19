#include "AcceleratePlayer.h"

CallType AcceleratePlayer::operator()(bool released) {
    if (released) {
        if (vec_.x != 0) subject_->slow_x();
    }
    else {
        float acc_y = 0;
        if (vec_.y < 0) {
            if (subject_->get_rect().grounded()) {
                acc_y = vec_.y;
            }
        }
        subject_->accelerate(vec_.x, acc_y);
    }
    return CallType::None;
}