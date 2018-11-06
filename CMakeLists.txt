cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(NovemberGameJam)


# Our directories
include_directories(${CMAKE_SOURCE_DIR}/src/core/)
include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/src/objects/components)
# SFML directories
include_directories(${CMAKE_SOURCE_DIR}/include/SFML-2.4.2/include/)
link_directories(${CMAKE_SOURCE_DIR}/include/SFML-2.4.2/lib/)
# JSON directories
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(${CMAKE_SOURCE_DIR}/include/json/json)

# Testing directories.
if (BUILD_TEST)
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/tests/tests_core/tests_logging)
endif (BUILD_TEST)

# C++ compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

# Build the full project.
add_executable(NovemberGameJam
        # Core code
        src/core/main.cpp
        src/core/Logger.cpp src/core/Logger.h
        src/core/App.cpp src/core/App.h
        # Resource / resource management
        src/resources/Resource.cpp src/resources/Resource.h
        src/resources/ResourceManager.cpp src/resources/ResourceManager.h
        # Game objects
        src/objects/GameObject.cpp src/objects/GameObject.h
        src/objects/components/PhysicsRect.cpp src/objects/components/PhysicsRect.h
        src/objects/ObjectManager.cpp src/objects/ObjectManager.h
        src/objects/Player.cpp src/objects/Player.h)

# Link the project (system dependant)
if (WIN32)
    # No building on Windows yet.
endif ()
if (UNIX AND NOT APPLE)
    link_directories("/usr/lib/x86_64-linux-gnu/")
    target_link_libraries(NovemberGameJam sfml-window sfml-graphics sfml-system stdc++fs nlohmann_json::nlohmann_json)
endif ()
if (APPLE)
    # The compiler & SFML must match - however, the hard-to-avoid mac default is clang
    # which unfortunately appears to be VERY difficult to get to support C++17
    # maybe I'll figure it out some time
    link_directories("/Users/michael/Programming/ExtraHybrid/include/SFML-2.4.2/lib/")
    target_link_libraries(NovemberGameJam sfml-graphics.dylib sfml-window.dylib sfml-system.dylib stdc++fs nlohmann_json::nlohmann_json)
endif ()
