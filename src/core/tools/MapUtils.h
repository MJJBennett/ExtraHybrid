#ifndef NOVEMBERGAMEJAM_MAPUTILS_H
#define NOVEMBERGAMEJAM_MAPUTILS_H

#include <map>

template<typename key_t, typename value_t>
void change_key(std::map<key_t, value_t>& map, key_t original, key_t after) {
    // https://en.cppreference.com/w/cpp/container/map/extract
    auto wrapper = map.extract(original); // Get the value for the original key
    wrapper.key() = after; // Set the new key
    map.insert(std::move(wrapper));
}

#endif //NOVEMBERGAMEJAM_MAPUTILS_H
