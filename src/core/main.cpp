#include <iostream>
#include "App.h"

int main(int argc, char *argv[]) {
    App app(std::cout);
    app.initialize();
    app.run();
}
