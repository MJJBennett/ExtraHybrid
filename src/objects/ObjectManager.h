#ifndef NOVEMBERGAMEJAM_OBJECTMANAGER_H
#define NOVEMBERGAMEJAM_OBJECTMANAGER_H

#include "GameObject.h"
#include "Logger.h"

#include <vector>

class ObjectManager : public sf::Drawable {
public:
    explicit ObjectManager(Logger<std::ostream>& logger) : logger_(logger) {}
    void tick();

    void add_object(GameObject obj) { game_objects.push_back(std::move(obj)); }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (auto&& obj : game_objects) target.draw(obj);
    }
private:
    std::vector<GameObject> game_objects;
    Logger<std::ostream>& logger_;
};


#endif //NOVEMBERGAMEJAM_OBJECTMANAGER_H
