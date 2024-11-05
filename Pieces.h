//
// Created by page on 25/10/2024.
//

#ifndef LO21_PIECES_H
#define LO21_PIECES_H
#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>

class Piece {
    int x_position;
    int y_position;
    friend class Mouvement;
    friend class Case;
public:
    int** coupPossibles();

};

class Abeille : public Piece{

};

class Fourmi : public Piece{

};

class Scarabee : public Piece{

};

class Sauterelle : public Piece{

};

class Araignee : public Piece{

};

class Moustique : public Piece{

};

class Coccinelle : public Piece{

};


#endif //LO21_PIECES_H
