//
// Created by page on 13/11/2024.
//

#include "legalmoves.h"

void LegalMoveContext::changeStrategy(TYPE_PIECE typePiece) {
    //si la strategie à appliquer est la même, on ne la change pas
        if (strategy != nullptr) {
            cout<<"\nOn suppprime la strategie";
            delete strategy;
        }
        if (typePiece == Abeille) {
            strategy = new LegalMoveAbeille();
        } else if (typePiece == Fourmi) {
            strategy = new LegalMoveFourmi();
        } else if (typePiece == Scarabee) {
            strategy = new LegalMoveScarabee();
        } else if (typePiece == Sauterelle) {
            strategy = new LegalMoveSauterelle();
        } else if (typePiece == Araignee) {
            strategy = new LegalMoveAraignee();
        } else if (typePiece == Moustique) {
            strategy = new LegalMoveMoustique();
        } else if (typePiece == Coccinelle) {
            strategy = new LegalMoveCoccinelle();
        } else {
            std::cout << "Attention choix de piece invalide";
            strategy = nullptr;
        }
    }



vector<Coords > LegalMoveContext::searchLegalMoves(Coords coord, Graphe graph, bool camp) {
    changeStrategy(graph.getCase(coord).getUpperPiece().getType());
    vector<Coords> result=strategy->searchMoves(coord,graph,camp);
    if (result.empty()){
        cout<<"\n Oh non le gros nullos\n";
        }
    return result;
}
