#include "plateau.h"
#include <iostream>

// METHODES PLATEAU
Plateau::Plateau(const Plateau& p) {
	reserve = p.reserve;
	graphe = p.graphe;
}

Plateau& Plateau::operator=(const Plateau& p) {
	graphe = p.graphe;
	reserve = p.reserve;
	return *this;
}

/*! \brief Affiche le plateau avec les pièces du joueur courant en bas et celles de son adversaire en haut.
*/
void Plateau::afficher(bool joueur_courant) {

	Graphe g;
	const Coords c(0, 0);

    std::cout<<"--------------------------------"<<std::endl;
    auto pieces_adversaire = piecesReserve(!joueur_courant);

    for (size_t i=0; i<pieces_adversaire.size(); i++) {
        g.addPiece(*pieces_adversaire.at(i), c);
        std::cout<<"<"<<g.getCase(c)<<">";
        g.supprPiece(c);
    }
    std::cout<<std::endl<<"---------- ADVERSAIRE ----------"<<std::endl;

	std::cout<<getGraphe()<<std::endl;

    std::cout<<"------------- VOUS -------------"<<std::endl;
    auto pieces_vous = piecesReserve(joueur_courant);

    for (size_t i=0; i<pieces_vous.size(); i++) {
        g.addPiece(*pieces_vous.at(i), c);
        std::cout<<"<"<<g.getCase(c)<<">";
        g.supprPiece(c);
    }
    std::cout<<std::endl<<"--------------------------------"<<std::endl;

	std::cout<<std::endl;
}

/*! \brief Pour savoir si la pièce est dans la réserve.
*/
bool Plateau::inReserve(const Piece& p) const {
    std::printf("%s", (&p)->strPiece().c_str());
    auto i = 0;
    while (i < reserve.size() && reserve.at(i) != &p) {i++; }

    return i < reserve.size();
}

/*! \brief Renvoie la liste des pièces du joueur pas déjà dans la ruche.
*/
std::vector<const Piece*> Plateau::piecesReserve(bool joueur) const {
    std::vector<const Piece*> pieces_joueur;

    for (size_t i=0; i<reserve.size(); i++)
        if (reserve.at(i)->getCamp()==joueur)
            pieces_joueur.push_back(reserve.at(i));

    return pieces_joueur;
}

/*! \brief Supprime une pièce de la réserve (rien si pièce pas dans réserve).
*/
void Plateau::supprPieceReserve(const Piece& p) {
	for (auto i=0; i<reserve.size(); i++)
		if (reserve.at(i)==&p)
			reserve.erase(reserve.begin()+i);
}

/*! \brief Déplace la pièce depuis le graphe ou la réserve.
*/
void Plateau::movePiece(const Piece& p, const Coords& c) {
	if (isPieceStuck(p)) throw runtime_error("ERROR Plateau::movePiece : Piece bloquee.");

	if (inReserve(p)) {
		getMutableGraphe().addPiece(p, c);
		supprPieceReserve(p);
	}
	else {
		const Coords* coords = coordsPiece(p);
		if (*coords == c) throw runtime_error("ERROR Plateau::movePiece : Coordonnees de destination et d'arrivee de la piece identiques.");
		getMutableGraphe().movePiece(p, c);
	}
}

/*! \brief Renvoie les coordonnées de la pièce (pointeur nul si elle est dans la réserve, erreur si elle n'est nulle part).
*/
const Coords* Plateau::coordsPiece(const Piece& p) const {
	// renvoie nullptr si pièce dans réserve
	if (inReserve(p)) return nullptr;
	// erreur si pièce pas sur le plateau
	if (!getGraphe().hasPiece(p)) throw runtime_error("ERROR Plateau::coordsPiece : Piece inexistante.");
	// renvoie coordonnées de la pièce si dans graphe
	return &getGraphe().coordsPiece(p);
}

/*! \brief Renvoie si la pièce peut effectuer une action (sortir de la réserve ou se déplacer sur le graphe.
*/
bool Plateau::isPieceStuck(const Piece& p) const {
	return (!inReserve(p) && getGraphe().isPieceStuck(p));
}
