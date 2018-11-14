#include "PrintHelp.h"
#include <tools/Keyboard.h>

CallType PrintHelp::operator()(Controls *c) {
    c->for_each_key([&](sf::Keyboard::Key key) {
        std::cout << "Key " << keyToString(key) << " is bound to " << c->nameAt(key) << ".\n";
    });
    std::cout << std::flush;
    return CallType::None;
}