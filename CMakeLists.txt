cmake_minimum_required(VERSION 3.10)

project(NovemberGameJam)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

include_directories(${CMAKE_SOURCE_DIR}/include/SFML-2.4.2/include/)
link_directories(${CMAKE_SOURCE_DIR}/include/SFML-2.4.2/lib/)

# Add nlohmann/json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(${CMAKE_SOURCE_DIR}/include/json/json)

add_executable(NovemberGameJam
        src/main.cpp
        src/Resource.cpp src/Resource.h
        src/ResourceManager.cpp src/ResourceManager.h
        src/EventManager.h src/EventManager.cpp
        src/Logger.cpp src/Logger.h
        src/App.cpp src/App.h)

if (WIN32)

endif ()
if (UNIX AND NOT APPLE)
    link_directories("/usr/lib/x86_64-linux-gnu/")
    target_link_libraries(NovemberGameJam sfml-window sfml-graphics sfml-system stdc++fs nlohmann_json::nlohmann_json)
endif ()
if (APPLE)
    link_directories("/Users/michael/Programming/ExtraHybrid/include/SFML-2.4.2/lib/")
    target_link_libraries(NovemberGameJam sfml-graphics.dylib sfml-window.dylib sfml-system.dylib stdc++fs nlohmann_json::nlohmann_json)
endif ()
