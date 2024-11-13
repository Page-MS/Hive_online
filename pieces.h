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
enum TYPE_PIECE
{
Scarabee,Abeille,Fourmi,Sauterelle, Araignee, Moustique, Coccinelle
};
class Piece {
    int x_position;
    int y_position;
    TYPE_PIECE typePiece;
    friend class Mouvement;
    friend class Case;
    friend class GameManager;
public:
    //Si les pièces sont crées avant d'être mises sur le plateau, elles sont alors toutes placées à un emplacement abérant
    Piece(TYPE_PIECE type,int x=-100, int y=-100): x_position(x), y_position(y), typePiece(type){}
    ~Piece()=default;
    int** coupsPossibles();
    TYPE_PIECE get_type(){return typePiece;}

};

#endif //LO21_PIECES_H
