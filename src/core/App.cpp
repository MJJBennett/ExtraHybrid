#include <objects/Player.h>
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
}

void App::run() {
    while (w.isOpen()) loop();
}

void App::loop() {
    sf::Event event{};
    while (w.pollEvent(event)) process_event(event);
    w.clear(sf::Color::Black);
    if (state_.t_draw_resource_manager)
        for (auto &&sprite: r.sprites) w.draw(sprite);
    else
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
    switch (key) {
        case sf::Keyboard::A:
            if (!c.execute(key)) logger_.write(Message("Key A is unbound."));
            return;
        case sf::Keyboard::B:
            logger_.write(Message::key_pressed("B"));
            r.sprites.push_back(r.get_sprite("../resources/Player.1.png"));
            r.sprites.back().setPosition(5 * r.sprites.size(), 60 + 32 * r.sprites.size());
            return;
        case sf::Keyboard::C:
            logger_.write(Message::key_pressed("C"));
            state_.toggle(state_.t_draw_resource_manager);
            return;
        case sf::Keyboard::D: {
            logger_.write(Message::key_pressed("D"));
            GameObject obj(PhysicsRect({5, 10, 15, 20}));
            r.give_sprite(obj, "../resources/Player.1.png");
            o.add_object(obj);
            return;
        }
        case sf::Keyboard::P: {
            logger_.write(Message::key_pressed("P"));
            // This could probably be made to work with shared_ptr
            // But this is much easier.
            auto p = new Player(PhysicsRect({5, 10, 15, 20}));
            r.give_sprite(*p, "../resources/Player.1.png");
            o.add_special(p);
            o.set_player(p);
            return;
        }
        case sf::Keyboard::S: {
            if (c.has(sf::Keyboard::A)) logger_.write(Message("Already set up the keybind."));
            else c.set(sf::Keyboard::A, new AcceleratePlayer(o.get_player()));
            return;
        }
        case sf::Keyboard::Escape:
            // This is beautiful and I won't let you tell me it isn't.
            logger_.write(Message(Message::close(Message::key_pressed("Escape").string())));
            w.close();
            return;
        default:
            return;
    }
}


App::~App() {
    if (w.isOpen()) w.close();
    logger_.write(Message("Closed application."));
}
