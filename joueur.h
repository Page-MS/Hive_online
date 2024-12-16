#ifndef LO21_JOUEUR_H
#define LO21_JOUEUR_H

#include <iostream>
#include <string>
#include <vector>
#include "plateau.h"
#include <initializer_list>
#include <array>
#include <cstdlib>

using namespace std;

class Joueur {
protected:
    string nom;
    vector<Piece*> pieces; // pieces du joueur
    bool isIA;

public:
    Joueur(const std::string& nomJoueur, bool IA=false) : nom(nomJoueur), isIA(IA) {}
    Joueur(){}
    Joueur(const Joueur& autre) : nom(autre.nom) {
        for (Piece* piece : autre.pieces) {
            pieces.push_back(new Piece(*piece)); // copie chaque pièce
        }
    }
    Joueur& operator=(const Joueur& autre);*
    ~Joueur() {
        for (Piece* piece : pieces) {
            delete piece; // libère chaque pièce
        }
    }

    void jouerCoup(Piece* pieceChoisie, const Coords& destination, Plateau& plateau); // joueur joue un coup

    string getNom() const { return nom; }

    void ajouterPiece(Piece* piece) { pieces.push_back(piece); } // ajoute une piece

    bool getIsIA() { return isIA; }

    vector<Piece*> getPieces(){return pieces;}
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
    Joueur* joueurs[2];              // liste des joueurs
    int numero_tour;
    Joueur* joueur_courant;

public:
    EtatDuJeu(int num_tour, const Plateau& p,  const Joueur& j1, const Joueur& j2, const Joueur& jc);
    EtatDuJeu();
    EtatDuJeu& operator=(const EtatDuJeu& jeu);
    vector<Mouvement> coupPossibles(Joueur& j);  // coups possibles
    bool FinDuJeu() const;  // vérifie si le jeu est fini
    void ajouterMouvement(const Mouvement& mvt) { historique.push_back(mvt); } // ajoute un coup à l'historique
    void annulerDernierMouvement(); // annule le dernier coup
    Plateau& getPlateau() { return plateau; } // accès au plateau

    Joueur* getJoueurCourant() {return joueur_courant;}

};





class IAJoueur : public Joueur {
private:
    int difficulte; // niveau de l'ia

public:
    IAJoueur(const std::string& nomJoueur, int niveauDifficulte):Joueur(nomJoueur, true), difficulte(niveauDifficulte) {}

    void prendreDecision(EtatDuJeu& etat);  // décide quoi jouer

    int evaluerSituation(const EtatDuJeu& etat) const;  // évalue l'état du jeu
};


class EvalMouvement {
public:
    int evalCoup(const Mouvement& mvt, const EtatDuJeu& etat);  // évalue un coup

    Mouvement comparerCoups(const std::vector<Mouvement>& coups, const EtatDuJeu& etat); // compare les coups
};

#endif // LO21_JOUEUR_H
