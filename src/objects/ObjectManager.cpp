#include "ObjectManager.h"

void ObjectManager::tick() {
    for (auto &&obj : game_objects_) {
        PhysicsManager::update_object(obj);
    }
    for (auto &&obj : special_objects_) {
        PhysicsManager::update_object(*obj);
    }
}
