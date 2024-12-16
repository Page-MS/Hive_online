cmake_minimum_required(VERSION 3.25)
project(LO21)

set(CMAKE_CXX_STANDARD 20)

add_executable(LO21 main.cpp Pieces.cpp cases.h cases.h coords.h plateau.h plateau.cpp cases.cpp pieces.cpp pieces.h legalmoves.cpp legalmoves.h partie.hpp partie.cpp gamemanager.cpp gamemanager.h
        Joueur.cpp
        Joueur.h)
