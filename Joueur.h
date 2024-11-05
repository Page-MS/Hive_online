#ifndef LO21_JOUEUR_H
#define LO21_JOUEUR_H
#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>
#include "Pieces.h"

using namespace std;

class Joueur {
    string nom;
    vector<Piece*> pieces;

public:
    Joueur(const std::string& nomJoueur) : nom(nomJoueur) {}
    void jouerCoup();

    string getNom() const { return nom; }
    void ajouterPiece(Piece* piece) { pieces.insert(pieces.end(), piece); }
};


class IAJoueur : public Joueur {
    int difficulte;

public:
    IAJoueur(const std::string& nomJoueur, int niveauDifficulte):Joueur(nomJoueur), difficulte(niveauDifficulte) {}

    //void prendreDecision(EtatDuJeu& etat);

    //int evaluerSituation(const EtatDuJeu& etat) const;
};

#endif