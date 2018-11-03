#include "App.h"

void App::initialize() {
    // Create a directory for logging.
    create_directories("logging");
    // Let the user know we're initializing.
    logger_.write_header();
    logger_.write(Message("Launching application."));

    // Create a window:
    w.create(sf::VideoMode(800, 600), "Example Window");
}

void App::run() {
    while (w.isOpen()) loop();
}

void App::loop() {
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
                        logger_.write(Message("Pressed A"));
                        continue;
                    case sf::Keyboard::Escape:
                        // This is beautiful and I won't let you tell me it isn't.
                        logger_.write(Message(Message::close(Message::key_pressed("Escape").string())));
                        w.close();
                        continue;
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

App::~App() {
    if (w.isOpen()) w.close();
    logger_.write(Message("Closed application."));
}
