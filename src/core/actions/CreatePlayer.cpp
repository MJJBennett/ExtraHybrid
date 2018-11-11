#include "CreatePlayer.h"
#include "resources/ResourceManager.h"
#include "objects/ObjectManager.h"

CallType CreatePlayer::operator()() {
    return CallType::Full;
}

CallType CreatePlayer::operator()(ResourceManager* r, ObjectManager* o) {
    auto p = new Player(PhysicsRect({5, 10, 15, 20}));
    r->give_sprite(*p, "../resources/Player.1.png");
    o->add_special(p);
    o->set_player(p);
    return CallType::None;
}
