#include "joueur.h"
#include <unordered_set>
#include <algorithm>
#include <fstream>

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
            pieces.emplace_back(modele, IA);
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

bool Joueur::jouerCoupCreer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau) {
    if (!plateau.inReserve(*pieceChoisie)) {
        cout<<"La pièce choisie n'est pas dans la réserve.\n";
        return false;
    }

    if (!plateau.canPlace(*pieceChoisie, destination)) {
        cout<<"La position cible est invalide ou occupée.\n";
        return false;
    }

    plateau.movePiece(*pieceChoisie, destination);
    return true;
}

bool Joueur::jouerCoupDeplacer(Piece* pieceChoisie, const Coords& destination, Plateau& plateau){
    if (plateau.inReserve(*pieceChoisie)) {
        cout<<"La pièce choisie n'est pas dans la réserve.\n";
        return false;
    }

    if (plateau.isPieceStuck(*pieceChoisie)){
        cout<<"La pièce choisie est bloqué sous une autre pièce.\n";
        return false;
    }

    if (!plateau.canPlace(*pieceChoisie, destination)) {
        cout<<"La position cible est invalide ou occupée.\n";
        return false;
    }


    // Obtenir les mouvements légaux de la pièce
    LegalMoveContext& moveContext = LegalMoveContext::getInstance();
    moveContext.changeStrategy(pieceChoisie->getType());
    Graphe copygraphe = plateau.getGraphe();
    vector<Coords> legalMoves = moveContext.searchLegalMoves(destination, &copygraphe, pieceChoisie->getCamp());

    //parcours les legalmoves pour verifier que destination en fait bien partie
    auto it = std::find(legalMoves.begin(), legalMoves.end(), destination);
    if (it == legalMoves.end()) {
        cout<<"La destination n'est pas un mouvement légal pour cette pièce.\n";
        return false;
    }

    plateau.movePiece(*pieceChoisie, destination);
    return true;
}



void Joueur::save(const std::string& fichier, Plateau& plateau) const {
    std::ofstream file(fichier);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    // Écrire le camp du joueur
    file << "Camp: " << camp << "\n";

    // Compter et écrire le nombre de pièces de chaque type sur le plateau
    std::map<TYPE_PIECE, int> piecesCount;
    for (auto piece : pieces) {
        if (!plateau.inReserve(*piece)) {
            piecesCount[piece->getType()]++;
        }
    }

    for (const auto& entry : piecesCount) {
        file << "Type: " << entry.first << ", Nombre: " << entry.second << "\n";
    }

    file << "FIN_JOUEUR\n";

    file.close();
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






