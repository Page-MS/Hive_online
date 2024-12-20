#ifndef PLATEAU_H
#define PLATEAU_H
#include "cases.h"

class ReminderPiece {
    const void* adresse;
    TYPE_PIECE type;
    bool camp;

    public :
        ReminderPiece(const Piece& p) : adresse(reinterpret_cast<const void*>(&p)), type(p.getType()), camp(p.getCamp()) {}
        ReminderPiece(const ReminderPiece& rem)=default;
        ReminderPiece& operator=(const ReminderPiece& rem);
        void setAdresse(const Piece* p) { adresse = reinterpret_cast<const void*>(p); }

        const Piece* getAdresse() const { return reinterpret_cast<const Piece*>(adresse); }
        TYPE_PIECE getType() const { return type; }
        bool getCamp() const { return camp; }
};

// PLATEAU
class Plateau {
    Graphe graphe;
    std::vector<const Piece*> reserve;
    std::vector<ReminderPiece> memoire;

    Graphe& getMutableGraphe() { return graphe; }

    //const Reminder& getReminder(const Piece* p) const;

    public :
        Plateau()=default;
        ~Plateau()=default;
        Plateau(const Plateau& p);
        Plateau(const std::vector<Piece*>& pieces) { fillReserve(pieces); }
        Plateau(const std::vector<Piece*>& pieces1, const std::vector<Piece*>& pieces2) { fillReserve(pieces1);  fillReserve(pieces2);}
        Plateau& operator=(const Plateau& p);

        void piecesCoherence(const std::vector<Piece*>& pieces);
        void piecesCoherence(const std::vector<Piece*>& pieces1, const std::vector<Piece*>& pieces2);

        const Graphe& getGraphe() const { return graphe; }

        std::vector<const Piece*> piecesReserve(bool joueur) const;
        bool inReserve(const Piece* p) const;
        bool inReserve(const Piece& p) const { return inReserve(&p); }

        void fillReserve(const std::vector<Piece*>& pieces);
        void addPieceReserve(const Piece& p);
        void supprPieceReserve(const Piece& p);
        void movePiece(const Piece& p, const Coords& c);

        const Coords* coordsPiece(const Piece* p) const;
        const Coords* coordsPiece(const Piece& p) const { return coordsPiece(&p); }
        bool isPieceStuck(const Piece& p) const;
        bool canPlace(const Piece& p, const Coords& c) const { return getGraphe().canPlace(c, p.getCamp());}

        void afficher(bool joueur_courant) const;
        void afficher(bool joueur_courant, const Coords& selected) const;
        void afficher(bool joueur_courant, const Coords& selected1, const Coords& selected2) const;
        void afficher(const Piece& p, const Coords& selected) const;
        void afficher(const Piece& p) const;



};


#endif