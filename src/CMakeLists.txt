project(NovemberGameJam)

add_executable(NovemberGameJam main.cpp EventManager.h EventManager.cpp Logger.cpp Logger.h)

if (WIN32)
    
endif()
if (UNIX AND NOT APPLE)
link_directories("/usr/lib/x86_64-linux-gnu/")
target_link_libraries(NovemberGameJam sfml-window sfml-graphics sfml-system)
endif()
if (APPLE)
link_directories("/Users/michael/Programming/ExtraHybrid/include/SFML-2.4.2/lib/")
target_link_libraries(NovemberGameJam sfml-graphics.dylib sfml-window.dylib sfml-system.dylib)
endif()
