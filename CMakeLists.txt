cmake_minimum_required(VERSION 3.20)
project(Projet_Annuel)

set(CMAKE_CXX_STANDARD 14)

include_directories("Library C++")

add_executable(Projet_Annuel
        "Library C++/main.cpp"
        "Library C++/utils_ariel.cpp"
        "Library C++/utils_ariel.h" "Library C++/tools_mamadou.cpp" "Library C++/tools_mamadou.h")
