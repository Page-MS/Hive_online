#include "plateau.h"
#include <iostream>


/*! \brief Pour savoir si la pièce est dans la réserve.
*/
bool Plateau::inReserve(const Piece& p) const {
	auto i = 0;
	while (i < reserve.size() && reserve.at(i) != &p) i++;

	return i < reserve.size();
}

void Plateau::supprPieceReserve(const Piece& p) {
	for (auto i=0; i<reserve.size(); i++)
		if (reserve.at(i)==&p)
			reserve.erase(reserve.begin()+i);
}

/*! \brief Déplace la pièce depuis le graphe ou la réserve.
*/
void Plateau::movePiece(const Piece& p, const Coords& c) {
	if (isPieceStuck(p)) throw exception("ERROR Plateau::movePiece : Piece bloquee.");

	if (inReserve(p)) {
		getMutableGraphe().addPiece(p, c);
		supprPieceReserve(p);
	}
	else {
		const Coords* coords = coordsPiece(p);
		if (*coords == c) throw exception("ERROR Plateau::movePiece : Coordonnees de destination et d'arrivee de la piece identiques.");
		getMutableGraphe().movePiece(p, c);
	}
}

/*! \brief Renvoie les coordonnées de la pièce (pointeur nul si elle est dans la réserve, erreur si elle n'est nulle part).
*/
const Coords* Plateau::coordsPiece(const Piece& p) const {
	// renvoie nullptr si pièce dans réserve
	if (inReserve(p)) return nullptr;
	// erreur si pièce pas sur le plateau
	if (!getGraphe().hasPiece(p)) throw exception("ERROR Plateau::coordsPiece : Piece inexistante.");
	// renvoie coordonnées de la pièce si dans graphe
	return &getGraphe().coordsPiece(p);
}

/*! \brief Renvoie si la pièce peut effectuer une action (sortir de la réserve ou se déplacer sur le graphe.
*/
bool Plateau::isPieceStuck(const Piece& p) const {
	return (!inReserve(p) && getGraphe().isPieceStuck(p));
}