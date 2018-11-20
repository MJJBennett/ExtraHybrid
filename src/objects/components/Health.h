#ifndef NOVEMBERGAMEJAM_HEALTH_H
#define NOVEMBERGAMEJAM_HEALTH_H

#include <type_traits>

template<typename Num_T>
class Health {
    static_assert(std::is_arithmetic<Num_T>::value, "Health must be templated with a numeric type.");
public:
    Health() = default;

    explicit Health(Num_T initial_health) : health_(initial_health) {}

    Num_T get() { return health_; }

    void set(Num_T new_health) { health_ = new_health; }

    Num_T damage(Num_T damage) {
        health_ -= damage;
        return health_;
    }

    Num_T heal(Num_T heal) {
        health_ += heal;
        return health_;
    }

private:
    Num_T health_ = 0;
};


#endif //NOVEMBERGAMEJAM_HEALTH_H
