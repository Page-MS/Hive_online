#include "plateau.h"
#include <iostream>
#include <algorithm>

// METHODES REMINDERPIECE
ReminderPiece& ReminderPiece::operator=(const ReminderPiece& rem) {
	adresse = rem.adresse;
	type = rem.type;
	camp = rem.camp;
	return *this;
}

// METHODES PLATEAU
Plateau::Plateau(const Plateau& p) {
	reserve = p.reserve;
	memoire = p.memoire;
	graphe = p.graphe;
}

Plateau& Plateau::operator=(const Plateau& p) {
	graphe = p.graphe;
	reserve = p.reserve;
	memoire = p.memoire;
	return *this;
}


// Affiche le plateau sans aucune case sélectionnée
void Plateau::afficher(bool joueur_courant) const {

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

// Affiche le plateau avec une case sélectionnée dans le graphe
void Plateau::afficher(bool joueur_courant, const Coords& selected) const {
	Graphe g;
	const Coords c(0, 0);

	std::cout<<"--------------------------------"<<std::endl;
	for (size_t i=0; i<reserve.size(); i++)
		if (reserve.at(i)->getCamp() != joueur_courant) {
			g.addPiece(*reserve.at(i), c);
			std::cout<<"<"<<g.getCase(c)<<">";
			g.supprPiece(c);
		}
	std::cout<<std::endl<<"---------- ADVERSAIRE ----------"<<std::endl;

	std::cout<<getGraphe().toStr(selected)<<std::endl;

	std::cout<<"------------- VOUS -------------"<<std::endl;
	for (size_t i=0; i<reserve.size(); i++)
		if (reserve.at(i)->getCamp() == joueur_courant) {
			g.addPiece(*reserve.at(i), c);
			std::cout<<"<"<<g.getCase(c)<<">";
			g.supprPiece(c);
		}
	std::cout<<std::endl<<"--------------------------------"<<std::endl;

	std::cout<<std::endl;
}

// Affiche le plateau avec deux cases sélectionnées dans le graphe
void Plateau::afficher(bool joueur_courant, const Coords& selected1, const Coords& selected2) const {
	Graphe g;
	const Coords c(0, 0);

	std::cout<<"--------------------------------"<<std::endl;
	for (size_t i=0; i<reserve.size(); i++)
		if (reserve.at(i)->getCamp() != joueur_courant) {
			g.addPiece(*reserve.at(i), c);
			std::cout<<"<"<<g.getCase(c)<<">";
			g.supprPiece(c);
		}
	std::cout<<std::endl<<"---------- ADVERSAIRE ----------"<<std::endl;

	std::cout<<getGraphe().toStr(selected1, selected2)<<std::endl;

	std::cout<<"------------- VOUS -------------"<<std::endl;
	for (size_t i=0; i<reserve.size(); i++)
		if (reserve.at(i)->getCamp() == joueur_courant) {
			g.addPiece(*reserve.at(i), c);
			std::cout<<"<"<<g.getCase(c)<<">";
			g.supprPiece(c);
		}
	std::cout<<std::endl<<"--------------------------------"<<std::endl;

	std::cout<<std::endl;
}

// Affiche le plateau avec une case sélectionnée dans le graphe et une dans la main du joueur
void Plateau::afficher(const Piece& p, const Coords& selected) const {
	Graphe g;
	const Coords c(0, 0);

	bool joueur_courant = p.getCamp();

	std::cout<<"--------------------------------"<<std::endl;
	for (size_t i=0; i<reserve.size(); i++)
		if (reserve.at(i)->getCamp() != joueur_courant) {
			g.addPiece(*reserve.at(i), c);
			std::cout<<"<"<<g.getCase(c)<<">";
			g.supprPiece(c);
		}
	std::cout<<std::endl<<"---------- ADVERSAIRE ----------"<<std::endl;

	std::cout<<getGraphe().toStr(selected)<<std::endl;

	std::cout<<"------------- VOUS -------------"<<std::endl;
	for (size_t i=0; i<reserve.size(); i++)
		if (reserve.at(i)->getCamp() == joueur_courant) {
			g.addPiece(*reserve.at(i), c);

			if (&p == reserve.at(i))
				std::cout<<"\033[32m<"<<g.getCase(c)<<">\033[0m";
			else std::cout<<"<"<<g.getCase(c)<<">";
			g.supprPiece(c);
		}
	std::cout<<std::endl<<"--------------------------------"<<std::endl;

	std::cout<<std::endl;
}

// Affiche le plateau avec une pièce sélectionnée dans la main du joueur
void Plateau::afficher(const Piece& p) const {
	Graphe g;
	const Coords c(0, 0);

	bool joueur_courant = p.getCamp();

	std::cout<<"--------------------------------"<<std::endl;
	for (size_t i=0; i<reserve.size(); i++)
		if (reserve.at(i)->getCamp() != joueur_courant) {
			g.addPiece(*reserve.at(i), c);
			std::cout<<"<"<<g.getCase(c)<<">";
			g.supprPiece(c);
		}
	std::cout<<std::endl<<"---------- ADVERSAIRE ----------"<<std::endl;

	std::cout<<getGraphe().toStr()<<std::endl;

	std::cout<<"------------- VOUS -------------"<<std::endl;
	for (size_t i=0; i<reserve.size(); i++)
		if (reserve.at(i)->getCamp() == joueur_courant) {
			g.addPiece(*reserve.at(i), c);

			if (&p == reserve.at(i))
				std::cout<<"\033[32m<"<<g.getCase(c)<<">\033[0m";
			else std::cout<<"<"<<g.getCase(c)<<">";
			g.supprPiece(c);
		}
	std::cout<<std::endl<<"--------------------------------"<<std::endl;

	std::cout<<std::endl;
}


/*! \brief Pour savoir si la pièce est dans la réserve.
*/
bool Plateau::inReserve(const Piece* p) const {
	auto i = 0;
	while (i < reserve.size() && reserve.at(i) != p) i++;

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

/*! \brief Remplit la réserve du plateau avec les pièces données.
*/
void Plateau::fillReserve(const std::vector<Piece*>& pieces) {
	for (auto piece:pieces) {
		addPieceReserve(*piece);
	}
}

/*! \brief Ajoute une pièce à la réserve
*/
void Plateau::addPieceReserve(const Piece& p) {
	if (!inReserve(p)) {
		reserve.push_back(&p);
		memoire.push_back(ReminderPiece(p));
	}
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
const Coords* Plateau::coordsPiece(const Piece* p) const {
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

/*! \brief Échange les adresses des anciennes pièces avec des nouvelles
*/
void Plateau::piecesCoherence(const std::vector<Piece*>& pieces) {

	std::vector<size_t> updated;
	ReminderPiece* rem;
	const Coords* coords;
	const Piece* rem_adresse;
	size_t i;

	// parcours de la liste des nouvelles pièces
	for (auto piece:pieces) {
		
		i=0;
		// récupération d'une ancienne pièce compatible
		for (size_t i=0; i<memoire.size(); i++) {
			// pièce compatible si pas déjà mise à jour, et si camp et type correspondent
			if (std::find(updated.begin(), updated.end(), i) == updated.end()) {
				rem = &memoire.at(i);
				
				if (rem->getType() == piece->getType() && rem->getCamp() == piece->getCamp()) {

					// récupération de l'emplacement de l'ancienne pièce
					coords = coordsPiece(rem->getAdresse());

					// changement de l'adresse de la pièce si elle est dans la réserve
					if (coords == nullptr) {
						auto ite = std::find(reserve.begin(), reserve.end(), rem->getAdresse());
						if (ite==reserve.end()) throw runtime_error("ERROR Plateau::piecesCoherence : réserve corrompue;.");
						*ite = piece;
					}
					// changement de l'adresse de la pièce si elle est dans le graphe
					else {
						getMutableGraphe().changePiece(*coords, piece, rem->getAdresse());
					}
					rem->setAdresse(piece);
					updated.push_back(i);
				}
			}
		}
	}
}

void Plateau::piecesCoherence(const std::vector<Piece*>& pieces1, const std::vector<Piece*>& pieces2) {
	std::vector<Piece*> pieces = pieces1;
	pieces.insert(pieces.end(), pieces2.begin(), pieces2.end());
	piecesCoherence(pieces);
}