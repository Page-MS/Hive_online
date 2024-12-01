#ifndef PLATEAU_H
#define PLATEAU_H
#include "cases.h"

// PLATEAU
class Plateau {
    Graphe graphe;
    std::vector<const Piece*> reserve;


    public :
        Plateau()=default;
        ~Plateau()=default;
        const Graphe& getGraphe() const { return graphe; }
        Graphe& getMutableGraphe() { return graphe; }

        bool inReserve(const Piece& p) const;

        void addPieceReserve(const Piece& p) { reserve.push_back(&p); }
        void supprPieceReserve(const Piece& p);
        void movePiece(const Piece& p, const Coords& c);

        const Coords* coordsPiece(const Piece& p) const;
        bool isPieceStuck(const Piece& p) const;



};

#endif