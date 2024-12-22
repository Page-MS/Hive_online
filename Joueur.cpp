#include "joueur.h"
#include <unordered_set>
#include <algorithm>
#include <fstream>

Joueur::Joueur(const std::string& nom_joueur, bool camp_joueur, bool IA) : nom(nom_joueur), camp(camp_joueur), isIA(IA) {
    map<TYPE_PIECE, int> piecesNecessaires = {
        {Araignee, 2},
        {Sauterelle, 3},
        {Fourmi, 3},
        {Scarabee, 2},
        {Moustique, 1},
        {Coccinelle, 1},
        {Abeille, 1}
    };

    for (const auto& typeDePiece : piecesNecessaires) {
        TYPE_PIECE modele = typeDePiece.first;
        int nombre = typeDePiece.second;

        for (int i = 0; i < nombre; ++i) {
            pieces.emplace_back(new Piece(modele, camp));
        }
    }
}

Joueur& Joueur::operator=(const Joueur& autre) {
    if (this != &autre) { // evite la copie de soi-même
        nom = autre.nom;
        camp = autre.camp;
        isIA = autre.isIA;
        // libere les pieces
        for (const Piece* piece : pieces) {delete piece;}
        pieces.clear();

        // copie les nouvelles pieces
        for (const Piece* piece : autre.pieces) {pieces.push_back(new Piece(*piece));}
    }
    return *this;
}
bool Joueur::jouerCoupCreer(const Piece* pieceChoisie, const Coords& destination, Plateau& plateau) {
    if(pieceChoisie == nullptr) {
        cout<<"La piece choisie n'existe pas.\n";
        return false;
    }
    if (pieceChoisie->getCamp()!=camp) throw runtime_error("ERROR Joueur::jouerCoupCreer : la piece appartient au joueur adverse.");

    if (!plateau.inReserve(*pieceChoisie)) {
        cout<<"La piece choisie n'est pas dans la reserve.\n";
        return false;
    }

    if (!plateau.canPlace(*pieceChoisie, destination)) {
        cout<<"La position cible est invalide ou occupee.\n";
        return false;
    }

    plateau.movePiece(*pieceChoisie, destination);
    return true;
}

bool Joueur::jouerCoupDeplacer(const Piece* pieceChoisie, const Coords& destination, Plateau& plateau){
    cout<< camp<<endl;
    if (pieceChoisie->getCamp()!=camp) throw runtime_error("ERROR Joueur::jouerCoupDeplacer : la piece appartient au joueur adverse.");

    if (plateau.inReserve(*pieceChoisie)) {
        cout<<"La piece choisie n'est pas dans la reserve.\n";
        return false;
    }

    if (plateau.isPieceStuck(*pieceChoisie)){
        cout<<"La piece choisie est bloque sous une autre piece.\n";
        return false;
    }

    /*if (!plateau.canPlace(*pieceChoisie, destination)) {
        cout<<"La position cible est invalide ou occupee.\n";
        return false;
    }*/

    if (plateau.getGraphe().getNbInhabitedCases()>0) {
        // Obtenir les mouvements legaux de la piece
        LegalMoveContext& moveContext = LegalMoveContext::getInstance();
        moveContext.changeStrategy(pieceChoisie->getType());
        Graphe copygraphe = plateau.getGraphe();
        vector<Coords> legalMoves = moveContext.searchLegalMoves(*plateau.coordsPiece(*pieceChoisie), &copygraphe, pieceChoisie->getCamp());
        //parcours les legalmoves pour verifier que destination en fait bien partie
        auto it = std::find(legalMoves.begin(), legalMoves.end(), destination);
        if (it == legalMoves.end()) {
            cout<<"La destination n'est pas un mouvement legal pour cette piece.\n";
            return false;
        }
    }
    plateau.movePiece(*pieceChoisie, destination);
    return true;
}

void Mouvement::ExecuterMvt(){

}

void Mouvement::AnnulerMvt(){

}

void IAJoueur::prendreDecision(EtatDuJeu& etat){

}

int IAJoueur::evaluerSituation(const EtatDuJeu& etat) const{
return 0;
}


int EvalMouvement::evalCoup(const Mouvement& mvt, const EtatDuJeu& etat){
return 0;
}

Mouvement EvalMouvement::comparerCoups(const std::vector<Mouvement>& coups, const EtatDuJeu& etat){
return Mouvement(new Piece(TYPE_PIECE::Sauterelle, true), Coords(0, 0), Coords(0, 0));
}












