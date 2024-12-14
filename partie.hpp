#ifndef PARTIE_HPP
#define PARTIE_HPP

#include <iostream>
#include "plateau.h"
#include "Joueur.h"



using namespace std;
//Forward Definitions



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
        Partie() : nb_retour_arriere(0), etat_actuel(), etat_precedent(), start_joueur_id(0) {}
        void setStartJoueurId();//méthode qui détermine qui commence la partie
        void commencerPartie(string pseudo1, string pseudo2, bool IA1=false, bool IA2=false);
        void lancerProchainTour();
        void sauvegarderEtat();
        void terminerPartie();
        void restaurerEtat(const EtatDuJeu &etat);
};



class MementoPartie{
    private :
        int numero_tour;
        Plateau plateau;
        Joueur joueurs[2];
        Joueur* joueur_courant;
    
    public:
        friend class Partie;//evite de faire des getters, a voir si c'est judicieux
        MementoPartie(int num_tour, const Plateau& p, const Joueur& joueur1, const Joueur& joueur2, const Joueur& joueur_courant);
        MementoPartie();
        MementoPartie& operator=(const MementoPartie& memento);
};

#endif
