cmake_minimum_required(VERSION 3.25)
project(LO21)

set(CMAKE_CXX_STANDARD 17)

add_executable(LO21 main.cpp Pieces.cpp cases.h cases.h coords.h Joueur.cpp plateau.h plateau.cpp cases.cpp pieces.cpp pieces.h legalmoves.cpp legalmoves.h Joueur.h)
