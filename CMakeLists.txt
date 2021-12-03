cmake_minimum_required(VERSION 3.20)
project(Projet_avion)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projet_avion main.cpp avion.cpp struct.cpp aeroport.cpp ccr.cpp)
find_package (Threads)

target_compile_features(Projet_avion PUBLIC cxx_std_17)
target_link_libraries (Projet_avion Threads::Threads)
