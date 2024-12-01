#ifndef PARTIE_HPP
#define PARTIE_HPP

#include <iostream>
#include "plateau.h"
<<<<<<< HEAD
#include "joueur.h"
=======
#include "Joueur.h"
>>>>>>> feature/main

using namespace std;

class EtatDuJeu {
    private:
        Plateau plateau;               // plateau avec les pièces
        vector<Mouvement> historique;  // liste des coups
        Joueur** joueurs[2];              // liste des joueurs
        int numero_tour;
        Joueur* joueur_courant;

    public:
        EtatDuJeu(int num_tour, const Plateau& p,  const Joueur& j1, const Joueur& j2, const Joueur& jc);
        EtatDuJeu();
        EtatDuJeu& operator=(const EtatDuJeu& jeu);
        vector<Mouvement> coupPossibles(Joueur& j);  // coups possibles
        bool FinDuJeu() const;  // vérifie si le jeu est fini
        void ajouterMouvement(const Mouvement& mvt) { historique.push_back(mvt); } // ajoute un coup à l'historique
        void annulerDernierMouvement(); // annule le dernier coup
        Plateau& getPlateau() { return plateau; } // accès au plateau
};

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

<<<<<<< HEAD
class GameManager{
    Partie partie_active;
    EtatDuJeu** sauvegardes;
    static GameManager* instance;
};
=======

>>>>>>> feature/main

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
