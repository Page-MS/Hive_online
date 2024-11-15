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
