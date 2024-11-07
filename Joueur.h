#ifndef LO21_JOUEUR_H
#define LO21_JOUEUR_H

#include <iostream>
#include <string>
#include <vector>
#include "pieces.h"
#include "plateau.h"
#include "coords.h"
#include "cases.h"

using namespace std;

class Joueur {
protected:
    string nom;
    vector<Piece*> pieces; // pieces du joueur

public:
    Joueur(const std::string& nomJoueur) : nom(nomJoueur) {}
    ~Joueur() {
        for (Piece* piece : pieces) {
            delete piece; // libère chaque pièce
        }
    }

    virtual void jouerCoup(); // joueur joue un coup

    string getNom() const { return nom; }

    void ajouterPiece(Piece* piece) { pieces.push_back(piece); } // ajoute une piece
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


class EtatDuJeu {
private:
    Plateau plateau;               // plateau avec les pièces
    vector<Mouvement> historique;  // liste des coups
    vector<Joueur> joueurs;        // liste des joueurs

public:
    EtatDuJeu(const std::vector<Joueur>& joueurs):joueurs(joueurs) {}

    vector<Mouvement> coupPossibles(Joueur& j);  // coups possibles

    bool FinDuJeu() const;  // vérifie si le jeu est fini

    void ajouterMouvement(const Mouvement& mvt) { historique.push_back(mvt); } // ajoute un coup à l'historique

    void annulerDernierMouvement(); // annule le dernier coup

    Plateau& getPlateau() { return plateau; } // accès au plateau
};


class IAJoueur : public Joueur {
private:
    int difficulte; // niveau de l'ia

public:
    IAJoueur(const std::string& nomJoueur, int niveauDifficulte):Joueur(nomJoueur), difficulte(niveauDifficulte) {}

    void prendreDecision(EtatDuJeu& etat);  // décide quoi jouer

    int evaluerSituation(const EtatDuJeu& etat) const;  // évalue l'état du jeu
};


class EvalMouvement {
public:
    int evalCoup(const Mouvement& mvt, const EtatDuJeu& etat);  // évalue un coup

    Mouvement comparerCoups(const std::vector<Mouvement>& coups, const EtatDuJeu& etat); // compare les coups
};

#endif // LO21_JOUEUR_H