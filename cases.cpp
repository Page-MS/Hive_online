#include "cases.h"

// AFFICHAGE
std::ostream& operator<<(std::ostream& flux, const Case& c) {
    flux<<c.showCase();
    return flux;
}

std::ostream& operator<<(std::ostream& flux, const Graphe& g) {
    flux<<"Graphe :"<<std::endl;

    // variables
    std::vector<std::string> str (g.getMaxY() - g.getMinY() + 1, "");
    Coords coords (g.getMinX(), g.getMinY());
    int i_vect = 0;

    //itérateurs
    auto ite = g.getIterator();
    auto end_ligne_ite = g.getIterator();
    end_ligne_ite.endLigne();
    auto end_colonne_ite = g.getIterator();
    end_colonne_ite.endColonne();

    while (coords.getX()<=g.getMaxX()) {
        while(coords.getY()<=g.getMaxY()) {
            // si on est sur une case existante, on l'affiche, puis on déplace l'itérateur à la prochaine case
            if (coords == ite.getCurrent().getCoords() ) {
                str.at(i_vect) += "< " + ite.getCurrent().showCase() + " >";

                // déplacement de l'itérateur, retour au début si fin atteinte
                ite.nextLigne();
                if (ite==end_ligne_ite) {

                    ite.nextColonne();
                    if (ite.onSameColonne(end_colonne_ite)) {
                        ite.firstColonne();
                        ite.firstLigne();
                    }
                    else {
                        ite.firstLigne();
                        end_ligne_ite = ite;
                        end_ligne_ite.endLigne();
                    }
                }
            }
            // si on est sur une case non existante, on affiche un vide
            else if (isCaseCoords(coords)) {
                str.at(i_vect) += caseVoid();
            }

            // si on est sur une bordure de case
            else {
                // si la case juste à gauche n'existe pas, on affiche des frontières latérales vides
                if (!g.hasCase(coords + Coords(-1,0)))
                    str.at(i_vect) += " ";
                // si une case juste en haut ou en bas existe, on affiche ses frontières
                if ( g.hasCase(coords + Coords(0,-1)) || g.hasCase(coords + Coords(0,1)) )
                    str.at(i_vect) += caseBorder();
                else str.at(i_vect) += caseBorderVoid();
            }
            
            coords.addY(1);
            i_vect++;
        }

        coords.addX(1);
        coords.setY(g.getMinY());
        i_vect=0;
    }
    
    for (i_vect=0; i_vect<str.size(); i_vect++)
        flux<<str.at(i_vect)<<std::endl;

    return flux;
}

std::string caseBorder() {
    string str;
    for (auto i=0 ; i < 2 + Case::getNameLength() ; i++)
        str = str + "-";
    return str;
}

std::string caseVoid() {
    string str;
    for (auto i=0 ; i < 4 + Case::getNameLength() ; i++)
        str = str + " ";
    return str;
}

std::string caseBorderVoid() {
    string str;
    for (auto i=0 ; i < 2 + Case::getNameLength() ; i++)
        str = str + " ";
    return str;
}

// METHODES CASE
std::string Case::showCase() const {
    string str;
    if (empty()) str="XX";
    else {
        TYPE_PIECE p = getUpperPiece().getType();
        
        switch (p) {
            case TYPE_PIECE::Scarabee :
                str="Sc";
                break;
            case TYPE_PIECE::Abeille :
                str="Ab";
                break;
            case TYPE_PIECE::Fourmi :
                str="Fo";
                break;
            case TYPE_PIECE::Sauterelle :
                str="Sa";
                break;
            case TYPE_PIECE::Araignee :
                str="Ar";
                break;
            case TYPE_PIECE::Moustique :
                str="Mo";
                break;
            case TYPE_PIECE::Coccinelle :
                str="Co";
                break;
            default :
                throw exception("ERROR Case::showCase : Ce type de pièce n'est pas pris en compte.");
        }
    }

    return str;
}

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
    if (hasPiece(p)) throw exception("ERROR Case::addPiece : Pièce déjà sur cette case.");
    pieces.push_back(p);
}

void Case::supprPiece() { //supprime la pièce la plus haut placée
    // erreur si aucune pièce à supprimer sur la case
    if (empty()) throw exception("ERROR Case::supprPiece : Case non occupée.");
    pieces.pop_back();
}

void Case::clear() { //supprime toutes les pièces
    // erreur si aucune pièce à supprimer sur la case
    if (empty()) throw exception("ERROR Case::clear : Case déjà vide.");

    for (unsigned int i=getNbPieces() ; i>0 ; i--) supprPiece();
}

const Piece& Case::getUpperPiece() const { //erreur si pas de pièce sur la case
    if (empty()) throw exception("ERROR Case::getUpperPiece : Case vide, aucune pièce à récupérer");
    auto ite = end()--;

    return *(ite.getCurrent());
};

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
    if (ite.getVectorColonne()!=end_ite.getVectorColonne() && ite.getCurrent().getColonne()==c) {
        end_ite=ite;
        end_ite.endLigne();
        while (ite!=end_ite && ite.getCurrent().getLigne()<l) ite.nextLigne();
    }
    
    return ite;
}


Case* Graphe::getMutableCase(double c, double l) const { //renvoie pointeur nul si case n'existe pas
    // renvoie pointeur nul si graphe vide, ou coordonnées hors des extrêmes du graphe
    if (nb_cases==0 || c>max_x || c<min_x || l>max_y || l<min_y) return nullptr;

    //création des itérateurs
    auto ite = getIterator();
    auto end_ite = getIterator() ;
    end_ite.endColonne();

    // parcourt les colonnes jusqu'à arriver à la fin ou trouver celle qui contient peut-être la case
    while (!ite.onSameColonne(end_ite) && ite.getCurrent().getColonne()<c ) ite.nextColonne();
    
    // renvoie pointeur nul si tout parcouru sans succès
    if (ite.onSameColonne(end_ite) || ite.getCurrent().getColonne()>c ) return nullptr;

    end_ite=ite;
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
    if (pt==nullptr) throw exception("ERROR Graphe::getCase : Case n'existe pas.");
    return *pt;
}

const Case& Graphe::getCase(const Coords& c) const {
    Case* pt = getMutableCase(c);
    if (pt==nullptr) throw exception("ERROR Graphe::getCase : Case n'existe pas.");
    return *pt;
}

const Coords Graphe::coordsAdjacent(const Coords& c, unsigned int side) const { //renvoie coordonnées de case adjacente (même si adjacente inexistante)
    if (side == 0) return coordsNorth(c);
    if (side == 1) return coordsNorthEast(c);
    if (side == 2) return coordsSouthEast(c);
    if (side == 3) return coordsSouth(c);
    if (side == 4) return coordsSouthWest(c);
    if (side == 5) return coordsNorthWest(c);
    throw exception("ERROR Graphe::coordsAdjacent : Côté invalide.");
}

void Graphe::updateAttributes(const Coords& c) {
    nb_cases++;

    // si nouvelle colonne à gauche ou à droite, mettre à jour min/max de X
    if (max_x<c.getX()) max_x=c.getX();
    else if (min_x>c.getX()) min_x=c.getX();

    // si nouvelle ligne en haut ou en bas, mettre à jour min/max de Y
    if (max_y<c.getY()) max_y=c.getY();
    else if (min_y>c.getY()) min_y=c.getY();
}

void Graphe::addPiece(const Piece& p, const Coords& c) { //erreur si case inexistante ou contient déjà la pièce
    Case* ca = getMutableCase(c);

    if (ca==nullptr) throw exception("ERROR Graphe::addPiece : Case non existante.");
    if (ca->hasPiece(&p)) throw exception("ERROR Graphe::addPiece : Case contient déjà la pièce.");

    ca->addPiece(&p);

    // ajout de cases adjacentes vides s'il n'y en a pas
    Coords coords_adjac(0, 0);
    for (unsigned int i=0; i<6; i++) {
        coords_adjac = coordsAdjacent(c, i);
        if (!hasCase(coords_adjac))
            addCase(coords_adjac);
    }
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

        updateAttributes(c);
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

        updateAttributes(c);
        return;
    }

    end_ite.goToVectorColonne( ite.getVectorColonne() );
    end_ite.endLigne();

    // si colonne pré-existante et case inédite à la fin du tableau, création de la nouvelle case à la fin du tableau
    if (ite.getVectorLigne()==end_ite.getVectorLigne()) {
        Case* new_case = new Case(c);

        cases[ite.getVectorColonne()].push_back( new_case );
        
        updateAttributes(c);
        return;
    }

    // si colonne pré-existante et case inédite dans le tableau, création de la nouvelle case
    if (ite.getCurrentLigne()!=c.getY()) {
        Case* new_case = new Case(c);

        auto vect_ite = cases[ite.getVectorColonne()].begin();
        for (unsigned int i=0; i<ite.getVectorLigne(); i++) vect_ite++;

        cases[ite.getVectorColonne()].emplace(vect_ite, new_case);

        updateAttributes(c);
        return;
    }

    // si case déjà existante, erreur
    if (ite.getCurrent().getCoords()==c) throw exception("ERROR Graphe::addCase : Case existe déjà.");
}


// iterator
void Graphe::Iterator::goToColonne(double c) { //coordonnées "réelles", erreur si colonne n'existe pas
    auto end_ite = *this;
    end_ite.endColonne();

    firstColonne();

    while (*this!=end_ite && getCurrent().getColonne()<c) nextColonne();
    if (*this==end_ite || getCurrent().getColonne()>c) throw exception("ERROR Graphe::Iterator::goToColonne : Colonne non occupée.");
}

void Graphe::Iterator::goToLigne(double l) { //coordonnées "réelles", erreur si ligne n'existe pas dans colonne actuelle
    auto end_ite = *this;
    end_ite.goToVectorColonne(getVectorColonne());
    end_ite.endLigne();

    firstLigne();

    while (*this!=end_ite && getCurrent().getLigne()<l) nextLigne();
    if (*this==end_ite || getCurrent().getColonne()>l) throw exception("ERROR Graphe::Iterator::goToLigne : Ligne non occupée dans cette colonne.");
}


void Graphe::Iterator::goToCoords(double c, double l) { //coordonnées "réelles", erreur si n'existent pas
    goToColonne(c);
    goToLigne(l);
}

void Graphe::Iterator::goToCoords(const Coords& c) {
    goToCoords(c.getX(), c.getY());
}
