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
#include "coords.h"
#include "cases.h"

using namespace std;
enum TYPE_PIECE
{
Scarabee,Abeille,Fourmi,Sauterelle,Araignee,Moustique,Coccinelle
};
class Piece {
    int x_position;
    int y_position;
    bool camp;
    TYPE_PIECE type_piece;
    friend class Mouvement;
    friend class Case;
    friend class GameManager;
public:
    //Si les pièces sont crées avant d'être mises sur le plateau, elles sont alors toutes placées à un emplacement abérant
    Piece(TYPE_PIECE type,bool c): camp(c), type_piece(type){}
    ~Piece()=default;
    vector<Coords*> coupsPossibles(Graphe graph);
    TYPE_PIECE getType() const {return type_piece;}
    bool getCamp() const { return camp; }
    std::string strPiece() const;
};

#endif //LO21_PIECES_H
