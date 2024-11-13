//
// Created by page on 13/11/2024.
//

#ifndef LO21_LEGALMOVES_H
#define LO21_LEGALMOVES_H
#include "pieces.h"
class LegalMoveContext{
private:
    LegalMoveContext();
    //on supprime l'affectation et la copie
    LegalMoveContext(const LegalMoveContext&) = delete;
    LegalMoveContext& operator=(const LegalMoveContext&) = delete;
public:
    //usage de singleton pour obtenir l'unique instance du legalMoveContext
    static LegalMoveContext& getInstance(){
        LegalMoveContext instance;
        return instance;
    }
    int** searchLegalMoves(TYPE_PIECE typePiece,int x, int y);

};

#endif //LO21_LEGALMOVES_H
