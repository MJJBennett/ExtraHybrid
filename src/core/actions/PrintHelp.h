#ifndef NOVEMBERGAMEJAM_PRINTHELP_H
#define NOVEMBERGAMEJAM_PRINTHELP_H

#include "Action.h"
#include "Controls.h"
#include <iostream>
#include <functional>

class PrintHelp : public Action {
public:
    PrintHelp() : Action("PrintHelp") {}

    // We can always execute this.
    // Hopefully.
    bool can_execute() override { return true; }

    CallType operator()() override { return CallType::Controls; }

    CallType operator()(Controls* c) override;
private:

};


#endif //NOVEMBERGAMEJAM_PRINTHELP_H
