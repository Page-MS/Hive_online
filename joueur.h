#ifndef LO21_JOUEUR_H
#define LO21_JOUEUR_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "pieces.h"
#include "plateau.h"
#include "legalmoves.h"


#include <initializer_list>
#include <array>
#include <cstdlib>

using namespace std;

class EtatDuJeu;

class joueur {
protected:
    string nom;
    vector<Piece*> pieces; // pieces du joueur
    bool isIA;
    bool camp;

public:
    joueur(const std::string& nomJoueur,bool Camp, bool IA=false);
    joueur(){}
    joueur(const joueur& autre) : nom(autre.nom) {
        for (Piece* piece : autre.pieces) {
            pieces.push_back(new Piece(*piece)); // copie chaque pièce
        }
    }
    joueur& operator=(const joueur& autre);
    ~joueur() {
        for (Piece* piece : pieces) {
            delete piece; // libère chaque pièce
        }
    }

    virtual void jouerCoupCreer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau);

    virtual void jouerCoupDeplacer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau);


    vector<Piece*> getPieces(){ return pieces; }
    vector<Coords> getPlacementPossibilities(const Plateau& plateau) const;

    string getNom() const { return nom; }

    void ajouterPiece(Piece* piece) { pieces.push_back(piece); } // ajoute une piece

    bool getIsIA() { return isIA; }
};


class Mouvement {
private:
    Piece* piece;       // piece qui bouge
    Coords posInitial;  // position de départ
    Coords posFinal;    // position d'arrivée

public:
    Mouvement(Piece* p, const Coords& initial, const Coords& final):piece(p), posInitial(initial), posFinal(final) {}

    Coords getPosInitial() const { return posInitial; }
    Coords getPosFinal() const { return posFinal; }
    Piece* getPiece() const { return piece; }

    void ExecuterMvt();  // exécute le déplacement
    void AnnulerMvt();   // annule le déplacement
};

class IAJoueur : public joueur {
private:
    int difficulte; // niveau de l'ia

public:
    IAJoueur(const std::string& nomJoueur, int niveauDifficulte): joueur(nomJoueur, true), difficulte(niveauDifficulte) {}

    void jouerCoupCreer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau) override;

    void jouerCoupDeplacer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau)override;

    
};


class EvalMouvement {
public:
    int evalCoup(const Mouvement& mvt, const EtatDuJeu& etat);  // évalue un coup

    Mouvement comparerCoups(const std::vector<Mouvement>& coups, const EtatDuJeu& etat); // compare les coups
};

#endif // LO21_JOUEUR_H