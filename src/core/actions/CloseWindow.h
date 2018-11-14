#ifndef NOVEMBERGAMEJAM_CLOSEWINDOW_H
#define NOVEMBERGAMEJAM_CLOSEWINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Action.h"

class CloseWindow : public SubjectAction<sf::RenderWindow> {
public:
    CloseWindow() = delete;

    explicit CloseWindow(ObjectWrapper<sf::RenderWindow>& window) : SubjectAction(window, "CloseWindow") {}

    CallType operator()() override;
private:

};


#endif //NOVEMBERGAMEJAM_CLOSEWINDOW_H
