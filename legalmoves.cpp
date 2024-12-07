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
            current_strategy=Abeille;
        } else if (typePiece == Fourmi) {
            strategy = new LegalMoveFourmi();
            current_strategy=Fourmi;
        } else if (typePiece == Scarabee) {
            strategy = new LegalMoveScarabee();
            current_strategy=Scarabee;
        } else if (typePiece == Sauterelle) {
            strategy = new LegalMoveSauterelle();
            current_strategy=Sauterelle;
        } else if (typePiece == Araignee) {
            strategy = new LegalMoveAraignee();
            current_strategy=Araignee;
        } else if (typePiece == Moustique) {
            strategy = new LegalMoveMoustique();
            current_strategy=Moustique;
        } else if (typePiece == Coccinelle) {
            strategy = new LegalMoveCoccinelle();
            current_strategy=Coccinelle;
        } else {
            std::cout << "Attention choix de piece invalide";
            strategy = nullptr;
        }
    }



vector<Coords > LegalMoveContext::searchLegalMoves(Coords coord, Graphe graph, bool camp) {
    changeStrategy(graph.getCase(coord).getUpperPiece().getType());
    vector<Coords> result=strategy->searchMoves(coord,graph,camp);
    if (result.empty()){
        cout<<"\n pas de resultat\n";
        }
    return result;
}

vector<Coords> LegalMoveAbeille::searchMoves(Coords coord,Graphe graph, bool camp) {
    graphe_avant_coup=graph;
    graphe_a_manipuler=graph;
    vector<Coords> resultat;
    if(graphe_a_manipuler.wouldHiveBreak(coord)){
        cout<<"\nNe peut pas bouger sans casser la hive";
        return resultat;
    }
    vector<Coords> voisins=graphe_a_manipuler.coordsAllAdjacents(coord);
    for(auto i:voisins){
        if (graphe_a_manipuler.getCase(i).empty()){
            resultat.push_back(i);
            cout<<"\n On ajoute :"<<i.getX()<<":"<<i.getY();
        }
    }
    return resultat;
};

vector<Coords> LegalMoveScarabee::searchMoves(Coords coord,Graphe graph, bool campvector){
        graphe_avant_coup=graph;
        graphe_a_manipuler=graph;
        vector<Coords> resultat;
        if(graphe_a_manipuler.getCase(coord).getNbPieces()<=1){
            if(graphe_a_manipuler.wouldHiveBreak(coord)){
                cout<<"\nNe peut pas bouger sans casser la hive";
                return resultat;
            }
        }
        vector<Coords> voisins=graphe_a_manipuler.coordsAllAdjacents(coord);
        for(auto i:voisins){
                resultat.push_back(i);
                cout<<"\n On ajoute :"<<i.getX()<<":"<<i.getY();
        }
        return resultat;

    }

