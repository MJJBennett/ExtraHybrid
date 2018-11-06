#ifndef NOVEMBERGAMEJAM_OBJECTMANAGER_H
#define NOVEMBERGAMEJAM_OBJECTMANAGER_H

#include "GameObject.h"
#include "Logger.h"

#include <vector>

class ObjectManager {
    explicit ObjectManager(Logger<std::ostream>& logger) : logger_(logger) {}
    void tick();
private:
    std::vector<GameObject> game_objects;
    Logger<std::ostream>& logger_;
};


#endif //NOVEMBERGAMEJAM_OBJECTMANAGER_H
