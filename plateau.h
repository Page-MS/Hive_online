#ifndef PLATEAU_H
#define PLATEAU_H
#include "cases.h"

// PLATEAU
class Plateau {
    Graphe graphe;
    std::vector<const Piece*> reserve;
    
    Graphe& getMutableGraphe() { return graphe; }

    public :
        Plateau()=default;
        ~Plateau()=default;
        Plateau(const Plateau& p);
        Plateau& operator=(const Plateau& p);

        const Graphe& getGraphe() const { return graphe; }

        bool inReserve(const Piece& p) const;

        void addPieceReserve(const Piece& p) { if (!inReserve(p)) reserve.push_back(&p); }
        void supprPieceReserve(const Piece& p);
        void movePiece(const Piece& p, const Coords& c);

        const Coords* coordsPiece(const Piece& p) const;
        bool isPieceStuck(const Piece& p) const;
        bool canPlace(const Piece& p, const Coords& c) const { return getGraphe().canPlace(c, p.getCamp());}

        void afficher(bool joueur_courant);
};


#endif