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
    vector<Coords> voisins=graphe_a_manipuler.coordsExistentAdjacents(coord);
    int cote_voisin=0;
    for(auto i:voisins){
        if (graphe_a_manipuler.getCase(i).empty() and graphe_a_manipuler.canSlide(coord,cote_voisin)){
            resultat.push_back(i);
            cout<<"\n On ajoute :"<<i.getX()<<":"<<i.getY();
            cote_voisin++;
        }
    }
    return resultat;
}

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
        vector<Coords> voisins=graphe_a_manipuler.coordsExistentAdjacents(coord);
        for(auto i:voisins){
                resultat.push_back(i);
                cout<<"\n On ajoute :"<<i.getX()<<":"<<i.getY();
        }
        return resultat;

    }


vector<Coords> LegalMoveAraignee::searchMoves(Coords coord,Graphe graph, bool camp){
    graphe_avant_coup=graph;
    graphe_a_manipuler=graph;
    vector<Coords> resultat;
    if(graphe_a_manipuler.wouldHiveBreak(coord)){
        cout<<"\nNe peut pas bouger sans casser la hive";
        return resultat;
    }
    resultat= rechercheDansVoisins(coord,graph,camp,0);

    return resultat;

}

vector<Coords> LegalMoveAraignee::rechercheDansVoisins(Coords coord, Graphe graph, bool camp,unsigned int profondeur) const {
    vector<Coords> resultat;
    vector<Coords> voisins=graphe_a_manipuler.coordsExistentAdjacents(coord);
    profondeur++;
    unsigned int cote_voisin=0;
    if (profondeur<3){
    for(auto i:voisins) {
        if (graphe_a_manipuler.getCase(i).empty() and graphe_a_manipuler.canSlide(coord, cote_voisin) and (not graphe_a_manipuler.coordsInhabitedAdjacents(i).empty()) ) {
            vector<Coords> resultat_voisin = rechercheDansVoisins(i, graph, camp, profondeur);
            for(auto resultat_potentiel:resultat_voisin){
                if (find(resultat.begin(), resultat.end(), resultat_potentiel) == resultat.end()) {
                    resultat.push_back(resultat_potentiel);
                }
            }


        }
        cote_voisin++;
    }
    }else if (profondeur==3){
        for(auto j:voisins)
            if (graphe_a_manipuler.getCase(j).empty() and graphe_a_manipuler.canSlide(coord, cote_voisin)and (not graphe_a_manipuler.coordsInhabitedAdjacents(j).empty()) ) {
                resultat.push_back(j);
                cote_voisin++;
            }
        }

    return resultat;

        }

    vector<Coords> LegalMoveFourmi::searchMoves(Coords coord, Graphe graph, bool camp) {
        graphe_avant_coup=graph;
        graphe_a_manipuler=graph;
        vector<Coords> resultat;
        if(graphe_a_manipuler.wouldHiveBreak(coord)){
            cout<<"\nNe peut pas bouger sans casser la hive";
            return resultat;
        }
        vector<Coords> voisins_traites;
        voisins_traites.push_back(coord);
        resultat= rechercheDansVoisins(coord,graph,camp,voisins_traites);

        return resultat;
}

vector<Coords> LegalMoveFourmi::rechercheDansVoisins(Coords coord, Graphe graph, bool camp, vector<Coords>& voisins_traites) const {
    vector<Coords> voisins = graphe_a_manipuler.coordsExistentAdjacents(coord);
    unsigned int cote_voisin = 0;
    for (auto i: voisins) {
        if (graphe_a_manipuler.getCase(i).empty() and graphe_a_manipuler.canSlide(coord, cote_voisin) and
            (not graphe_a_manipuler.coordsInhabitedAdjacents(i).empty()) and (find(voisins_traites.begin(), voisins_traites.end(), i) == voisins_traites.end())) {
            voisins_traites.push_back(i);
            vector<Coords> resultat_voisin = rechercheDansVoisins(i, graph, camp, voisins_traites);
            for (auto resultat_potentiel: resultat_voisin) {
                if (find(voisins_traites.begin(), voisins_traites.end(), resultat_potentiel) == voisins_traites.end()) {
                    voisins_traites.push_back(resultat_potentiel);
                }
            }

        }
    }
    return voisins_traites;

}