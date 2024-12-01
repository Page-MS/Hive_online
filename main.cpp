
#include "pieces.h"
#include "plateau.cpp"
#include "cases.cpp"
#include "coords.cpp"

int main() {
    try {
    Plateau plateau;
    Graphe& g = plateau.getMutableGraphe();

    Piece abeille(TYPE_PIECE::Abeille);
    Piece fourmi(TYPE_PIECE::Fourmi);
    Piece scarabee(TYPE_PIECE::Scarabee);

    cout<<"---- ADD PIECE ----\n";
    g.addPiece(abeille, Coords(0, 0));
    g.addPiece(fourmi, Coords(0, 2));


    cout<<"\n---- AFFICHAGE ----\n";
    cout<<g<<endl;

    cout<<"---- DELETE THEN ADD Fourmi ----"<<endl;
    g.supprPiece(Coords(0, 2));
    g.addPiece(fourmi, Coords(0, 2));

    cout<<"\n---- AFFICHAGE ----\n";
    cout<<g<<endl;

    cout<<"---- MOVE PIECE FOURMI TO (0, 0) ----\n";
    g.movePiece(fourmi, Coords(0, 0));
    cout<<"\n---- AFFICHAGE ----\n";
    cout<<g<<endl;

    cout<<"---- MOVE PIECE FOURMI TO (1, 1) ----\n";
    g.movePiece(fourmi, Coords(1, 1));
    cout<<"\n---- AFFICHAGE ----\n";
    cout<<g<<endl;

    const Case& ca = g.getCase(0, 0);

    cout<<"Case has piece fourmi : "<<ca.hasPiece(fourmi);

    } catch (const exception& e) {
        cout<<e.what()<<endl;
    }

    cout<<"\n\nTout nickel !"<<endl;
    return 0;
}
