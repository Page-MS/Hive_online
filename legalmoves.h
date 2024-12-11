//
// Created by page on 13/11/2024.
//

#ifndef LO21_LEGALMOVES_H
#define LO21_LEGALMOVES_H
#include "pieces.h"

class LegalMoveInterface{
public:
    virtual ~LegalMoveInterface()=default;
    virtual vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) = 0;
    //Pour calculer sur le graph
    Graphe graphe_avant_coup;
    Graphe graphe_a_manipuler;
};
class LegalMoveAbeille : public LegalMoveInterface {
    vector<Coords> searchMoves(Coords coord, Graphe graph, bool camp) override;
};
class LegalMoveContext{
private:
    LegalMoveContext(): strategy(new LegalMoveAbeille){};
    //on supprime l'affectation et la copie
    LegalMoveContext(const LegalMoveContext&) = delete;
    LegalMoveContext& operator=(const LegalMoveContext&) = delete;
    ~LegalMoveContext(){delete strategy;}
    //La strategie actuelle pour traiter le cas en cours
    LegalMoveInterface* strategy;
    TYPE_PIECE current_strategy;
public:
    //usage de singleton pour obtenir l'unique instance du legalMoveContext
    static LegalMoveContext& getInstance(){
        static LegalMoveContext instance;
        return instance;
    }
    vector<Coords> searchLegalMoves(Coords coord,Graphe graph, bool camp);
    void changeStrategy(TYPE_PIECE typePiece);

};


class LegalMoveMoustique : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) override;
};

class LegalMoveFourmi : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool campvector) override;
    vector<Coords> rechercheDansVoisins(Coords coord, Graphe graph, bool camp, vector<Coords>& voisins_traites) const;
};

class LegalMoveScarabee : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool campvector) override;
};

class LegalMoveCoccinelle : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) override;
    vector<Coords> rechercheDansVoisins(Coords coord, Graphe graph, bool camp,unsigned int profondeur) const;
};


class LegalMoveSauterelle : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) override;
};

class LegalMoveAraignee : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) override;
    vector<Coords> rechercheDansVoisins(Coords coord,Graphe graph, bool camp,unsigned int profondeur) const;
};




#endif //LO21_LEGALMOVES_H
