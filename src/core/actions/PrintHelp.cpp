#include "PrintHelp.h"
#include <tools/Keyboard.h>

CallType PrintHelp::operator()(Controls *c) {
    const auto print_keybind = [&](sf::Keyboard::Key key) {
        std::cout << "Key " << keyToString(key) << " is bound to " << c->nameAt(key) << ".\n";
    };
    Controls::for_each(c, print_keybind);
    std::cout << std::flush;
    return CallType::None;
}