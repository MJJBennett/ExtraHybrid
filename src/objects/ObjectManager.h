#ifndef NOVEMBERGAMEJAM_OBJECTMANAGER_H
#define NOVEMBERGAMEJAM_OBJECTMANAGER_H

#include "GameObject.h"
#include "Logger.h"

#include "objects/Player.h"
#include <vector>

class ObjectManager : public sf::Drawable {
public:
    explicit ObjectManager(Logger<std::ostream>& logger) : logger_(logger) {}
    void tick();

    void add_object(GameObject obj) { game_objects_.push_back(std::move(obj)); }

    // Give up ownership of obj to the ObjectManager.
    void add_special(GameObject* obj) { special_objects_.push_back(obj); }

    void set_player(Player* p) {
        if (!p) logger_.write(Message::warning("Set player to nullptr."));
        if (player_ != nullptr) logger_.write(Message::warning("Overwriting player_."));
        player_ = p;
    }

    Player * get_player() const { return player_; }

    ~ObjectManager() override {
        for (auto&& ptr : special_objects_) delete ptr;
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (auto&& obj : game_objects_) target.draw(obj);
        for (auto&& obj : special_objects_) target.draw(*obj);
    }
private:
    std::vector<GameObject> game_objects_;
    std::vector<GameObject*> special_objects_;
    Logger<std::ostream>& logger_;

    Player * player_ = nullptr;
};


#endif //NOVEMBERGAMEJAM_OBJECTMANAGER_H
