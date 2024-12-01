#include "cases.h"

// AFFICHAGE
std::ostream& operator<<(std::ostream& flux, const Case& c) {
    /* Affichage d'une case, peut être ajouté au cout<< */

    flux<<c.showCase();
    return flux;
}

std::ostream& operator<<(std::ostream& flux, const Graphe& g) {
    /* Affichage du graphe, peut être ajouté au cout<< */

    flux<<std::endl;

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

// METHODES CASE
/*! \brief Pour affichage d'une case, mais renvoie uniquement le string à utiliser.
*/
std::string Case::showCase() const {
    string str;
    if (empty()) str="xx";
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

/*! \brief Permet de savoir si une pièce est contenue dans la case impliquée, pour supprimer la pièce ou récupérer ses coordonnées.
*/
bool Case::hasPiece(const Piece& p) const { //renvoie True si pièce est sur la case, False sinon
    bool has_piece = false;
    auto ite = begin();

    // parcourt toutes les pièces dans la case, s'arrête quand la pièce a été trouvée ou que l'on a atteint la fin
    while (!ite.atEnd() && !has_piece) {
        has_piece = ite.getCurrent() == &p;
        ite++;
    }
    
    return has_piece;
}

/*! \brief [PRIVÉ] Pour ajouter une pièce sur une case, tout en haut de la pile (erreur si pièce déjà sur la case).
    Utiliser Case::hasPiece pour savoir si pièce sur la case.
*/
void Case::addPiece(const Piece& p) { //erreur si pièce est déjà sur la case
    if (hasPiece(p)) throw exception("ERROR Case::addPiece : Pièce déjà sur cette case.");
    pieces.push_back(&p);
}

/*! \brief [PRIVÉ] Pour supprimer la pièce en haut de la pile de pièces de la case (erreur si case vide).
    Utiliser Case::empty pour savoir si case vide.
*/
void Case::supprPiece() { //supprime la pièce la plus haut placée
    // erreur si aucune pièce à supprimer sur la case
    if (empty()) throw exception("ERROR Case::supprPiece : Case non occupée.");
    pieces.pop_back();
}

/*! \brief [PRIVÉ] Pour supprimer toutes les pièces présentes sur la case (erreur si case vide).
    Utiliser Case::empty pour savoir si case vide.
*/
void Case::clear() { //supprime toutes les pièces
    // erreur si aucune pièce à supprimer sur la case
    if (empty()) throw exception("ERROR Case::clear : Case déjà vide.");

    for (unsigned int i=getNbPieces() ; i>0 ; i--) supprPiece();
}

/*! \brief Pour récupérer la pièce située tout en haut de la pile de pièces (erreur si case vide).
    Utiliser Case::empty pour savoir si case vide.
*/
const Piece& Case::getUpperPiece() const { //erreur si pas de pièce sur la case
    if (empty()) throw exception("ERROR Case::getUpperPiece : Case vide, aucune pièce à récupérer");
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

/*! \brief [PRIVÉ] Pour récupérer une case modifiable en fonction de ses coordonnées.
*/
Case* Graphe::getMutableCase(const Coords& c) const {
    return getMutableCase(c.getX(), c.getY());
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
    if (pt==nullptr) throw exception("ERROR Graphe::getCase : Case n'existe pas.");
    return *pt;
}

/*! \brief Pour récupérer une case non modifiable en fonction de ses coordonnées (erreur si case n'existe pas).
    Utiliser Graphe::hasCase pour savoir si case existe.
*/
const Case& Graphe::getCase(const Coords& c) const {
    Case* pt = getMutableCase(c);
    if (pt==nullptr) throw exception("ERROR Graphe::getCase : Case n'existe pas.");
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
const Coords Graphe::coordsAdjacent(const Coords& c, unsigned int side) const { //renvoie coordonnées de case adjacente (même si adjacente inexistante)
    if (side == 0) return coordsNorth(c);
    if (side == 1) return coordsNorthEast(c);
    if (side == 2) return coordsSouthEast(c);
    if (side == 3) return coordsSouth(c);
    if (side == 4) return coordsSouthWest(c);
    if (side == 5) return coordsNorthWest(c);
    throw exception("ERROR Graphe::coordsAdjacent : Côté invalide.");
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
    
    if (coords==nullptr) throw exception("ERROR Graphe::coordsPiece : Piece pas dans graphe.");
    
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

// modification graphe
/*! \brief [PRIVÉ] Pour mettre à jour attributs de Graphe après ajout d'une nouvelle case (nombre de cases et extrémités gauche/droite/haute/basse).
*/
void Graphe::updateAttributes(const Coords& c) {
    
    // modification des attributs du graphe en cas d'ajout de case
    if (getMutableCase(c) != nullptr) {
        nb_cases++;

        // si nouvelle colonne à gauche ou à droite, mettre à jour min/max de X
        if (nb_cases == 1) max_x, min_x = c.getX();
        else if (max_x < c.getX()) max_x = c.getX();
        else if (min_x > c.getX()) min_x = c.getX();

        // si nouvelle ligne en haut ou en bas, mettre à jour min/max de Y
        if (nb_cases == 1) max_y, min_y = c.getY();
        if (max_y < c.getY()) max_y = c.getY();
        else if (min_y > c.getY()) min_y = c.getY();

    }

    // modification des attributs du graphe en cas de suppression de case
    else {
        nb_cases--;
        auto ite = getIterator();

        // si le graphe est vide, alors tout est set à 0
        if (ite.atEndColonne()) {
            max_x, min_x, max_y, min_y = 0;
            return;
        }

        // si la colonne est vide, il y a une erreur dans le vecteur cases
        if (ite.atEndLigne()) throw exception("ERROR Graphe::updateAttributes : Colonne vide.");
        if (ite.getCurrentColonne() > min_x) min_x = ite.getCurrentColonne();
        double min_ligne = max_y, max_ligne = min_y;

        while (!ite.atEndColonne()) {
            if (ite.getCurrentLigne() < min_ligne) min_ligne = ite.getCurrentLigne();
            
            ite.endLigne();
            ite.prevLigne();

            if (ite.getCurrentLigne() > max_ligne) max_ligne = ite.getCurrentLigne();

            ite.firstLigne();
            ite.nextColonne();
            if (!ite.atEndColonne() && ite.atEndLigne()) throw exception("ERROR Graphe::updateAttributes : Colonne vide.");
        }
        ite.prevColonne();
        if (ite.getCurrentColonne() < max_x) max_x = ite.getCurrentColonne();
        min_y = min_ligne;
        max_y = max_ligne;
    }
}

/*! \brief [PRIVÉ] Pour ajouter une case à des coordonnées précises (erreur si case existe déjà).
    Utiliser Graphe::hasCase pour savoir si case existe.
*/
void Graphe::addCase(const Coords& c) { //erreur si case existe déjà

    auto ite = findCasePlace(c);

    // si colonne inédite et à la fin du tableau, ajout d'une nouvelle colonne à la fin et création de la nouvelle case
    if (ite.atEndColonne()) {
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

    // si colonne pré-existante et case inédite à la fin du tableau, création de la nouvelle case à la fin du tableau
    if (ite.atEndLigne()) {
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

/*! \brief [PRIVÉ] Pour supprimer une case à des coordonnées précises (erreur si case n'existe pas).
*/
void Graphe::supprCase(const Coords& c) {
    auto ite = findCasePlace(c);

    if (ite.atEndColonne() || ite.atEndLigne() || ite.getCurrent().getCoords()!=c) throw exception("ERROR Graphe::supprCase : Case n'existe pas.");

    const Case* ca = &ite.getCurrent();

    ite.goToColonne(c.getX());
    std::erase(cases.at(ite.getVectorColonne()), ca);
    std::erase_if(cases, [](std::vector<Case*> v) { return v.size() == 0; });

    delete ca;

    updateAttributes(c);
}

/*! \brief Pour ajouter une pièce à des coordonnées précises (erreur si pièce déjà dans le graphe).
    Utiliser Graphe::hasPiece pour savoir si pièce dans graphe.
*/
void Graphe::addPiece(const Piece& p, const Coords& c) { //erreur si case inexistante ou contient déjà la pièce
    Case* ca = getMutableCase(c);
    
    if (ca==nullptr) throw exception("ERROR Graphe::addPiece : Case non existante.");
    if (ca->hasPiece(p)) throw exception("ERROR Graphe::addPiece : Case contient déjà la pièce.");

    ca->addPiece(p);

    // ajout de cases adjacentes vides s'il n'y en a pas
    Coords coords_adjac(0, 0);
    for (unsigned int i=0; i<6; i++) {
        coords_adjac = coordsAdjacent(c, i);
        if (!hasCase(coords_adjac))
            addCase(coords_adjac);
    }
}

/*! \brief [PRIVÉ] Pour supprimer une pièce du graphe, prend la pièce sur le dessus aux coordonnées indiquées (erreur si case inexistante ou vide).
    Bien vérifier coordonnées de la pièce avant d'exécuter.
*/
void Graphe::supprPiece(Case& c) {
    c.supprPiece();

        //suppression des cases pas en contact avec la ruche
    if (c.empty()) {

        const Case* ca = nullptr;
        unsigned int i = 0;
        auto ite = getIterator();

        while (i <= 5) {
            const Coords adjacent = coordsAdjacent(c.getCoords(), i);

            if (hasCase(adjacent) && isIsland(adjacent)) {
                supprCase(adjacent);
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
    supprPiece(*getMutableCase(c));
}

/*! Pour déplacer une pièce du graphe aux coordonnées indiquées (erreur si case inexistante ou pièce coincée).
*/
void Graphe::movePiece(const Piece& p, const Coords& c) {
    const Coords& coords = coordsPiece(p);
    if (getExistentCase(coords).isPieceStuck(p)) throw exception("ERROR Graphe::movePiece : Pièce coincée, mouvement impossible.");
    
    Case* ca = getMutableCase(c);
    if (ca==nullptr) throw exception("ERROR Graphe::movePiece : Case de destination inexistante.");

    addPiece(p, c);
    supprPiece(coords);
}

// iterator

/*! \brief Pour déplacer l'itérateur sur une colonne précise (erreur si colonne n'existe pas).
    Déplacer l'itérateur "manuellement" pour savoir si colonne existe.
*/
void Graphe::Iterator::goToColonne(double c) { //coordonnées "réelles", erreur si colonne n'existe pas
    firstColonne();

    while (!this->atEndColonne() && getCurrent().getColonne()<c) nextColonne();
    if (this->atEndColonne() || getCurrent().getColonne()>c) throw exception("ERROR Graphe::Iterator::goToColonne : Colonne non occupée.");
}

/*! \brief Pour déplacer l'itérateur sur une ligne précise, en étant déjà sur la bonne colonne (erreur si ligne n'existe pas).
    Utiliser Graphe::hasCase pour savoir si la case existe, ou déplacer l'itérateur "manuellement".
*/
void Graphe::Iterator::goToLigne(double l) { //coordonnées "réelles", erreur si ligne n'existe pas dans colonne actuelle
    firstLigne();
    while (!atEndLigne() && getCurrentLigne() < l)
        nextLigne();
    
    if (atEndLigne() || getCurrentLigne()!=l) throw exception("ERROR Graphe::Iterator::goToLigne : Ligne non occupée dans cette colonne.");
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