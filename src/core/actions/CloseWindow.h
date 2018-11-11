#ifndef NOVEMBERGAMEJAM_CLOSEWINDOW_H
#define NOVEMBERGAMEJAM_CLOSEWINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Action.h"

class CloseWindow : public Action<sf::RenderWindow> {
public:
    CloseWindow() = delete;

    explicit CloseWindow(ObjectWrapper<sf::RenderWindow>& window) : Action(window, "CloseWindow") {}

    CallType operator()() override;
    CallType operator()(ResourceManager*, ObjectManager*) override { return CallType::Error; }
private:

};


#endif //NOVEMBERGAMEJAM_CLOSEWINDOW_H
