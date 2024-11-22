#ifndef CASES_H
#define CASES_H
#include "coords.h"
#include "pieces.h"
#include <vector>

// CASES
class Case {
    friend class Graphe;

    // Iterateur
    class Iterator {
        friend class Case;

        // attributs
        const std::vector<const Piece*>& vect;
        unsigned int current;

        // constructeur/destructeur privés (recopie possible)
        Iterator(const std::vector<const Piece*>& v, unsigned int n=0) : vect(v), current(n) {}
        ~Iterator()=default;

        public:
            // recopie
            Iterator(const Iterator& ite)=default;
            Iterator operator=(const Iterator& ite) { current=ite.current; }

            // renvoyer pièce actuelle
            const Piece* getCurrent() const { return vect.at(current); }
            // renvoyer niveau dans la pile (0 tout en bas)
            unsigned int getNiveau() const { return current; }

            // remonter/descendre dans la pile
            void next() { (*this)++; }
            void prev() { (*this)--; }

            // opérateurs
            Iterator operator++(int) { current++; return *this; }
            Iterator operator--(int) { current--; return *this; }
            bool operator==(const Iterator& ite) const { return ite.getNiveau()==getNiveau(); }
            bool operator!=(const Iterator& ite) const { return ite.getNiveau()!=getNiveau(); }
    };

    private:
        // attributs (coordonnées de la case et liste de pièces)
        Coords coords;
        std::vector<const Piece*> pieces;

    protected:
        // constructeur/destructeur (recopie interdite)
        Case(const Coords& c) : coords(c) {}
        Case(double ligne, double colonne) : coords(Coords(colonne, ligne)) {};
        virtual ~Case()=default;
        Case(const Case& c)=delete;
        Case operator=(const Case& c)=delete;

        // modifier emplacement case (pour recentrage du graphe)
        virtual void setCoords(double ligne, double colonne) { coords.changeXY(colonne, ligne); }
        virtual void setCoords(const Coords& c) { coords=c; }

        // ajouter pièce sur le dessus, supprimer pièce du dessus ou tout supprimer
        void addPiece(const Piece* p);
        void supprPiece();
        void clear();

    public:
        // getters
        virtual const Coords& getCoords() const { return coords; }
        double getLigne() const { return coords.getY(); }
        double getColonne() const { return coords.getX(); }
        unsigned int getNbPieces() const { return pieces.size(); }

        // vrai si aucune pièce sur la case
        bool empty() const { return (getNbPieces()==0); }
        // vrai si pièce est placée sur la case
        bool hasPiece(const Piece* p) const;

        // itérateur
        Iterator begin() const { return Iterator(pieces); }
        Iterator end() const { return Iterator(pieces, pieces.size()); }
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
                Iterator operator=(const Iterator& ite) { colonne=ite.colonne ; ligne=ite.ligne; }
                ~Iterator()=default;

                // renvoie case actuelle non modifiable
                const Case& getCurrent() const { return *vect.at(colonne).at(ligne); }
                // renvoie emplacement de l'itérateur dans la ruche (coordonnées "réelles" des cases)
                double getCurrentColonne() const { return vect.at(colonne).at(0)->getColonne(); }
                double getCurrentLigne() const { return vect.at(colonne).at(ligne)->getLigne(); }
                
                // début/fin, avant/arrière, et vers colonne précise (selon coordonnées "réelles" dans la ruche)
                void firstColonne() { colonne=0; }
                void endColonne() { colonne = vect.size(); }
                void nextColonne() { colonne++; }
                void prevColonne() { colonne--; }
                void goToColonne(double c);

                // début/fin, avant/arrière, et vers ligne précise (besoin d'être déjà sur la colonne désirée)
                void firstLigne() { ligne=0; }
                void endLigne() { ligne = vect.at(colonne).size(); }
                void nextLigne() { ligne++; }
                void prevLigne() { ligne--; }
                void goToLigne(double l);

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
        double max_x, min_x, max_y, min_y;
        std::vector<std::vector<Case*>> cases;

        // recopie interdite
        Graphe(const Graphe& g)=delete;
        Graphe operator=(const Graphe& g)=delete;

        // renvoie une case modifiable
        Case* getMutableCase(double c, double l) const;
        Case* getMutableCase(const Coords& c) const;

        // ajoute case dans la ruche
        void addCase(const Coords& c);

    public:
        // constructeur/destructeur
        Graphe() : nb_cases(0), max_x(0), min_x(0), max_y(0), min_y(0) {}
        virtual ~Graphe();

        // getters
        unsigned int getNbCases() const { return nb_cases; }
        virtual bool estVide() const { return (getNbCases()==0); }

        // itérateur
        Iterator getIterator() const { Iterator ite = Iterator(cases); return ite; }

        // renvoie case non modifiable
        const Case& getCase(double c, double l) const;
        const Case& getCase(const Coords& c) const;
        
        // renvoie coordonnées de la case adjacente (side 0-6, à partir de nord dans sens horaire)
        const Coords coordsAdjacent(const Coords& c, unsigned int side) const;
        // renvoie coordonnées de la case adjacente
        const Coords coordsNorth(const Coords& c) const { return Coords(c.getX(), c.getY()-2); }
        const Coords coordsNorthEast(const Coords& c) const { return Coords(c.getX()+1, c.getY()-1); }
        const Coords coordsSouthEast(const Coords& c) const { return Coords(c.getX()+1, c.getY()+1); }
        const Coords coordsSouth(const Coords& c) const { return Coords(c.getX(), c.getY()+2); }
        const Coords coordsSouthWest(const Coords& c) const { return Coords(c.getX()-1, c.getY()+1); }
        const Coords coordsNorthWest(const Coords& c) const { return Coords(c.getX()-1, c.getY()-1); }

        // renvoie endroit où devrait se situer une case (coordonnées différentes si case pas dans graphe)
        Iterator findCasePlace(double c, double l) const;
        Iterator findCasePlace(const Coords& c) const { return findCasePlace(c.getX(), c.getY()); }

        // ajoute pièce dans une case de la ruche
        void addPiece(const Piece& p, const Coords& c);
};

#endif