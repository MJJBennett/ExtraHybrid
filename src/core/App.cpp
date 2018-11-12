#include <objects/Player.h>
#include <actions/CloseWindow.h>
#include <actions/CreatePlayer.h>
#include "actions/AcceleratePlayer.h"

#include "App.h"

void App::initialize() {
    // Create a directory for logging.
    create_directories("logging");
    // Let the user know we're initializing.
    logger_.write_header();
    logger_.write(Message("Launching application."));
    // Create a window.
    w.create(sf::VideoMode(800, 600), "ExtraHybrid");
    // Preload textures.
    ResourceManager::Multi_Fail status;
    std::string core_resources_file = "../resources/core.json";
    logger_.write(Message("Loading core resources from ", core_resources_file, '.'));
    if (!(status = r.load_from_file(core_resources_file))) {
        logger_.write(Message("Failed to load ", status.num_fails, " thing", status.num_fails > 1 ? "s " : " ",
                              "from core resources file."));
    }

    c.set(sf::Keyboard::Escape, new CloseWindow(window_wrapper_));
    c.set(sf::Keyboard::A, new AcceleratePlayer(o.get_player()));
    c.set(sf::Keyboard::P, new CreatePlayer(o.get_player()));
    // Note: Other default keybinds as follows.
    //  - sf::Keyboard::J - Configuration (change keybinds)
}

void App::run() {
    while (w.isOpen()) loop();
}

void App::loop() {
    sf::Event event{};
    while (w.pollEvent(event)) process_event(event);
    o.tick();
    w.clear(sf::Color::Black);
    w.draw(o);
    w.display();
}

void App::process_event(const sf::Event &event) {
    switch (event.type) {
        case sf::Event::Resized:
            w.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            return;
        case sf::Event::Closed:
            w.close();
            return;
        case sf::Event::KeyReleased:
            process_key_event(event.key.code);
            return;
        default:
            return;
    }
}

void App::process_key_event(const sf::Keyboard::Key &key) {
    c.execute(key);
    //if (!c.execute(key)) logger_.write(Message("Keypress unsuccessful."));
}


App::~App() {
    if (w.isOpen()) w.close();
    logger_.write(Message("Closed application."));
}
