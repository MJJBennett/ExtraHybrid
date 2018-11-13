#include "LogPlayer.h"
#include "Logger.h"

CallType LogPlayer::operator()(Logger<std::ostream> *l) {
    if (auto player = subject_.get(); player == nullptr) l->write(Message("There is currently no player."));
    else {
        l->write(Message("x position: ", player->rect_.x(), " | y position: ", player->rect_.y(),
                         "\nx velocity: ", player->rect_.x_velocity(), " | y velocity: ", player->rect_.y_velocity()));
    }
    return CallType::None;
}
