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

class Joueur {
protected:
    string nom;
    vector<Piece*> pieces; // pieces du joueur
    bool isIA;
    bool camp;

public:
    Joueur(const std::string& nomJoueur, bool IA=false);
    Joueur(){}
    Joueur(const Joueur& autre) : nom(autre.nom) {
        for (Piece* piece : autre.pieces) {
            pieces.push_back(new Piece(*piece)); // copie chaque pièce
        }
    }
    Joueur& operator=(const Joueur& autre);
    ~Joueur() {
        for (Piece* piece : pieces) {
            delete piece; // libère chaque pièce
        }
    }

    bool jouerCoupCreer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau);

    bool jouerCoupDeplacer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau);

    vector<Piece*> getPieces(){ return pieces; }

    string getNom() const { return nom; }

    void ajouterPiece(Piece* piece) { pieces.push_back(piece); } // ajoute une piece

    bool getIsIA() { return isIA; }

    void setCamp(bool newCamp) { camp = newCamp; }
    bool getCamp() { return camp; }
    void save(const std::string& fichier, Plateau& plateau) const;
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

class IAJoueur : public Joueur {
public:
    IAJoueur(const std::string& nomJoueur):Joueur(nomJoueur, true) {}

    void prendreDecision(EtatDuJeu& etat);  // décide quoi jouer

    int evaluerSituation(const EtatDuJeu& etat) const;  // évalue l'état du jeu
};


class EvalMouvement {
public:
    int evalCoup(const Mouvement& mvt, const EtatDuJeu& etat);  // évalue un coup

    Mouvement comparerCoups(const std::vector<Mouvement>& coups, const EtatDuJeu& etat); // compare les coups
};

#endif // LO21_JOUEUR_H