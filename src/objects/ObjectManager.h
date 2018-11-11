#ifndef NOVEMBERGAMEJAM_OBJECTMANAGER_H
#define NOVEMBERGAMEJAM_OBJECTMANAGER_H

#include "GameObject.h"
#include "Logger.h"

#include "objects/Player.h"
#include <vector>
#include "objects/ObjectWrapper.h"
#include "PhysicsManager.h"

class ObjectManager : public sf::Drawable {
    friend class PhysicsManager;
public:
    explicit ObjectManager(Logger<std::ostream> &logger) : logger_(logger) {}

    void tick();

    void add_object(GameObject obj) { game_objects_.push_back(std::move(obj)); }

    // Give up ownership of obj to the ObjectManager.
    void add_special(GameObject *obj) { special_objects_.push_back(obj); }

    void set_player(Player *p) {
        if (!p) logger_.write(Message::warning("Set player to nullptr."));
        if (player_.get() != nullptr) logger_.write(Message::warning("Overwriting player_."));
        player_.update(p);
    }

    ObjectWrapper<Player>& get_player() { return player_; }

    Player* get_current_player() const { return player_.get(); }

    ~ObjectManager() override {
        for (auto &&ptr : special_objects_) delete ptr;
    }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        for (auto &&obj : game_objects_) target.draw(obj);
        for (auto &&obj : special_objects_) target.draw(*obj);
    }

private:
    std::vector<GameObject> game_objects_;
    std::vector<GameObject *> special_objects_;
    Logger<std::ostream> &logger_;

    ObjectWrapper<Player> player_;
};


#endif //NOVEMBERGAMEJAM_OBJECTMANAGER_H
