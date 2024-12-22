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

bool Joueur::jouerCoupDeplacer(const Piece* pieceChoisie, const Coords& destination, Plateau& plateau) {
    try {
        if (pieceChoisie->getCamp() != camp) {
            throw std::runtime_error("La pièce appartient au joueur adverse.");
        }

        if (plateau.inReserve(*pieceChoisie)) {
            std::cout << "La pièce choisie est encore dans la réserve. Déplacement impossible.\n";
            return false;
        }

        if (plateau.isPieceStuck(*pieceChoisie)) {
            std::cout << "La pièce choisie est bloquée sous une autre pièce. Déplacement impossible.\n";
            return false;
        }

        if (!plateau.canPlace(*pieceChoisie, destination)) {
            std::cout << "La position cible est invalide ou occupée.\n";
            return false;
        }

        if (plateau.getGraphe().getNbInhabitedCases() > 0) {
            LegalMoveContext& moveContext = LegalMoveContext::getInstance();
            moveContext.changeStrategy(pieceChoisie->getType());

            const Graphe& graphe = plateau.getGraphe();
            const Coords* coordsActuelles = plateau.coordsPiece(*pieceChoisie);

            if (!coordsActuelles) {
                throw std::runtime_error("coordsPiece a renvoyé nullptr pour la pièce : " + pieceChoisie->strPiece());
            }

            std::vector<Coords> legalMoves = moveContext.searchLegalMoves(
                *coordsActuelles, const_cast<Graphe*>(&graphe), pieceChoisie->getCamp());

            if (legalMoves.empty()) {
                std::cout << "Aucun mouvement légal disponible pour la pièce " << pieceChoisie->strPiece() << ".\n";
                return false;
            }

            if (std::find(legalMoves.begin(), legalMoves.end(), destination) == legalMoves.end()) {
                std::cout << "La destination " << destination.getX() << ":" << destination.getY()
                << " n'est pas un mouvement légal pour la pièce.\n";
                return false;
            }
        }

        plateau.movePiece(*pieceChoisie, destination);
        std::cout << "Déplacement réussi de la pièce " << pieceChoisie->strPiece()
                  << " vers " << destination.getX() << ":" << destination.getY() << ".\n";
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Exception dans Joueur::jouerCoupDeplacer : " << e.what() << "\n";
        return false;
    }
}



void Joueur::save(const std::string& fichier, Plateau& plateau) const {
    std::ofstream file(fichier);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    // ecrire le camp du joueur
    file << "Camp: " << camp << "\n";

    // Compter et ecrire le nombre de pieces de chaque type sur le plateau
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
    return 0;
}


int EvalMouvement::evalCoup(const Mouvement& mvt, const EtatDuJeu& etat){
    return 0;
}

Mouvement EvalMouvement::comparerCoups(const std::vector<Mouvement>& coups, const EtatDuJeu& etat){
    return Mouvement(new Piece(TYPE_PIECE::Sauterelle, true), Coords(0, 0), Coords(0, 0));
}












