#include "EventManager.h"
#include <SFML/Graphics.hpp>
#include "Logger.h"
#include <iostream>

int main(int argc, char * argv[]) {
    //Create a window
    sf::RenderWindow w(sf::VideoMode(800, 600), "Example Window");
    Logger l("something.txt", ::std::cout);
    l.write(Message("Hi!"));
    l.flush(false);

    //Main loop

    while (w.isOpen()) {

        //Basic event loop
        sf::Event e{};
        while (w.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Resized: w.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
                    continue;
                case sf::Event::Closed:  w.close();
                    continue;
            }
        }

        //Do logical updates here

        w.clear(sf::Color::Black);

        //Draw here with w.draw(//drawable)

        w.display();

    }
    //Ensure the window is closed
    w.close();

}