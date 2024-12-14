#include "pieces.h"
#include "legalmoves.h"

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
            throw runtime_error("ERROR Case::showCase : Ce type de piece n'est pas pris en compte.");
    }

    return str;
}

vector<Coords> Piece::coupsPossibles(Graphe graph, Coords coord) const {
    LegalMoveContext* legalmove=&LegalMoveContext::getInstance();
    vector<Coords> b =legalmove->searchLegalMoves(coord,graph,getCamp());
    return b;
}
