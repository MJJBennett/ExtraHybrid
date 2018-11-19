#include <objects/Player.h>
#include <actions/CloseWindow.h>
#include <actions/CreatePlayer.h>
#include <actions/LogPlayer.h>
#include <actions/PrintHelp.h>
#include <actions/RebindKey.h>
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

    // Meta options
    c.set(sf::Keyboard::Escape, new CloseWindow(window_wrapper_));
    c.set(sf::Keyboard::Num0, new RebindKey(controls_wrapper_, &logger_));
    c.set(sf::Keyboard::L, new LogPlayer(o.get_player()));
    c.set(sf::Keyboard::H, new PrintHelp());

    // Game modification options
    c.set(sf::Keyboard::P, new CreatePlayer(o.get_player()));

    // Actual game functionality
    const float base_acceleration = 40;
    c.set(sf::Keyboard::D, new AcceleratePlayer(o.get_player(), phys::vec2{base_acceleration,0}));
    c.set(sf::Keyboard::W, new AcceleratePlayer(o.get_player(), phys::vec2{0,-base_acceleration*5}));
    c.set(sf::Keyboard::A, new AcceleratePlayer(o.get_player(), phys::vec2{-base_acceleration,0}));
    c.set(sf::Keyboard::S, new AcceleratePlayer(o.get_player(), phys::vec2{0,base_acceleration}));
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
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            c.execute(event);
            return;
        default:
            return;
    }
}

App::~App() {
    if (w.isOpen()) w.close();
    logger_.write(Message("Closed application."));
}
