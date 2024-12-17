cmake_minimum_required(VERSION 3.25)
project(LO21)

set(CMAKE_CXX_STANDARD 20)

add_executable(LO21 main.cpp pieces.cpp cases.h cases.h coords.h plateau.h plateau.cpp cases.cpp coords.cpp pieces.cpp pieces.h legalmoves.cpp legalmoves.h partie.hpp partie.cpp
        Joueur.cpp
        Joueur.h)
