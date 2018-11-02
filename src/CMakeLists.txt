project(NovemberGameJam)

add_executable(NovemberGameJam main.cpp EventManager.h EventManager.cpp Logger.cpp Logger.h)

link_directories("/usr/lib/x86_64-linux-gnu/")
target_link_libraries(NovemberGameJam sfml-window sfml-graphics sfml-system)