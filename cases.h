#ifndef CASES_H
#define CASES_H
#include "coords.h"
#include "pieces.h"
#include <vector>

// CASES
class Case {
    friend class Graphe;

    class Iterator {
        friend class Case;

        const std::vector<const Piece*>& vect;
        unsigned int current;

        Iterator(const std::vector<const Piece*>& v, unsigned int n=0) : vect(v), current(n) {}
        ~Iterator()=default;

        public:
            Iterator(const Iterator& ite)=default;
            Iterator operator=(const Iterator& ite) { current=ite.current; }

            const Piece* getCurrent() const { return vect.at(current); }
            unsigned int getNiveau() const { return current; }
            void next() { (*this)++; }
            void prev() { (*this)--; }

            Iterator operator++(int) { current++; return *this; }
            Iterator operator--(int) { current--; return *this; }
            bool operator==(const Iterator& ite) const { return ite.getNiveau()==getNiveau(); }
            bool operator!=(const Iterator& ite) const { return ite.getNiveau()!=getNiveau(); }
    };

    private:
        Coords coords;
        std::vector<const Piece*> pieces;

    protected:
        // constructeur/destructeur
        Case(const Coords& c) : coords(c) {}
        Case(double ligne, double colonne) : coords(Coords(colonne, ligne)) {};
        virtual ~Case()=default;
        Case(const Case& c)=delete;
        Case operator=(const Case& c)=delete;

        virtual void setCoords(double ligne, double colonne) { coords.changeXY(colonne, ligne); }
        virtual void setCoords(const Coords& c) { coords=c; }
        void addPiece(const Piece* p);
        void supprPiece();
        void clear();

    public:
        virtual const Coords& getCoords() const { return coords; }
        double getLigne() const { return coords.getY(); }
        double getColonne() const { return coords.getX(); }
        unsigned int getNbPieces() const { return pieces.size(); }
        bool empty() const { return (getNbPieces()==0); }
        bool hasPiece(const Piece* p) const;

        Iterator begin() const { return Iterator(pieces); }
        Iterator end() const { return Iterator(pieces, pieces.size()); }
};

// GRAPHE
class Graphe {
    class Iterator {
            friend class Graphe;

            private:
                const std::vector<std::vector<Case*>>& vect;
                unsigned int colonne;
                unsigned int ligne;

                Iterator(const std::vector<std::vector<Case*>> &v) : vect(v), ligne(0), colonne(0) {}

                unsigned int getVectorLigne() const { return ligne; }
                unsigned int getVectorColonne() const { return colonne; }
                Case* getMutableCurrent() { return vect.at(colonne).at(ligne); }

                void goToVectorLigne(unsigned int l) { ligne=l; }
                void goToVectorColonne(unsigned int c) { colonne=c; }

            public:
                Iterator(const Iterator& ite)=default;
                Iterator operator=(const Iterator& ite) { colonne=ite.colonne ; ligne=ite.ligne; }
                ~Iterator()=default;

                const Case& getCurrent() const { return *vect.at(colonne).at(ligne); }
                double getCurrentColonne() const { return vect.at(colonne).at(0)->getColonne(); }
                double getCurrentLigne() const { return vect.at(colonne).at(ligne)->getLigne(); }
                
                void firstColonne() { colonne=0; }
                void endColonne() { colonne = vect.size(); }
                void nextColonne() { colonne++; }
                void prevColonne() { colonne--; }
                void goToColonne(double c);

                void firstLigne() { ligne=0; }
                void endLigne() { ligne = vect.at(colonne).size(); }
                void nextLigne() { ligne++; }
                void prevLigne() { ligne--; }
                void goToLigne(double l);

                void goToCoords(double c, double l);
                void goToCoords(const Coords& c);

                bool operator==(const Iterator& ite) const { return ( colonne==ite.colonne && ligne==ite.ligne ); }
                bool operator!=(const Iterator& ite) const { return ( colonne!=ite.colonne || ligne!=ite.ligne ); }
        };

    private:
        unsigned int nb_cases;
        double max_x, min_x, max_y, min_y;
        std::vector<std::vector<Case*>> cases;

        Graphe(const Graphe& g)=delete;
        Graphe operator=(const Graphe& g)=delete;

        Case* getMutableCase(double c, double l) const;
        Case* getMutableCase(const Coords& c) const;

        void addCase(const Coords& c);

    public:
        Graphe() : nb_cases(0), max_x(0), min_x(0), max_y(0), min_y(0) {}
        virtual ~Graphe();

        unsigned int getNbCases() const { return nb_cases; }
        virtual bool estVide() const { return (getNbCases()==0); }

        Iterator getIterator() const { Iterator ite = Iterator(cases); return ite; }

        const Case& getCase(double c, double l) const;
        const Case& getCase(const Coords& c) const;
        
        const Coords coordsAdjacent(const Coords& c, unsigned int side) const;

        const Coords coordsNorth(const Coords& c) const { return Coords(c.getX(), c.getY()-2); }
        const Coords coordsNorthEast(const Coords& c) const { return Coords(c.getX()+1, c.getY()-1); }
        const Coords coordsSouthEast(const Coords& c) const { return Coords(c.getX()+1, c.getY()+1); }
        const Coords coordsSouth(const Coords& c) const { return Coords(c.getX(), c.getY()+2); }
        const Coords coordsSouthWest(const Coords& c) const { return Coords(c.getX()-1, c.getY()+1); }
        const Coords coordsNorthWest(const Coords& c) const { return Coords(c.getX()-1, c.getY()-1); }

        Iterator findCasePlace(double c, double l) const;
        Iterator findCasePlace(const Coords& c) const { return findCasePlace(c.getX(), c.getY()); }
        void addPiece(const Piece& p, const Coords& c);
};

#endif