//
// Created by page on 13/11/2024.
//

#ifndef LO21_LEGALMOVES_H
#define LO21_LEGALMOVES_H
#include "pieces.h"

class LegalMoveInterface{
public:
    virtual ~LegalMoveInterface()=default;
    virtual vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) const = 0;
    bool checkReineAbeille(Coords case_a_check) const; //return true si le coup est valide par rapport aux règles de pose de la reine abeille en debut de partie
    bool aUnVoisin(Coords depart, Coords arrivee) const; //return true si la case passée en argument a au moins un voisin qui n'est pas la pièce déplacée
    bool cassePasRuche(Coords depart) const;//check que le coup ne casse pas la hive (qu'on a un passage entre tout)
    bool peutPasser(Coords depart, Coords arrivee) const; //vérifier qu'une pièce peut passer dans un trou en vérifiant que les cases ont moins de 2 voisins en commun
    //Pour calculer sur le graph
    Graphe graphe_avant_coup;
    Graphe graphe_a_manipuler;
};
class LegalMoveAbeille : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) const override{
        Coords a(5,6);
        vector<Coords> b;
        b.push_back(a);
        return b;

    }
};

class LegalMoveContext{
private:
    LegalMoveContext(): strategy(new LegalMoveAbeille){};
    //on supprime l'affectation et la copie
    LegalMoveContext(const LegalMoveContext&) = delete;
    LegalMoveContext& operator=(const LegalMoveContext&) = delete;
    ~LegalMoveContext(){delete strategy;}
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
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) const override{
        Coords a(5,6);
        vector<Coords> b;
        b.push_back(a);
        return b;
    }
};

class LegalMoveFourmi : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) const override{
        Coords a(5,6);
        vector<Coords> b;
        b.push_back(a);
        return b;

    }
};

class LegalMoveScarabee : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) const override{
        Coords a(5,6);
        vector<Coords> b;
        b.push_back(a);
        return b;

    }
};

class LegalMoveCoccinelle : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) const override{
        Coords a(5,6);
        vector<Coords> b;
        b.push_back(a);
        return b;

    }
};


class LegalMoveSauterelle : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) const override{
        Coords a(5,6);
        vector<Coords> b;
        b.push_back(a);
        return b;
    }
};

class LegalMoveAraignee : public LegalMoveInterface{
    vector<Coords> searchMoves(Coords coord,Graphe graph, bool camp) const override{
        Coords a(5,6);
        vector<Coords> b;
        b.push_back(a);
        return b;

    }
};




#endif //LO21_LEGALMOVES_H
