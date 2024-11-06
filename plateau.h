#ifndef PLATEAU_H
#define PLATEAU_H
#include "cases.h"

// PLATEAU
class Plateau {
    Graphe graphe;

    public :
        Plateau()=default;
        ~Plateau()=default;
        Graphe& getGraphe() { return graphe; }
};

#endif