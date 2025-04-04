#ifndef CASES_H
#define CASES_H
#include "coords.h"
#include "pieces.h"
#include <vector>
#include <iostream>
#include <string>

// CASES
class Case {
    friend class Graphe;

    // Iterateur
    class Iterator {
        friend class Case;

        // attributs
        const std::vector<const Piece*>* vect;
        unsigned int current;

        // constructeur/destructeur privés (recopie possible)
        Iterator(const std::vector<const Piece*>& v, unsigned int n=0) : vect(&v), current(n) {}

        public:
            // recopie
            Iterator(const Iterator& ite)=default;
            Iterator operator=(const Iterator& ite) { current=ite.current; return ite; }
            ~Iterator()=default;

            // renvoyer pièce actuelle
            const Piece* getCurrent() const { return vect->at(current); }
            // renvoyer niveau dans la pile (0 tout en bas)
            unsigned int getNiveau() const { return current; }

            // remonter/descendre dans la pile
            void next() { (*this)++; }
            void prev() { (*this)--; }
            bool atEnd() const { return current==vect->size(); }

            // opérateurs
            Iterator operator++(int) { current++; return *this; }
            Iterator operator--(int) { current--; return *this; }
            bool operator==(const Iterator& ite) const { return ite.getNiveau()==getNiveau(); }
            bool operator!=(const Iterator& ite) const { return ite.getNiveau()!=getNiveau(); }
            const Piece& operator*() const { return *getCurrent(); }
    };

    private:
        // longueur de nom de case lors de l'affichage console
        static const size_t name_length = 2;

        // attributs (coordonnées de la case et liste de pièces)
        Coords coords;
        std::vector<const Piece*> pieces;

    protected:
        // constructeur/destructeur (recopie interdite)
        Case(const Coords& c) : coords(c) {}
        Case(double ligne, double colonne) : coords(Coords(colonne, ligne)) {};
        virtual ~Case()=default;
        Case(const Case& c)=default;
        Case& operator=(const Case& c) { coords=c.coords; pieces=c.pieces; return *this; }

        // modifier emplacement case (pour recentrage du graphe)
        virtual void setCoords(double ligne, double colonne) { coords= Coords(colonne, ligne); }
        virtual void setCoords(const Coords& c) { coords=c; }

        // ajouter pièce sur le dessus, supprimer pièce du dessus ou tout supprimer
        void addPiece(const Piece& p);
        void supprPiece();
        void clear();

        void changePiece(const Piece* new_piece, const Piece* old_piece);

    public:
        // longueur du nom de case lors de l'affichage console
        static size_t getNameLength() { return name_length; }
        // affichage en string de la case
        std::string strCase() const;

        // getters
        virtual const Coords& getCoords() const { return coords; }
        double getLigne() const { return coords.getY(); }
        double getColonne() const { return coords.getX(); }
        unsigned int getNbPieces() const { return pieces.size(); }

        // vrai si aucune pièce sur la case
        bool empty() const { return (getNbPieces()==0); }
        // vrai si pièce est placée sur la case
        bool hasPiece(const Piece* p) const;
        bool hasPiece(const Piece& p) const { return hasPiece(&p); }
        // renvoie la pièce sur le dessus de la pile
        const Piece& getUpperPiece() const;
        // renvoie si la pièce est bloquée
        bool isPieceStuck(const Piece& p) const;

        // itérateur
        Iterator begin() const { return Iterator(pieces); }
        Iterator end() const { return Iterator(pieces, pieces.size()); }

        void operator<<(const Piece& p) { return addPiece(p); }
        void operator--(int) { return supprPiece(); }
};

// GRAPHE
class Graphe {
    // Iterateur
    class Iterator {
            friend class Graphe;

            private:
                // attributs
                const std::vector<std::vector<Case*>>& vect;
                unsigned int colonne;
                unsigned int ligne;

                // constructeur privé
                Iterator(const std::vector<std::vector<Case*>> &v) : vect(v), ligne(0), colonne(0) {}

                // renvoie emplacement de l'itérateur dans le tableau
                unsigned int getVectorColonne() const { return colonne; }
                unsigned int getVectorLigne() const { return ligne; }

                // renvoie case actuelle modifiable
                Case* getMutableCurrent() const { return vect.at(colonne).at(ligne); }

                // déplacement vers endroit du tableau (aucune vérification si valeurs aberrantes)
                void goToVectorColonne(unsigned int c) { colonne=c; }
                void goToVectorLigne(unsigned int l) { ligne=l; }

            public:
                // recopie et destructeur
                Iterator(const Iterator& ite)=default;
                Iterator operator=(const Iterator& ite) { colonne=ite.colonne; ligne=ite.ligne; return ite; }
                ~Iterator()=default;

                // renvoie case actuelle non modifiable
                const Case& getCurrent() const { return *vect.at(colonne).at(ligne); }
                // renvoie emplacement de l'itérateur dans la ruche (coordonnées "réelles" des cases)
                double getCurrentColonne() const { return vect.at(colonne).at(0)->getColonne(); }
                double getCurrentLigne() const { return vect.at(colonne).at(ligne)->getLigne(); }

                // renvoie si itérateurs au même endroit
                bool onSameColonne(const Iterator& ite) const { return colonne==ite.colonne; }
                bool onSameLigne(const Iterator& ite) const { return ligne==ite.ligne; }
                
                // début/fin, avant/arrière, et vers colonne précise (selon coordonnées "réelles" dans la ruche)
                void firstColonne() { colonne=0; }
                void endColonne() { colonne = vect.size(); }
                void nextColonne() { colonne++; }
                void prevColonne() { colonne--; }
                void goToColonne(double c);
                bool atEndColonne() const {return colonne == vect.size(); }

                // début/fin, avant/arrière, et vers ligne précise (besoin d'être déjà sur la colonne désirée)
                void firstLigne() { ligne=0; }
                void endLigne() { ligne = vect.at(colonne).size(); }
                void nextLigne() { ligne++; }
                void prevLigne() { ligne--; }
                void goToLigne(double l);
                bool atEndLigne() const {return ligne == vect.at(colonne).size(); }

                // déplacement vers case précise dans la ruche (erreur si n'existe pas)
                void goToCoords(double c, double l);
                void goToCoords(const Coords& c);

                // opérateurs
                bool operator==(const Iterator& ite) const { return ( colonne==ite.colonne && ligne==ite.ligne ); }
                bool operator!=(const Iterator& ite) const { return ( colonne!=ite.colonne || ligne!=ite.ligne ); }
        };

    private:
        // attributs (min/max sont coordonnées "réelles" dans la ruche)
        unsigned int nb_cases;
        unsigned int nb_inhabited_cases;
        double max_x, min_x, max_y, min_y;
        std::vector<std::vector<Case*>> cases;


        // met les attributs min, max et nb_cases à jour après la création d'une nouvelle case
        void updateAttributesAdd(double c, double l);
        void updateAttributesAdd(const Coords& c) { updateAttributesAdd(c.getX(), c.getY()); }
        void updateAttributesSuppr(double c, double l);
        void updateAttributesSuppr(const Coords& c) { updateAttributesSuppr(c.getX(), c.getY()); }
        void updateAttributes(const Coords& c, size_t modif=2);

        // renvoie une case modifiable
        Case* getMutableCase(double c, double l) const;
        Case* getMutableCase(const Coords& c) const {return getMutableCase(c.getX(), c.getY());}
        Case& getExistentCase(const Coords& c) const;

        // ajoute case dans la ruche
        Case* addCase(const Coords& c);
        Case* addCase(double c, double l) { return addCase(Coords(c, l)); }
        void supprCase(const Case& c);
        void supprCase(const Coords& c);
        void addPiece(const Piece& p, Case& c);
        void supprPiece(Case& c);
        void clear();

        // renvoie si une pièce est entourée de cases vides
        bool isIsland(double c, double l) const { return isIsland(Coords(c, l)); }
        bool isIsland(const Coords& c) const;
        bool isIsland(const Case& c) const { return isIsland(c.getCoords()); }
        bool isDeletable(const Case& c) const { return (c.empty() && isIsland(c.getCoords())); }

        const Coords* coordsPiecePointer(const Piece* p) const;
        const Coords* coordsPiecePointer(const Piece& p) const { return coordsPiecePointer(&p); }

    public:
        // constructeur/destructeur
        Graphe() : nb_cases(0), nb_inhabited_cases(0), max_x(0), min_x(0), max_y(0), min_y(0) { addCase(0, 0); }
        virtual ~Graphe();
        Graphe(const Graphe& g);
        Graphe& operator=(const Graphe& g);

        // getters
        double getMaxX() const { return max_x; }
        double getMinX() const { return min_x; }
        double getMaxY() const { return max_y; }
        double getMinY() const { return min_y; }
        unsigned int getNbCases() const { return nb_cases; }
        unsigned int getNbInhabitedCases() const { return nb_inhabited_cases; }
        virtual bool empty() const { return (getNbCases()==0); }

        // renvoie si graphe contient case
        bool hasCase(double c, double l) const { return (getMutableCase(c, l)!=nullptr); }
        bool hasCase(const Coords& c) const { return hasCase(c.getX(), c.getY()); }

        // renvoie si graphe contient pièce, et coordonnées pièce
        bool hasPiece(const Piece* p) const { return coordsPiecePointer(p)!=nullptr; };
        bool hasPiece(const Piece& p) const { return hasPiece(&p); };
        const Coords& coordsPiece(const Piece* p) const;
        const Coords& coordsPiece(const Piece& p) const { return coordsPiece(&p); }
        bool isPieceStuck(const Piece& p) const;
        // renvoie si une pièce est entourée d'autres pièces (pour la reine)
        bool isSurrounded(const Coords& c) const;
        bool isSurrounded(const Case& c) const { return isSurrounded(c.getCoords()); }
        bool wouldHiveBreak(const Coords& c) const;
        bool canSlide(const Coords& c, unsigned int side) const;
        bool canPlace(const Coords& c, bool camp) const;

        // renvoie case non modifiable
        const Case& getCase(double c, double l) const;
        const Case& getCase(const Coords& c) const { return getCase(c.getX(), c.getY()); } ;
        
        Coords coordsNorth(const Coords& c) const { return Coords(c.getX(), c.getY()-2); }
        Coords coordsNorthEast(const Coords& c) const { return Coords(c.getX()+1, c.getY()-1); }
        Coords coordsSouthEast(const Coords& c) const { return Coords(c.getX()+1, c.getY()+1); }
        Coords coordsSouth(const Coords& c) const { return Coords(c.getX(), c.getY()+2); }
        Coords coordsSouthWest(const Coords& c) const { return Coords(c.getX()-1, c.getY()+1); }
        Coords coordsNorthWest(const Coords& c) const { return Coords(c.getX()-1, c.getY()-1); }

        Coords coordsAdjacent(const Coords& c, unsigned int side) const;
        std::vector<Coords> coordsAllAdjacents(const Coords& c) const;
        std::vector<Coords> coordsExistentAdjacents(const Coords& c) const;
        std::vector<Coords> coordsInhabitedAdjacents(const Coords& c) const;

        // déplacements pièce dans la ruche
        void addPiece(const Piece& p, const Coords& c);
        void supprPiece(const Coords& c);
        void movePiece(const Piece& p, const Coords& c);

        // itérateur
        Iterator getIterator() const { Iterator ite = Iterator(cases); return ite; }
        Iterator findCasePlace(double c, double l) const;
        Iterator findCasePlace(const Coords& c) const { return findCasePlace(c.getX(), c.getY()); }

        void changePiece(const Coords& c, const Piece* new_piece, const Piece* old_piece);
        void changePiece(const Piece* new_piece, const Piece* old_piece);

        std::vector<Coords>placableCoords(bool camp) const;

        std::string toStr() const;
        std::string toStr(const Coords& selected) const;
        std::string toStr(const Coords& selected1, const Coords& selected2) const;
};

// AFFICHAGE
// renvoie la frontière nord ou sud d'une case
std::string caseBorder();
// renvoie un espace vide de la taille d'une case
std::string caseVoid();
// renvoie un espace vide de la taille d'une frontière
std::string caseBorderVoid();
//renvoie si deux cases sont sur la même ligne
bool onStraightLine(const Coords& c1, const Coords& c2);

// renvoie si les coordonnées sont correctes pour une case
bool isCaseCoords(int c, int l);
bool isCaseCoords(const Coords& c);

std::ostream& operator<<(std::ostream& flux, const Case& c);
std::ostream& operator<<(std::ostream& flux, const Graphe& g);

// couleurs ANSI
std::string setColor(bool camp, bool highlight=false);
std::string setColor(bool camp, TYPE_PIECE piece);
std::string resetColor();
std::string redColor();
std::string blueColor();
std::string queenRedColor();
std::string queenBlueColor();

#endif