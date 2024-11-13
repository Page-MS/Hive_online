#include "joueur.h"


void Joueur::jouerCoup(){

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
