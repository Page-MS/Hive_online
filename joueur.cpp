#include "joueur.h"
#include <unordered_set>
#include <algorithm>

joueur::joueur(const std::string& nomJoueur,bool Camp, bool IA) : nom(nomJoueur), isIA(IA), camp(Camp) {
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
            pieces.push_back(new Piece(modele, camp));
        }
    }
}

joueur& joueur::operator=(const joueur& autre) {
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

void joueur::jouerCoupCreer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau) {
    if (!plateau.inReserve(*pieceChoisie)) {
        throw std::invalid_argument("La pièce choisie n'est pas dans la réserve.");
    }

    if (!plateau.canPlace(*pieceChoisie, destination)) {
        throw std::invalid_argument("La position cible est invalide ou occupée.");
    }

    // Obtenir les mouvements légaux de la pièce
    LegalMoveContext& moveContext = LegalMoveContext::getInstance();
    moveContext.changeStrategy(pieceChoisie->getType());
    Graphe copygraphe = plateau.getGraphe();
    vector<Coords> legalMoves = moveContext.searchLegalMoves(destination, &copygraphe, pieceChoisie->getCamp());

    //parcours les legalmoves pour verifier que destination en fait bien partie
    auto it = std::find(legalMoves.begin(), legalMoves.end(), destination);
    if (it == legalMoves.end()) {
        throw std::invalid_argument("La destination n'est pas un mouvement légal pour cette pièce.");
    }

    plateau.movePiece(*pieceChoisie, destination);
}

void joueur::jouerCoupDeplacer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau){
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
    Graphe copygraphe = plateau.getGraphe();
    vector<Coords> legalMoves = moveContext.searchLegalMoves(destination, &copygraphe, pieceChoisie->getCamp());

    //parcours les legalmoves pour verifier que destination en fait bien partie
    auto it = std::find(legalMoves.begin(), legalMoves.end(), destination);
    if (it == legalMoves.end()) {
        throw std::invalid_argument("La destination n'est pas un mouvement légal pour cette pièce.");
    }

    plateau.movePiece(*pieceChoisie, destination);
}
//TODO: À supprimer, l'algo est foireux
vector<Coords> joueur::getPlacementPossibilities(const Plateau& plateau)const{
    vector<Coords> valid_pos;
    for (const Piece* piece : pieces) {
        const Coords* c = plateau.coordsPiece(*piece);
        if (c != nullptr){
            if(plateau.getGraphe().canPlace(*c, piece->getCamp())) valid_pos.push_back(*c);
        }
    }
    return vector<Coords>(valid_pos.begin(), valid_pos.end());
}

/*void Mouvement::ExecuterMvt(){

}

void Mouvement::AnnulerMvt(){

}*/






/*! \brief Retourne le choix de l'IA sur où poser sa pièce
*/
void IAJoueur::jouerCoupCreer(Piece *pieceChoisie, const Coords &destination, Plateau &plateau) {
    vector<Coords> resultat=plateau.getGraphe().placableCoords(camp);
    auto range = resultat.size();
    int num_choisi = rand() % range ;
    plateau.movePiece(*pieceChoisie,resultat[num_choisi]) ;

}
/*! \brief Effectue le deplacement de l'IA
*/
void IAJoueur::jouerCoupDeplacer(Piece *pieceChoisie, const Coords &destination, Plateau &plateau) {
    plateau.movePiece(*pieceChoisie,destination) ;

}


int EvalMouvement::evalCoup(const Mouvement& mvt, const EtatDuJeu& etat){

}

Mouvement EvalMouvement::comparerCoups(const std::vector<Mouvement>& coups, const EtatDuJeu& etat){

}