#include <bits/stdc++.h>
#include "joueur.h"

Joueur::Joueur(const std::string& nomJoueur, bool IA) : nom(nomJoueur), isIA(IA) {
    map<TYPE_PIECE, int> piecesNecessaires = {
        {Araignee, 2},
        {Sauterelle, 3},
        {Fourmi, 3},
        {Scarabee, 2},
        {Moustique, 1},
        {Coccinelle, 1},
        {Abeille, 1}
    };

    for (const auto& typeDePiecce : piecesNecessaires) {
        TYPE_PIECE modele = typeDePiecce.first;
        int nombre = typeDePiecce.second;

        for (int i = 0; i < nombre; ++i) {
            pieces.push_back(new Piece(modele, IA));
        }
    }
}

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

void Joueur::jouerCoupCreer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau) {
    if (!plateau.inReserve(*pieceChoisie)) {
        throw std::invalid_argument("La pièce choisie n'est pas dans la réserve.");
    }

    if (!plateau.canPlace(*pieceChoisie, destination)) {
        throw std::invalid_argument("La position cible est invalide ou occupée.");
    }

    // Obtenir les mouvements légaux de la pièce
    LegalMoveContext& moveContext = LegalMoveContext::getInstance();
    moveContext.changeStrategy(pieceChoisie->getType());
    vector<Coords> legalMoves = moveContext.searchLegalMoves(destination, plateau.getGraphe(), pieceChoisie->getCamp());

    //parcours les legalmoves pour verifier que destination en fait bien partie
    auto it = std::find(legalMoves.begin(), legalMoves.end(), destination);
    if (it == legalMoves.end()) {
        throw std::invalid_argument("La destination n'est pas un mouvement légal pour cette pièce.");
    }

    plateau.movePiece(*pieceChoisie, destination);
}

void Joueur::jouerCoupDeplacer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau){
    if (plateau.inReserve(*pieceChoisie)) {
        throw std::invalid_argument("La pièce choisie est dans la réserve.");
    }

    if (plateau.isPieceStuck(*pieceChoisie)){
        throw std::invalid_argument("La pièce choisie est bloqué sous une autre pièce.");
    }

    if (!plateau.canPlace(*pieceChoisie, destination)) {
        throw std::invalid_argument("La position cible est invalide ou occupée.");
    }


    // Obtenir les mouvements légaux de la pièce
    LegalMoveContext& moveContext = LegalMoveContext::getInstance();
    moveContext.changeStrategy(pieceChoisie->getType());
    vector<Coords> legalMoves = moveContext.searchLegalMoves(destination, plateau.getGraphe(), pieceChoisie->getCamp());

    //parcours les legalmoves pour verifier que destination en fait bien partie
    auto it = std::find(legalMoves.begin(), legalMoves.end(), destination);
    if (it == legalMoves.end()) {
        throw std::invalid_argument("La destination n'est pas un mouvement légal pour cette pièce.");
    }

    plateau.movePiece(*pieceChoisie, destination);
}


void Mouvement::ExecuterMvt(){

}

void Mouvement::AnnulerMvt(){

}

void IAJoueur::prendreDecision(EtatDuJeu& etat){

}

int IAJoueur::evaluerSituation(const EtatDuJeu& etat) const{

}


int EvalMouvement::evalCoup(const Mouvement& mvt, const EtatDuJeu& etat){

}

Mouvement EvalMouvement::comparerCoups(const std::vector<Mouvement>& coups, const EtatDuJeu& etat){

}
