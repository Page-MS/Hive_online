//
// Created by page on 13/11/2024.
//

#include "legalmoves.h"
#include "cases.h"
#include <algorithm>

void LegalMoveContext::changeStrategy(TYPE_PIECE typePiece) {
    //si la strategie à appliquer est la même, on ne la change pas
        if (strategy != nullptr) {
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
            std::cout << "\nAttention choix de piece invalide";
            strategy = nullptr;
        }
    }



vector<Coords > LegalMoveContext::searchLegalMoves(Coords coord, Graphe* graph, bool camp) {
    bool piece_vide=graph->getCase(coord).empty();
    if(!piece_vide) {
        changeStrategy(graph->getCase(coord).getUpperPiece().getType());
    }else {
        //TODO comprendre pourquoi on appelle des legalmoves sur une case vide
        cout<<"\n coord : "<<coord.getX()<<":"<<coord.getY()<<" camp : "<<camp<<"\n";
        throw std::runtime_error("LegalMoveContext::searchLegalMoves Appel des legalmove d'une piece vide");
    }
    vector<Coords> result=strategy->searchMoves(coord,graph,camp);
    return result;

}

vector<Coords> LegalMoveAbeille::searchMoves(Coords coord,Graphe* graph, bool camp) {
    graphe_a_manipuler=graph;
    vector<Coords> resultat;
    if(graphe_a_manipuler->wouldHiveBreak(coord)){
        return resultat;
    }
    vector<Coords> voisins=graphe_a_manipuler->coordsExistentAdjacents(coord);
    int cote_voisin=0;
    for(auto i:voisins){
        if (graphe_a_manipuler->getCase(i).empty() && graphe_a_manipuler->canSlide(coord,cote_voisin)){
            bool a_autre_voisin_que_piece_de_base=0;
            for (auto voisins_i :graphe_a_manipuler->coordsInhabitedAdjacents(i)){
                if (voisins_i != coord){
                    resultat.push_back(i);

                }
            }

        }
        cote_voisin++;
    }
    return resultat;
}


vector<Coords> LegalMoveScarabee::searchMoves(Coords coord,Graphe* graph, bool campvector){
        graphe_avant_coup=graph;
        graphe_a_manipuler=graph;
        vector<Coords> resultat;
        if(graphe_a_manipuler->getCase(coord).getNbPieces()<=1){
            if(graphe_a_manipuler->wouldHiveBreak(coord)){
                return resultat;
            }
        }
        vector<Coords> voisins=graphe_a_manipuler->coordsExistentAdjacents(coord);
        for(auto i:voisins){
                resultat.push_back(i);
        }
        return resultat;

    }


vector<Coords> LegalMoveAraignee::searchMoves(Coords coord,Graphe* graph, bool camp){
    graphe_a_manipuler=graph;
    vector<Coords> resultat;
    if(graphe_a_manipuler->wouldHiveBreak(coord)){
        return resultat;
    }
    resultat= rechercheDansVoisins(coord,graph,camp,0);

    return resultat;

}


vector<Coords> LegalMoveAraignee::rechercheDansVoisins(Coords coord, Graphe* graph, bool camp,unsigned int profondeur) const {
    vector<Coords> resultat;
    vector<Coords> voisins=graphe_a_manipuler->coordsExistentAdjacents(coord);
    profondeur++;
    unsigned int cote_voisin=0;
    if (profondeur<3) {
        for(auto i:voisins) {
            if (graphe_a_manipuler->getCase(i).empty() && graphe_a_manipuler->canSlide(coord, cote_voisin) && !graphe_a_manipuler->coordsInhabitedAdjacents(i).empty()) {
                vector<Coords> resultat_voisin = rechercheDansVoisins(i, graph, camp, profondeur);
                for(auto resultat_potentiel:resultat_voisin){
                    if (find(resultat.begin(), resultat.end(), resultat_potentiel) == resultat.end()) {
                        resultat.push_back(resultat_potentiel);
                    }
                }


            }
            cote_voisin++;
        }
    } else if (profondeur==3) {
        for(auto j:voisins)
            if (graphe_a_manipuler->getCase(j).empty() && graphe_a_manipuler->canSlide(coord, cote_voisin) && !graphe_a_manipuler->coordsInhabitedAdjacents(j).empty())  {
                resultat.push_back(j);

            }
        cote_voisin++;
        }

    return resultat;

}

vector<Coords> LegalMoveFourmi::searchMoves(Coords coord, Graphe* graph, bool camp) {
    graphe_avant_coup=graph;
    graphe_a_manipuler=graph;
    vector<Coords> resultat;
    if(graphe_a_manipuler->wouldHiveBreak(coord)){
        return resultat;
    }
    vector<Coords> voisins_traites;
    voisins_traites.push_back(coord);
    resultat= rechercheDansVoisins(coord,graph,camp,voisins_traites);

    return resultat;
}

vector<Coords> LegalMoveFourmi::rechercheDansVoisins(Coords coord, Graphe* graph, bool camp, vector<Coords>& voisins_traites) const {
    vector<Coords> voisins = graphe_a_manipuler->coordsExistentAdjacents(coord);
    unsigned int cote_voisin = 0;
    for (auto i: voisins) {
        if (graphe_a_manipuler->getCase(i).empty() && graphe_a_manipuler->canSlide(coord, cote_voisin) &&
            !graphe_a_manipuler->coordsInhabitedAdjacents(i).empty() && (find(voisins_traites.begin(), voisins_traites.end(), i) == voisins_traites.end())) {
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

vector<Coords> LegalMoveCoccinelle::searchMoves(Coords coord, Graphe* graph, bool camp) {
    graphe_a_manipuler=graph;
    vector<Coords> resultat;
    if(graphe_a_manipuler->wouldHiveBreak(coord)){
        return resultat;
    }
    resultat= rechercheDansVoisins(coord,graph,camp,0);

    return resultat;
}

vector<Coords> LegalMoveCoccinelle::rechercheDansVoisins(Coords coord, Graphe* graph, bool camp,unsigned int profondeur) const {
    vector<Coords> resultat;
    vector<Coords> voisins=graphe_a_manipuler->coordsExistentAdjacents(coord);
    profondeur++;
    unsigned int cote_voisin=0;
    if (profondeur<3){
        for(auto i:voisins) {
            if ( !graphe_a_manipuler->getCase(i).empty() && !graphe_a_manipuler->coordsInhabitedAdjacents(i).empty() ) {
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
            if (graphe_a_manipuler->getCase(j).empty() && !graphe_a_manipuler->coordsInhabitedAdjacents(j).empty()) {
                resultat.push_back(j);

            }
        cote_voisin++;
    }

    return resultat;

}

vector<Coords> LegalMoveSauterelle::searchMoves(Coords coord,Graphe* graph, bool camp){
    graphe_a_manipuler=graph;
    vector<Coords> resultat;
    if(graphe_a_manipuler->wouldHiveBreak(coord)){
        return resultat;
    }
    vector<Coords> voisins=graphe_a_manipuler->coordsExistentAdjacents(coord);
    int cote_voisin=0;
    for(auto i:voisins){
        if (!graphe_a_manipuler->getCase(i).empty() ){
            Coords case_voisine= graphe_a_manipuler->coordsAdjacent(i,cote_voisin);
            bool voisin_is_not_empty = (!graphe_a_manipuler->getCase(case_voisine).empty());
            while(voisin_is_not_empty){
                case_voisine= graphe_a_manipuler->coordsAdjacent(case_voisine,cote_voisin);
                voisin_is_not_empty=(!graphe_a_manipuler->getCase(case_voisine).empty());
            }
            resultat.push_back(case_voisine);
            cote_voisin++;

        }
        }
    return resultat;
}
vector<Coords> LegalMoveContext::searchNeighbourMosquito(Coords coord, Graphe* graph,bool camp) {
    vector<Coords> result=strategy->searchMoves(coord,graph,camp);
    return result;

}
vector<Coords> LegalMoveMoustique::searchMoves(Coords coord,Graphe* graph, bool camp){
    graphe_a_manipuler=graph;
    vector<Coords> resultat;
    TYPE_PIECE type_voisin;
    vector<TYPE_PIECE> types_pieces_voisines;
    if(graphe_a_manipuler->wouldHiveBreak(coord)){
        return resultat;
    }
    vector<Coords> voisins=graphe_a_manipuler->coordsInhabitedAdjacents(coord);
    for (auto i:voisins){
        bool piece_vide=graphe_a_manipuler->getCase(i).empty();
        if(!piece_vide){
        type_voisin=graphe_a_manipuler->getCase(i).getUpperPiece().getType();}
        if (find(types_pieces_voisines.begin(), types_pieces_voisines.end(), type_voisin) == types_pieces_voisines.end()) {
            types_pieces_voisines.push_back(type_voisin);
        }
    }
    LegalMoveContext* legalmove = &LegalMoveContext::getInstance();
    for (auto type:types_pieces_voisines){
        //graphe_a_manipuler.getCase(coord)
        if (type!=5){
            legalmove->changeStrategy(type);
            vector<Coords> results_with_neighbour_type=legalmove->searchNeighbourMosquito(coord,graph,camp);
            for (auto potential_result:voisins){
                if (find(resultat.begin(), resultat.end(), potential_result) == resultat.end()) {
                    resultat.push_back(potential_result);
                }
        }}


    }
    return resultat;
}