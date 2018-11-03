#ifndef PROJECT_APP_H
#define PROJECT_APP_H

#include "Logger.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "EventManager.h"

class App {
public:
    explicit App(std::ostream& log_buffer) : logger_("logging/log.txt", log_buffer, 0) {}
    void initialize();
    ~App();
    void run();
private:
    void loop();
    Logger<std::ostream> logger_;
    sf::RenderWindow w;
};


#endif //PROJECT_APP_H
