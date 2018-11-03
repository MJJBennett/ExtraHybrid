#include "EventManager.h"
#include <SFML/Graphics.hpp>
#include "Logger.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    // Create a directory for logging
    create_directories("logging");
    // Create a logger
    Logger l("logging/log.txt", ::std::cout, 0);
    // Let the user know we're initializing
    l.write_header();
    l.write(Message("Launching application."));

    // Create a window
    sf::RenderWindow w(sf::VideoMode(800, 600), "Example Window");

    while (w.isOpen()) {
        sf::Event event{};
        while (w.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Resized:
                    w.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    continue;
                case sf::Event::Closed:
                    w.close();
                    continue;
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                        case sf::Keyboard::A:
                            l.write(Message("Pressed A"));
                        default:
                            continue;
                    }
                default:
                    continue;
            }
        }
        w.clear(sf::Color::Black);
        w.display();
    }
    w.close();
}
