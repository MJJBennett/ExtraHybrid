cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include/SFML-2.4.2/include/)
link_directories(${CMAKE_SOURCE_DIR}/include/SFML-2.4.2/lib/)

add_subdirectory(src)
