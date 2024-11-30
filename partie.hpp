#ifndef PARTIE_HPP
#define PARTIE_HPP

#include <iostream>
#include "plateau.h"
#include "joueur.h"

using namespace std;

class Partie{
    private :
        //attributs :
        int nb_retour_arriere; //nombre de retours en arriere possibles
        EtatDuJeu etat_precedent;
        EtatDuJeu etat_actuel;
        int start_joueur_id; //position du joueur qui commence le tour dans le tableau de 2 joueurs
        //constructeurs de recopie et d'affectation prives :
        Partie& operator=(const Partie& partie);
        Partie(const Partie& partie);
    public:
        Partie();
        ~Partie();
        void setStartJoueurId();//méthode qui détermine qui commence la partie
        void commencerPartie(string pseudo1, string pseudo2);
        void lancerProchainTour();
        void sauvegarderEtat();
        void terminerPartie();
        void restaurerEtat(const MementoPartie &etat);
};

class GameManager{
    Partie partie_active;
    EtatDuJeu** sauvegardes;
    static GameManager* instance;
};

#endif
