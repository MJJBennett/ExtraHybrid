#include "Player.h"
#include "Health.h"

std::optional<Health<Player::Health_T>&> Player::get_health() const {
    return health_;
}