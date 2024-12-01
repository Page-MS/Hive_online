
#include "pieces.h"
#include "plateau.cpp"
#include "cases.cpp"
#include "coords.cpp"

int main() {
    try {
    Plateau plateau;

    Piece abeille(TYPE_PIECE::Abeille);
    Piece fourmi(TYPE_PIECE::Fourmi);
    Piece scarabee(TYPE_PIECE::Scarabee);

    plateau.getMutableGraphe().addPiece(abeille, Coords(0, 0));
    plateau.getMutableGraphe().addPiece(fourmi, Coords(1, 1));

    cout<<plateau.getMutableGraphe()<<endl;

    plateau.getMutableGraphe().movePiece(abeille, Coords(0, 2));
    cout<<plateau.getMutableGraphe()<<endl;
    } catch (const exception& e) {
        cout<<e.what()<<endl;
    }

    cout<<"Tout nickel !"<<endl;
    return 0;
}
