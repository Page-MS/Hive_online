#include "joueur.h"

Joueur& Joueur::operator=(const Joueur& autre) {
    if (this != &autre) { // évite la copie de soi-même
        nom = autre.nom;
        // libere les pieces
        for (Piece* piece : pieces) {delete piece;}
        pieces.clear();

        // copie les nouvelles pièces
        for (Piece* piece : autre.pieces) {pieces.push_back(new Piece(*piece));}
    }
    return *this;
}

void Joueur::jouerCoup(Piece* pieceChoisie, const Coords& destination, Plateau& plateau){

}


void Mouvement::ExecuterMvt(){

}

void Mouvement::AnnulerMvt(){

}

EtatDuJeu(int num_tour, const Plateau& p,  const Joueur& j1, const Joueur& j2, const Joueur& jc){
    numero_tour = num_tour;
    plateau = p; //nécessite un constructeur de recopie de Plateau
    joueurs[0] = j1; //constructeur de recopie de Joueur
    joueurs[1] = j2;
    joueur_courant = nullptr;

    if(&jc == &j1) {
        joueur_courant = &joueurs[0];
    }else if(&jc == &j2) {
        joueur_courant = &joueurs[1];
    }else{
        joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans `partie`
    }
}

EtatDuJeu::EtatDuJeu(){
    numero_tour = 0;
    plateau = Plateau();
    joueurs[0] = Joueur(); //constructeur de recopie de Joueur
    joueurs[1] = Joueur();
    joueur_courant = nullptr;
}


EtatDuJeu& EtatDuJeu::operator=(const EtatDuJeu& jeu){
    if(this != &jeu){
        numero_tour = jeu.numero_tour;
        plateau = jeu.plateau; //nécessite un constructeur de recopie de Plateau
        joueurs[0] = jeu.joueurs[0]; //constructeur de recopie de Joueur
        joueurs[1] = jeu.joueurs[1];
        
        if(jeu.joueur_courant == &jeu.joueurs[0]) joueur_courant = &joueurs[0];

        else if(jeu.joueur_courant == &jeu.joueurs[1]) joueur_courant = &joueurs[1];

        else joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans le jeu que l'on recopie
    }
    return *this;
}

vector<Mouvement> EtatDuJeu::coupPossibles(Joueur& j){
    
}

bool EtatDuJeu::FinDuJeu() const{

}

void EtatDuJeu::annulerDernierMouvement(){

}


void IAJoueur::prendreDecision(EtatDuJeu& etat){

}

int IAJoueur::evaluerSituation(const EtatDuJeu& etat) const{

}


int EvalMouvement::evalCoup(const Mouvement& mvt, const EtatDuJeu& etat){

}

Mouvement EvalMouvement::comparerCoups(const std::vector<Mouvement>& coups, const EtatDuJeu& etat){

}
