project(LoggingTests)

# We are now TDD.
set(CMAKE_CXX_STANDARD 17)

add_executable(LoggingTests test.cpp)
target_link_libraries(LoggingTests stdc++fs nlohmann_json::nlohmann_json)