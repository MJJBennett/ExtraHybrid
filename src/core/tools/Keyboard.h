#ifndef NOVEMBERGAMEJAM_KEYBOARD_H
#define NOVEMBERGAMEJAM_KEYBOARD_H

#include <string>
#include <SFML/Window/Keyboard.hpp>

// I did not write this.
// Thank you, BlackHC: https://en.sfml-dev.org/forums/index.php?topic=8458.0
// You are truly a wrist-saver.
std::string keyToString(const sf::Keyboard::Key &key);

#endif //NOVEMBERGAMEJAM_KEYBOARD_H
