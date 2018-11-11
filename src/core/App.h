#ifndef PROJECT_APP_H
#define PROJECT_APP_H

#include "Logger.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../resources/ResourceManager.h"
#include "objects/ObjectManager.h"
#include "Controls.h"
#include "objects/ObjectWrapper.h"

struct State {
    bool toggle(bool &var) {
        var = !var;
        return var;
    }

    bool t_draw_resource_manager = false;
};

class App {
public:
    explicit App(std::ostream &log_buffer) : logger_("logging/log.txt", log_buffer, 0), r(logger_), o(logger_, r),
                                             c(logger_, &r, &o), window_wrapper_(&w) {}

    ~App();

    // Large application initialization process.
    void initialize();

    // Run the application.
    void run();

private:
    // Run 1 frame of the game.
    void loop();

    void process_event(const sf::Event &event);

    void process_key_event(const sf::Keyboard::Key &key);

private:
    // Private member variables.
    Logger<std::ostream> logger_;
    ObjectManager o;
    sf::RenderWindow w;
    ObjectWrapper<sf::RenderWindow> window_wrapper_;
    ResourceManager r;
    Controls c;

    State state_;
};


#endif //PROJECT_APP_H
