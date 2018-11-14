#ifndef NOVEMBERGAMEJAM_REBINDKEY_H
#define NOVEMBERGAMEJAM_REBINDKEY_H

#include "Action.h"

class RebindKey : public SubjectAction<Controls>, public KeyConsumer {
public:
    RebindKey() = delete;

    explicit RebindKey(ObjectWrapper<Controls> &controls, Logger<std::ostream> *logger) : SubjectAction(controls,
                                                                                                        "RebindKey"),
                                                                                          logger_(logger) {}

    bool consume_key(sf::Keyboard::Key key) override;

    CallType operator()() override;

private:
    enum class Status {
        None,
        GetKeyToRebind,
        GetNewKey,
    } status_ = Status::None;
    sf::Keyboard::Key old_key_ = sf::Keyboard::Key::Unknown;
    Logger<std::ostream> *logger_;
};


#endif //NOVEMBERGAMEJAM_REBINDKEY_H
