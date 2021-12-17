cmake_minimum_required(VERSION 3.20)
project(Projet_avion)

set(CMAKE_CXX_STANDARD 17)

find_package (Threads)
find_package(SFML 2 COMPONENTS graphics window network system)

add_executable(Projet_avion main.cpp controleurs/avion.cpp controleurs/struct.cpp controleurs/aeroport.cpp controleurs/ccr.cpp controleurs/tourDeControle.cpp)

target_compile_features(Projet_avion PUBLIC cxx_std_17)
target_link_libraries (Projet_avion Threads::Threads)
target_link_libraries (Projet_avion sfml-graphics sfml-window)
