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
using namespace std;
class Piece {
    int x_position;
    int y_position;
    friend class Mouvement;
    friend class Case;
    friend class GameManager;
public:
    //le destructeur est virtuel pour permettre la mise en place de classes concrètes
    virtual ~Piece()=default;
    virtual int** coupsPossibles() = 0;
    //le pointeur unique permet d'éviter les problèmes de mémoire
    static Piece* createPiece(int choice);

};

class Abeille : public Piece{
public :
    int** coupsPossibles() override;

};

class Fourmi : public Piece{
public :
    int** coupsPossibles() override;

};

class Scarabee : public Piece{
public :
    int** coupsPossibles() override;

};

class Sauterelle : public Piece{
public :
    int** coupsPossibles() override;

};

class Araignee : public Piece{
public :
    int** coupsPossibles() override;

};

class Moustique : public Piece{
public :
    int** coupsPossibles() override;

};

class Coccinelle : public Piece{
public :
    int** coupsPossibles() override;

};


#endif //LO21_PIECES_H
