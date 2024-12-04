
#include "pieces.h"

std::string Piece::strPiece() const {
    std::string str("");
    switch (getType()) {
        case TYPE_PIECE::Scarabee :
            str.append("Sc");
            break;
        case TYPE_PIECE::Abeille :
            str.append("Ab");
            break;
        case TYPE_PIECE::Fourmi :
            str.append("Fo");
            break;
        case TYPE_PIECE::Sauterelle :
            str.append("Sa");
            break;
        case TYPE_PIECE::Araignee :
            str.append("Ar");
            break;
        case TYPE_PIECE::Moustique :
            str.append("Mo");
            break;
        case TYPE_PIECE::Coccinelle :
            str.append("Co");
            break;
        default :
            throw exception("ERROR Case::showCase : Ce type de piece n'est pas pris en compte.");
    }

    return str;
}