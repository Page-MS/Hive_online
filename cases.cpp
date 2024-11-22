#include "cases.h"

// METHODES CASE
bool Case::hasPiece(const Piece* p) const { //renvoie True si pièce est sur la case, False sinon
    bool has_piece = false;
    auto ite = begin();
    auto end_ite = end();

    // parcourt toutes les pièces dans la case, s'arrête quand la pièce a été trouvée ou que l'on a atteint la fin
    while (ite!=end_ite && !has_piece) {
        ite++;
        has_piece = ite.getCurrent()==p;
    }
    return has_piece;
}

void Case::addPiece(const Piece* p) { //erreur si pièce est déjà sur la case
    if (hasPiece(p)) throw "Pièce déjà sur cette case.";
    pieces.push_back(p);
}

void Case::supprPiece() { //supprime la pièce la plus haut placée
    // erreur si aucune pièce à supprimer sur la case
    if (empty()) throw "Case non occupée.";
    pieces.pop_back();
}

void Case::clear() { //supprime toutes les pièces
    // erreur si aucune pièce à supprimer sur la case
    if (empty()) throw "Case déjà vide.";

    for (unsigned int i=getNbPieces() ; i>0 ; i--) supprPiece();
}

// METHODES GRAPHE
Graphe::~Graphe() {
    // supprime toutes les cases
    auto ite = getIterator();
    auto end_ite_c = ite;
    end_ite_c.endColonne();
    auto end_ite_l = ite;

    while (ite.getVectorColonne()!=end_ite_c.getVectorColonne()) {
        end_ite_l.endLigne();
        while (ite.getVectorColonne()!=end_ite_c.getVectorColonne()) {
            delete ite.getMutableCurrent();
            ite.nextLigne();
        }
        end_ite_l.nextColonne();
        ite.nextColonne();
    }
}


Graphe::Iterator Graphe::findCasePlace(double c, double l) const { //renvoie itérateur pointant vers l'emplacement de la case (existante ou non)
    // pointe directement sur la case si elle existe, sur une autre ou la fin d'une ligne/colonne sinon
    auto ite = getIterator();
    auto end_ite = getIterator(); end_ite.endColonne();

    while (ite!=end_ite && ite.getCurrent().getColonne()<c) ite.nextColonne();

    //si colonne déjà occupée
    if (ite!=end_ite && ite.getCurrent().getColonne()==c) {
        end_ite.endLigne();
        while (ite!=end_ite && ite.getCurrent().getLigne()<l) ite.nextLigne();
    }

    return ite;
}


Case* Graphe::getMutableCase(double c, double l) const { //renvoie pointeur nul si case n'existe pas
    if (nb_cases==0 || c>max_x || c<min_x || l>max_y || l<min_x) return nullptr;

    auto ite = getIterator();
    auto end_ite = getIterator() ;
    end_ite.endColonne();

    while (ite!=end_ite && ite.getCurrent().getColonne()<c ) ite.nextColonne();

    if (ite==end_ite || ite.getCurrent().getColonne()>c ) return nullptr;

    end_ite.goToVectorColonne(ite.getVectorColonne());
    end_ite.endLigne();

    while (ite!=end_ite && ite.getCurrent().getLigne()<l ) ite.nextLigne();

    if (ite==end_ite || ite.getCurrent().getLigne()>l ) return nullptr;

    return ite.getMutableCurrent();
}

Case* Graphe::getMutableCase(const Coords& c) const {
    return getMutableCase(c.getX(), c.getY());
}

const Case& Graphe::getCase(double c, double l) const { //erreur si case pas dans graphe
    Case* pt = getMutableCase(c, l);
    if (pt==nullptr) throw "Case n'existe pas.";
    return *pt;
}

const Case& Graphe::getCase(const Coords& c) const {
    Case* pt = getMutableCase(c);
    if (pt==nullptr) throw "Case n'existe pas.";
    return *pt;
}

const Coords Graphe::coordsAdjacent(const Coords& c, unsigned int side) const { //renvoie coordonnées de case adjacente (même si adjacente inexistante)
    if (side == 0) return coordsNorth(c);
    if (side == 1) return coordsNorthEast(c);
    if (side == 2) return coordsSouthEast(c);
    if (side == 3) return coordsSouth(c);
    if (side == 4) return coordsSouthWest(c);
    if (side == 5) return coordsNorthWest(c);
    throw "Côté invalide.";
}


void Graphe::addPiece(const Piece& p, const Coords& c) { //erreur si case inexistante ou contient déjà la pièce
    Case* ca = getMutableCase(c);

    if (ca==nullptr) throw "Case non inexistante.";
    if (ca->hasPiece(&p)) throw "Case contient déjà la pièce.";

    ca->addPiece(&p);
}

void Graphe::addCase(const Coords& c) { //erreur si case existe déjà
    auto ite = findCasePlace(c);
    auto end_ite = ite;
    end_ite.endColonne();

    // si colonne inédite et à la fin du tableau, ajout d'une nouvelle colonne à la fin et création de la nouvelle case
    if (ite.getVectorColonne()==end_ite.getVectorColonne()) {
        std::vector<Case*> new_colonne;
        Case* new_case = new Case(c);

        new_colonne.push_back( new_case );
        cases.push_back(new_colonne);

        return;
    }

    // si colonne inédite dans le tableau, ajout d'une nouvelle colonne et création de la nouvelle case
    if (ite.getCurrentColonne()!=c.getX()) {
        std::vector<Case*> new_colonne;
        Case* new_case = new Case(c);

        new_colonne.push_back( new_case );

        auto vect_ite = cases.begin();
        for (unsigned int i=0; i<ite.getVectorColonne(); i++) vect_ite++;

        cases.emplace(vect_ite, new_colonne);

        return;
    }

    end_ite.goToVectorColonne( ite.getVectorColonne() );
    end_ite.endLigne();

    // si colonne pré-existante et case inédite à la fin du tableau, création de la nouvelle case à la fin du tableau
    if (ite.getVectorLigne()==end_ite.getVectorLigne()) {
        Case* new_case = new Case(c);

        cases[ite.getVectorColonne()].push_back( new_case );
        
        return;
    }

    // si colonne pré-existante et case inédite dans le tableau, création de la nouvelle case
    if (ite.getCurrentLigne()!=c.getY()) {
        Case* new_case = new Case(c);

        auto vect_ite = cases[ite.getVectorColonne()].begin();
        for (unsigned int i=0; i<ite.getVectorLigne(); i++) vect_ite++;

        cases[ite.getVectorColonne()].emplace(vect_ite, new_case);

        return;
    }

    if (ite.getCurrent().getCoords()==c) throw "Case existe déjà.";
}


// iterator
void Graphe::Iterator::goToColonne(double c) { //coordonnées "réelles", erreur si colonne n'existe pas
    auto end_ite = *this;
    end_ite.endColonne();

    firstColonne();

    while (*this!=end_ite && getCurrent().getColonne()<c) nextColonne();
    if (*this==end_ite || getCurrent().getColonne()>c) throw "Colonne non occupée.";
}

void Graphe::Iterator::goToLigne(double l) { //coordonnées "réelles", erreur si ligne n'existe pas dans colonne actuelle
    auto end_ite = *this;
    end_ite.goToVectorColonne(getVectorColonne());
    end_ite.endLigne();

    firstLigne();

    while (*this!=end_ite && getCurrent().getLigne()<l) nextLigne();
    if (*this==end_ite || getCurrent().getColonne()>l) throw "Ligne non occupée dans cette colonne.";
}


void Graphe::Iterator::goToCoords(double c, double l) { //coordonnées "réelles", erreur si n'existent pas
    goToColonne(c);
    goToLigne(l);
}

void Graphe::Iterator::goToCoords(const Coords& c) {
    goToCoords(c.getX(), c.getY());
}