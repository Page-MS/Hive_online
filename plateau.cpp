#include "plateau.h"
#include <iostream>


/*! \brief Pour savoir si la pi�ce est dans la r�serve.
*/
bool Plateau::inReserve(const Piece& p) const {
	auto i = 0;
	while (i < reserve.size() && reserve.at(i) != &p) i++;

	return i < reserve.size();
}

/*! \brief D�place la pi�ce depuis le graphe ou la r�serve.
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

/*! \brief Renvoie les coordonn�es de la pi�ce (pointeur nul si elle est dans la r�serve, erreur si elle n'est nulle part).
*/
const Coords* Plateau::coordsPiece(const Piece& p) const {
	// renvoie nullptr si pi�ce dans r�serve
	if (inReserve(p)) return nullptr;
	// erreur si pi�ce pas sur le plateau
	if (!getGraphe().hasPiece(p)) throw exception("ERROR Plateau::coordsPiece : Piece inexistante.");
	// renvoie coordonn�es de la pi�ce si dans graphe
	return &getGraphe().coordsPiece(p);
}

/*! \brief Renvoie si la pi�ce peut effectuer une action (sortir de la r�serve ou se d�placer sur le graphe.
*/
bool Plateau::isPieceStuck(const Piece& p) const {
	return (!inReserve(p) && getGraphe().isPieceStuck(p));
}