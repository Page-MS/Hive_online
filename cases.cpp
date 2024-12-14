#include "cases.h"
#include <bits/stdc++.h>
// AFFICHAGE
std::ostream& operator<<(std::ostream& flux, const Case& c) { // Affichage d'une case, peut être ajouté au cout<<

    flux<<c.strCase();
    
    return flux;
}

std::ostream& operator<<(std::ostream& flux, const Graphe& g) {
    /* Affichage du graphe, peut être ajouté au cout<< */

    flux<<std::endl;
    if (g.empty()) {
        flux<<"Graphe vide."<<std::endl;
        return flux;
    }

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
                str.at(i_vect) += "<" + ite.getCurrent().strCase() + ">";

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

/*! \brief Pour affichage du graphe, renvoie un string de frontière de case (plusieurs tirets côte à côte).
*/
std::string caseBorder() {
    string str;
    for (auto i=0 ; i < 2 + Case::getNameLength() ; i++)
        str = str + "-";
    return str;
}

/*! \brief Pour affichage du graphe, renvoie un vide (plusieurs espaces côte à côte).
*/
std::string caseVoid() {
    string str;
    for (auto i=0 ; i < 3 + Case::getNameLength() ; i++)
        str = str + " ";
    return str;
}

/*! \brief Pour affichage du graphe, renvoie un espace (symbolise qu'il n'y a pas de case directement à gauche).
*/
std::string caseBorderVoid() {
    string str;
    for (auto i=0 ; i < 2 + Case::getNameLength() ; i++)
        str = str + " ";
    return str;
}

/*! \brief Pour savoir si deux cases sont sur la même ligne (donc atteignable par un saut)
*/
bool onStraightLine(const Coords& c1, const Coords& c2) {
    return (c1.getX()==c2.getX() ||
                (
                    abs(c1.getX()-c2.getX()) &&
                    abs(c1.getY()-c2.getY())
                )
            );
}

// METHODES CASE
/*! \brief Pour affichage d'une case, mais renvoie uniquement le string à utiliser.
*/
std::string Case::strCase() const {

    if (empty()) return " :: ";

    std::string symbole;
    if (getUpperPiece().getCamp())
        symbole="+";
    else symbole=".";

    return symbole + getUpperPiece().strPiece() + symbole;
}

/*! \brief Permet de savoir si une pièce est contenue dans la case impliquée, pour supprimer la pièce ou récupérer ses coordonnées.
*/
bool Case::hasPiece(const Piece& p) const { //renvoie True si pièce est sur la case, False sinon
    bool has_piece = false;
    auto ite = begin();

    // parcourt toutes les pièces dans la case, s'arrête quand la pièce a été trouvée ou que l'on a atteint la fin
    while (!ite.atEnd() && !has_piece) {
        if (ite.getCurrent() == &p) return true;
        ite++;
    }

    return has_piece;
}

/*! \brief [PRIVÉ] Pour ajouter une pièce sur une case, tout en haut de la pile (erreur si pièce déjà sur la case).
    Utiliser Case::hasPiece pour savoir si pièce sur la case.
*/
void Case::addPiece(const Piece& p) {
    if (hasPiece(p)) throw runtime_error("ERROR Case::addPiece : Piece deja sur cette case.");

    pieces.push_back(&p);
}

/*! \brief [PRIVÉ] Pour supprimer la pièce en haut de la pile de pièces de la case (erreur si case vide).
    Utiliser Case::empty pour savoir si case vide.
*/
void Case::supprPiece() { //supprime la pièce la plus haut placée
    if (empty()) throw runtime_error("ERROR Case::supprPiece : Case non occupee.");

    pieces.pop_back();
}

/*! \brief [PRIVÉ] Pour supprimer toutes les pièces présentes sur la case (erreur si case vide).
    Utiliser Case::empty pour savoir si case vide.
*/
void Case::clear() { //supprime toutes les pièces
    // erreur si aucune pièce à supprimer sur la case
    if (empty()) throw runtime_error("ERROR Case::clear : Case deja vide.");

    for (unsigned int i=getNbPieces() ; i>0 ; i--) supprPiece();
}

/*! \brief Pour récupérer la pièce située tout en haut de la pile de pièces (erreur si case vide).
    Utiliser Case::empty pour savoir si case vide.
*/
const Piece& Case::getUpperPiece() const { //erreur si pas de pièce sur la case
    if (empty()) throw runtime_error("ERROR Case::getUpperPiece : Case vide, aucune piece a recuperer");
    auto ite = end()--;

    return *ite;
};

/*! \brief Pour savoir si une pièce peut effectuer une action depuis cette case (pièce coincée si pas sur cette case).
*/
bool Case::isPieceStuck(const Piece& p) const {
    return (empty() || &getUpperPiece()!=&p);
}

// METHODES GRAPHE
Graphe::~Graphe() {
    // supprime toutes les cases
    auto ite = getIterator();

    while (!ite.atEndColonne()) {
        while (!ite.atEndLigne()) {
            delete ite.getMutableCurrent();
            ite.nextLigne();
        }
        ite.firstLigne();
        ite.nextColonne();
    }
}

Graphe::Graphe(const Graphe& g) {
    max_x=0;
    min_x=0;
    max_y=0;
    min_y=0;
    nb_inhabited_cases=0;
    nb_cases=0;

    *this = g;
}

Graphe& Graphe::operator=(const Graphe& g) {
    clear();

    auto ite = g.getIterator();
    Case* c = nullptr;

    // on parcourt toutes les cases du graphe à copier
    while (!ite.atEndColonne()) {
        while (!ite.atEndLigne()) {
            c = addCase(ite.getCurrent().getCoords());
            
            for (auto i=ite.getCurrent().begin(); i!=ite.getCurrent().end(); i++) {
                c->addPiece(*i);
                nb_inhabited_cases++;
            }
            ite.nextLigne();
        }
        ite.firstLigne();
        ite.nextColonne();
    }

    return *this;
}

// getters case
/*! \brief [PRIVÉ] Pour récupérer une case modifiable en fonction de ses coordonnées.
*/
Case* Graphe::getMutableCase(double c, double l) const { //renvoie pointeur nul si case n'existe pas
    
    //création de l'itérateur
    auto ite = getIterator();

    // parcourt les colonnes jusqu'à arriver à la fin ou trouver celle qui contient peut-être la case
    while (!ite.atEndColonne() && ite.getCurrent().getColonne()<c ) ite.nextColonne();
    
    // renvoie pointeur nul si tout parcouru sans succès
    if (ite.atEndColonne() || ite.getCurrent().getColonne()>c ) return nullptr;

    while (!ite.atEndLigne() && ite.getCurrent().getLigne()<l ) ite.nextLigne();

    if (ite.atEndLigne() || ite.getCurrent().getLigne()>l ) return nullptr;

    return ite.getMutableCurrent();
}

/*! \brief [PRIVÉ] Pour récupérer une case modifiable en fonction de ses coordonnées, en étant certain qu'elle existe.
*/
Case& Graphe::getExistentCase(const Coords& c) const {
    auto ite = getIterator();
    ite.goToCoords(c);
    return *ite.getMutableCurrent();
}

/*! \brief Pour récupérer une case non modifiable en fonction de ses coordonnées (erreur si case n'existe pas).
    Utiliser Graphe::hasCase pour savoir si case existe.
*/
const Case& Graphe::getCase(double c, double l) const { //erreur si case pas dans graphe
    Case* pt = getMutableCase(c, l);
    if (pt==nullptr) throw runtime_error("ERROR Graphe::getCase : Case n'existe pas.");
    return *pt;
}

// getters coords
/*! \brief Pour trouver l'emplacement supposé d'une case (si case existe, l'itérateur pointe directement sur la case, sinon sur la case triée après ou sur la fin d'une ligne/colonne).
*/
Graphe::Iterator Graphe::findCasePlace(double c, double l) const { //renvoie itérateur pointant vers l'emplacement de la case (existante ou non)
    // pointe directement sur la case si elle existe, sur une autre ou la fin d'une ligne/colonne sinon
    auto ite = getIterator();
    auto end_ite = getIterator(); end_ite.endColonne();

    while (!ite.atEndColonne() && ite.getCurrent().getColonne()<c) ite.nextColonne();

    //si colonne déjà occupée
    if (!ite.atEndColonne() && ite.getCurrent().getColonne()==c)
        while (!ite.atEndLigne() && ite.getCurrent().getLigne()<l) ite.nextLigne();
    
    return ite;
}

/*! \brief Pour récupérer les coordonnées d'un adjacent d'une case (qu'elle existe ou pas).
    Utiliser Graphe::hasCase pour savoir si case existe.
    Argument side = 0~5, 0 -> adjacent nord, puis dans sens horaire.
*/
Coords Graphe::coordsAdjacent(const Coords& c, unsigned int side) const { //renvoie coordonnées de case adjacente (même si adjacente inexistante)
    if (side == 0) return coordsNorth(c);
    if (side == 1) return coordsNorthEast(c);
    if (side == 2) return coordsSouthEast(c);
    if (side == 3) return coordsSouth(c);
    if (side == 4) return coordsSouthWest(c);
    if (side == 5) return coordsNorthWest(c);
    throw runtime_error("ERROR Graphe::coordsAdjacent : Cote invalide.");
}

/*! \brief Renvoie la liste des coordonnées adjacentes à une case.
*/
std::vector<Coords> Graphe::coordsAllAdjacents(const Coords& c) const {
    std::vector<Coords> coords;

    for (auto i=0; i<6; i++) {
        coords.push_back(coordsAdjacent(c, i));
    }

    return coords;
}

/*! \brief Renvoie la liste des coordonnées adjacentes à une case dont les cases existent dans le graphe.
*/
std::vector<Coords> Graphe::coordsExistentAdjacents(const Coords& c) const {
    std::vector<Coords> coords;

    for (auto i=0; i<6; i++) {
        if (hasCase(coordsAdjacent(c, i)))
            coords.push_back(coordsAdjacent(c, i));
    }

    return coords;
}

/*! \brief Renvoie la liste des coordonnées adjacentes à une case dont les cases existent dans le graphe et ne sont pas vides.
*/
std::vector<Coords> Graphe::coordsInhabitedAdjacents(const Coords& c) const {
    std::vector<Coords> coords;

    for (auto i=0; i<6; i++) {
        if (hasCase(coordsAdjacent(c, i)) && !getCase(coordsAdjacent(c, i)).empty()) {
            coords.push_back(coordsAdjacent(c, i));
        }
    }

    return coords;
}


/*! \brief [PRIVÉ] Pour connaître les coordonnées d'une pièce (pointeur nul si pièce pas dans graphe).
*/
const Coords* Graphe::coordsPiecePointer(const Piece& p) const {
    // création itérateur
    auto ite = getIterator();

    // parcourt tout le graphe jusqu'à pièce trouvée
    while (!ite.atEndColonne()) {
        while (!ite.atEndLigne()) {
            if (ite.getCurrent().hasPiece(p)) return &ite.getCurrent().getCoords();
            ite.nextLigne();
        }
        
        ite.nextColonne();
        ite.firstLigne();
    }
    
    return nullptr;
}

/*! \brief Pour connaître les coordonnées d'une pièce sur le graphe (erreur si pièce pas dans graphe).
*/
const Coords& Graphe::coordsPiece(const Piece& p) const {
    const Coords* coords = coordsPiecePointer(p);
    
    if (coords==nullptr) throw runtime_error("ERROR Graphe::coordsPiece : Piece pas dans graphe.");
    
    return *coords;
}

/*! \brief Pour savoir si une pièce peut effectuer une action (erreur si pièce pas dans graphe).
    Utiliser Graphe::hasPiece pour savoir si la pièce est sur le graphe.
*/
bool Graphe::isPieceStuck(const Piece& p) const {
    const Case& c = getExistentCase(coordsPiece(p));

    return c.isPieceStuck(p);
}

/*! \brief Pour savoir si une case est entourée de cases vides, pas en contact avec la ruche.
*/
bool Graphe::isIsland(const Coords& c) const {
    unsigned int i = 0;

    // on s'arrête quand tous les adjacents ont été parcourus, ou quand une case non vide a été trouvée.
    while (i<=5 && (!hasCase(coordsAdjacent(c, i)) || getCase(coordsAdjacent(c, i)).empty()))
        i++;

    return i>5;
}

/*! \brief Pour savoir si une case est entourée de cases occupées, par exemple si la reine est encerclée.
*/
bool Graphe::isSurrounded(const Coords& c) const {
    const Case* ca;

    // on s'arrête quand tous les adjacents ont été parcourus, ou quand une case vide a été trouvée.
    for (unsigned int i=0; i<=5; i++) {
        
        ca = getMutableCase(coordsAdjacent(c, i));
        if (ca==nullptr || ca->empty()) return false;
    }

    return true;
}

#include <stdexcept>

/*! \brief Renvoie si la ruche serait séparée dans le cas du déplacement d'une pièce depuis des coordonnées précises (erreur si coordonnées pas dans graphe ou case vide).
*/
bool Graphe::wouldHiveBreak(const Coords& c) const {
    const Case* ca = getMutableCase(c);
    if (ca==nullptr) throw std::runtime_error("ERROR Graphe::wouldHiveBreak : Case inexistante.");
    if (ca->empty()) throw std::runtime_error("ERROR Graphe::wouldHiveBreak : Case vide.");

    // ruche intacte si case contient plus d'une pièce
    if (ca->getNbPieces()>1) return false;

    // vecteur pour stocker les cases explorees
    std::vector<Coords> coords_list = coordsInhabitedAdjacents(ca->getCoords());
    // si la case n'est en contact avec aucune case habitee, ruche brisee
    if (coords_list.empty()) return false;
    // on prend un seul adjacent pour voir si on arrive à parcourir toute la ruche avec
    coords_list.resize(1);


    size_t to_search = 0;
    std::vector<Coords> adjacents;
    
    // on explore autant que possible jusqu'à atteindre la fin du vecteur (donc aucun nouvel adjacent à explorer)
    while (to_search<coords_list.size()) {
        adjacents = coordsExistentAdjacents(coords_list[to_search]);

        for (auto i_adja=0; i_adja<adjacents.size(); i_adja++) {
            if (adjacents[i_adja] != ca->getCoords()
                && std::find(coords_list.begin(), coords_list.end(), adjacents[i_adja]) == coords_list.end()
                && !getCase(adjacents[i_adja]).empty()) {

                coords_list.push_back(adjacents[i_adja]);
            }
        }
        to_search++;
    }

    return coords_list.size() != getNbInhabitedCases()-1;

}

/*! \brief Renvoie si une pièce peut glisser d'une case à sa voisine (ne prend pas en compte la présence ou non de pièce sur la case d'arriver).
*/
bool Graphe::canSlide(const Coords& c, unsigned int side) const {
    if (side<0 || side>5) throw runtime_error("ERROR Graphe::canSlide : Cote invalide.");

    auto adjacent = coordsAdjacent(c, (side+5)%6);
    if (!hasCase(adjacent) || getCase(adjacent).empty()) return true;

    adjacent = coordsAdjacent(c, (side+1)%6);

    return (!hasCase(adjacent) || getCase(adjacent).empty());
}

/*! \brief Renvoie si le joueur d'un camp donné peut poser sa pièce sur une case.
*/
bool Graphe::canPlace(const Coords& c, bool camp) const {
    if (!hasCase(c) || !getCase(c).empty()) return false;

    bool amie=false;
    Case* adjacent;
    for (auto i=0; i<6; i++) {
        adjacent = getMutableCase(coordsAdjacent(c, i));

        if (adjacent!=nullptr && !adjacent->empty()) {
            if (adjacent->getUpperPiece().getCamp()!=camp) return false;
            else amie=true;
        }
    }

    return amie;
}

// modification graphe
/*! \brief [PRIVÉ] Pour mettre à jour attributs de Graphe après ajout d'une nouvelle case (nombre de cases et extrémités gauche/droite/haute/basse).
*/
void Graphe::updateAttributesAdd(double c, double l) {
    nb_cases++;

    // si nouvelle colonne à gauche ou à droite, mettre à jour min/max de X
    if (nb_cases == 1) max_x, min_x = c;
    else if (max_x < c) max_x = c;
    else if (min_x > c) min_x = c;

    // si nouvelle ligne en haut ou en bas, mettre à jour min/max de Y
    if (nb_cases == 1) max_y, min_y = l;
    if (max_y < l) max_y = l;
    else if (min_y > l) min_y = l;
}

/*! \brief [PRIVÉ] Pour mettre à jour attributs de Graphe après suppression d'une nouvelle case (nombre de cases et extrémités gauche/droite/haute/basse).
*/
void Graphe::updateAttributesSuppr(double c, double l) {
    nb_cases--;
    if (nb_cases==0) {
        max_x=0;
        min_x=0;
        max_y=0;
        min_y=0;
        return;
    }
    
    // on ne recherche de nouvelles extrémités que si les anciennes étaient elles-mêmes aux extrémités
    if (c==max_x || c==min_x || l==max_y || l==min_y) {
        auto ite = getIterator();

        // si la colonne est vide, il y a une erreur dans le vecteur cases
        if (ite.atEndLigne()) throw runtime_error("ERROR Graphe::updateAttributes : Colonne vide.");
        if (ite.getCurrentColonne() > min_x) min_x = ite.getCurrentColonne();
        double min_ligne = max_y, max_ligne = min_y;

        while (!ite.atEndColonne()) {
            if (ite.getCurrentLigne() < min_ligne) min_ligne = ite.getCurrentLigne();
                
            ite.endLigne();
            ite.prevLigne();

            if (ite.getCurrentLigne() > max_ligne) max_ligne = ite.getCurrentLigne();

            ite.firstLigne();
            ite.nextColonne();
            if (!ite.atEndColonne() && ite.atEndLigne()) throw runtime_error("ERROR Graphe::updateAttributes : Colonne vide.");
        }
        ite.prevColonne();
        if (ite.getCurrentColonne() < max_x) max_x = ite.getCurrentColonne();
        min_y = min_ligne;
        max_y = max_ligne;
    }
}

/*! \brief [PRIVÉ] Pour mettre à jour attributs de Graphe après ajout ou suppression d'une nouvelle case (nombre de cases et extrémités gauche/droite/haute/basse).
    1 : ajout de la case
    0 : suppression de la case
    2 (default) : programme détermine lui-même
*/
void Graphe::updateAttributes(const Coords& c, size_t modif) {
    if (modif!=0 && modif!=1) modif= hasCase(c);

    if (modif==1) {
        return updateAttributesAdd(c);
    }
    if (modif==0) {
        return updateAttributesSuppr(c);
    }
    else {
        throw runtime_error("ERROR updateAttributes : argument de modification invalide, raison inconnue.");
    }
}

/*! \brief [PRIVÉ] Pour ajouter une case à des coordonnées précises (erreur si case existe déjà).
    Utiliser Graphe::hasCase pour savoir si case existe.
*/
Case* Graphe::addCase(const Coords& c) { //erreur si case existe déjà

    auto ite = findCasePlace(c);
    Case* new_case;

    // si colonne inédite et à la fin du tableau, ajout d'une nouvelle colonne à la fin et création de la nouvelle case
    if (ite.atEndColonne()) {
        std::vector<Case*> new_colonne;
        new_case = new Case(c);

        new_colonne.push_back( new_case );
        cases.push_back(new_colonne);

        updateAttributes(c, 1);
    }

    // si colonne inédite dans le tableau, ajout d'une nouvelle colonne et création de la nouvelle case
    else if (ite.getCurrentColonne()!=c.getX()) {
        std::vector<Case*> new_colonne;
        new_case = new Case(c);

        new_colonne.push_back( new_case );

        auto vect_ite = cases.begin();
        for (unsigned int i=0; i<ite.getVectorColonne(); i++) vect_ite++;

        cases.emplace(vect_ite, new_colonne);

        updateAttributes(c, 1);
    }

    // si colonne pré-existante et case inédite à la fin du tableau, création de la nouvelle case à la fin du tableau
    else if (ite.atEndLigne()) {
        new_case = new Case(c);

        cases[ite.getVectorColonne()].push_back( new_case );
        
        updateAttributes(c, 1);
    }

    // si colonne pré-existante et case inédite dans le tableau, création de la nouvelle case
    else if (ite.getCurrentLigne()!=c.getY()) {
        new_case = new Case(c);

        auto vect_ite = cases[ite.getVectorColonne()].begin();
        for (unsigned int i=0; i<ite.getVectorLigne(); i++) vect_ite++;

        cases[ite.getVectorColonne()].emplace(vect_ite, new_case);

        updateAttributes(c, 1);
    }

    // si case déjà existante, erreur
    else if (ite.getCurrent().getCoords()==c) throw runtime_error("ERROR Graphe::addCase : Case existe deja.");

    return new_case;
}

/*! \brief [PRIVÉ] Pour supprimer une case précise.
*/
void Graphe::supprCase(const Case& c) {
    auto ite = getIterator();
    ite.goToCoords(c.getCoords());

    // suppression de la case
    auto* colonne = &cases.at(ite.getVectorColonne());
    auto i=0;
    while (i<colonne->size() && colonne->at(i)!=&c) i++;

    colonne->erase(colonne->begin() + i );

    // suppression de la colonne vide
    if (colonne->size()==0)
        cases.erase( cases.begin() + ite.getVectorColonne() );

    updateAttributes(c.getCoords(), 0);

    if (!c.empty()) nb_inhabited_cases--;

    c.~Case();
}

/*! \brief [PRIVÉ] Pour supprimer une case à des coordonnées précises (erreur si case n'existe pas).
*/
void Graphe::supprCase(const Coords& c) {

    const Case* ca = getMutableCase(c);
    if (ca==nullptr) throw runtime_error("ERROR Graphe::supprCase : Case n'existe pas.");

    supprCase(*ca);
}

/*! \brief Pour ajouter une pièce à des coordonnées précises (erreur si pièce déjà dans le graphe).
    Utiliser Graphe::hasPiece pour savoir si pièce dans graphe.
*/
void Graphe::addPiece(const Piece& p, Case& c) { //erreur si case inexistante ou contient déjà la pièce
    c<<p;
    if (c.getNbPieces()==1) nb_inhabited_cases++;

    // ajout de cases adjacentes vides s'il n'y en a pas
    Coords coords_adjac(0, 0);

    for (unsigned int i=0; i<6; i++) {
        coords_adjac = coordsAdjacent(c.getCoords(), i);
        if (!hasCase(coords_adjac))
            addCase(coords_adjac);
    }
}

/*! \brief Pour ajouter une pièce à des coordonnées précises (erreur si pièce déjà dans le graphe).
    Utiliser Graphe::hasPiece pour savoir si pièce dans graphe.
*/
void Graphe::addPiece(const Piece& p, const Coords& c) { //erreur si case inexistante ou contient déjà la pièce

    Case* ca = getMutableCase(c);
    if (ca==nullptr) throw runtime_error("ERROR Graphe::addPiece : Case non existante.");

    addPiece(p, *ca);
}

/*! \brief [PRIVÉ] Pour supprimer une pièce du graphe, prend la pièce sur le dessus aux coordonnées indiquées (erreur si case inexistante ou vide).
    Bien vérifier coordonnées de la pièce avant d'exécuter.
*/
void Graphe::supprPiece(Case& c) {
    c--;

    //suppression des cases pas en contact avec la ruche
    if (c.empty()) {
        nb_inhabited_cases--;

        unsigned int i = 0;
        while (i <= 5) {
            const Coords adjacent = coordsAdjacent(c.getCoords(), i);

            Case* adjacase = getMutableCase(adjacent);
            if (adjacase!=nullptr && isDeletable(*adjacase)) {
                supprCase(*adjacase);
                adjacent.~Coords();
            }
            i++;
        }
    }
}

/*! \brief Pour supprimer une pièce du graphe, prend la pièce sur le dessus aux coordonnées indiquées (erreur si case inexistante ou vide).
    Bien vérifier coordonnées de la pièce avant d'exécuter.
*/
void Graphe::supprPiece(const Coords& c) {
    Case* ca = getMutableCase(c);
    if (ca==nullptr) throw runtime_error("ERROR Graphe::supprPiece : Case n'existe pas.");

    supprPiece(*ca);
}

/*! \brief Pour déplacer une pièce du graphe aux coordonnées indiquées (erreur si case inexistante ou pièce coincée).
*/
void Graphe::movePiece(const Piece& p, const Coords& c) {

    const Coords& coords = coordsPiece(p);
    Case& ca_from = getExistentCase(coords);
    if (ca_from.isPieceStuck(p)) throw runtime_error("ERROR Graphe::movePiece : Piece coincee, mouvement impossible.");

    Case* ca_to = getMutableCase(c);
    if (ca_to==nullptr) throw runtime_error("ERROR Graphe::movePiece : Case de destination inexistante.");

    supprPiece(ca_from);
    addPiece(p, *ca_to);
}

/*! \brief Vide entièrement le graphe
*/
void Graphe::clear() {
    if (empty()) return;

    auto ite = getIterator();

    while (!empty()) {
        supprCase(*ite.getMutableCurrent());
        ite = getIterator();
    }
}

// iterator

/*! \brief Pour déplacer l'itérateur sur une colonne précise (erreur si colonne n'existe pas).
    Déplacer l'itérateur "manuellement" pour savoir si colonne existe.
*/
void Graphe::Iterator::goToColonne(double c) { //coordonnées "réelles", erreur si colonne n'existe pas
    firstColonne();

    while (!this->atEndColonne() && getCurrent().getColonne()<c) nextColonne();
    if (this->atEndColonne() || getCurrent().getColonne()>c) throw runtime_error("ERROR Graphe::Iterator::goToColonne : Colonne non occupee.");
}

/*! \brief Pour déplacer l'itérateur sur une ligne précise, en étant déjà sur la bonne colonne (erreur si ligne n'existe pas).
    Utiliser Graphe::hasCase pour savoir si la case existe, ou déplacer l'itérateur "manuellement".
*/
void Graphe::Iterator::goToLigne(double l) { //coordonnées "réelles", erreur si ligne n'existe pas dans colonne actuelle
    firstLigne();
    while (!atEndLigne() && getCurrentLigne() < l)
        nextLigne();
    
    if (atEndLigne() || getCurrentLigne()!=l) throw runtime_error("ERROR Graphe::Iterator::goToLigne : Ligne non occupee dans cette colonne.");
}


/*! \brief Pour déplacer l'itérateur sur une case précise (erreur si case n'existe pas).
    Utiliser Graphe::hasCase pour savoir si la case existe, ou déplacer l'itérateur "manuellement".
*/
void Graphe::Iterator::goToCoords(double c, double l) { //coordonnées "réelles", erreur si n'existent pas
    goToColonne(c);
    goToLigne(l);
}

/*! \brief Pour déplacer l'itérateur sur une case précise (erreur si case n'existe pas).
    Utiliser Graphe::hasCase pour savoir si la case existe, ou déplacer l'itérateur "manuellement".
*/
void Graphe::Iterator::goToCoords(const Coords& c) {
    goToCoords(c.getX(), c.getY());
}
