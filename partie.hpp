#ifndef PARTIE_HPP
#define PARTIE_HPP

#include <iostream>
using namespace std;

class Joueur;
class Partie;
class Plateau;
class MementoPartie;
class GameManager;

class Joueur{ //impératif de faire un constructeur de recopie par affectation (utilisation dans MementoPartie)
    Partie* partie;
public:
    void setPartie(Partie* partie);
    bool isIa(); //permet de savoir si le joueur est une ia
    Joueur();
};


class Plateau{ //impératif de faire un constructeur de recopie par affectation (utilisation dans MementoPartie)
};

class MementoPartie{
    int numero_tour;
    Plateau plateau;
    Joueur joueurs[2];
    Joueur* joueur_courant;
public:
    friend class Partie;//evite de faire des getters, a voir si c'est judicieux
    MementoPartie(const Partie& partie);
    MementoPartie();
    MementoPartie& operator=(const MementoPartie& memento);
};

class Partie{
    int tourActuel;
    int nb_retour_arriere; //rajouté par rapport à l'uml
    MementoPartie etat_precedent; //remplace historique dans l'uml
    Plateau plateau;
    Joueur* joueurs[2]; //tableau de pointeurs sur les deux joueurs de la partie,rajouté par rapport à l'uml
    int start_joueur_id; //position du joueur qui commence le tour dans le tableau de 2 joueurs
    Joueur* joueur_courant; //pointeur sur le joueur courant, rajouté par rapport à l'uml

    Partie& operator=(const Partie& partie); //constructeurs de recopie et d'affectation privés pour l'instant
    Partie(const Partie& partie);
public:
    Partie();

    //getters
    const Plateau& getPlateau() const { return plateau; }
    Plateau& getPlateau() { return plateau; } // je sais pas s'il faut mettre ça mais on les avait mis en TD. a voir
    int getTourActuel()const{return tourActuel;}
    const Joueur& getJoueur(int i)const{return *joueurs[i];}
    const Joueur& getJoueurCourant()const{return *joueur_courant;}

    void setStartJoueurId();//méthode qui détermine qui commence la partie
    void commencerPartie();
    void lancerProchainTour();
    void sauvegarderEtat();
    void annulerCoup();
    void terminerPartie();
    void restaurerEtat(const MementoPartie &etat);
    ~Partie();
};

class GameManager{
    Partie partie_active;
    MementoPartie** sauvegardes;
    static GameManager* instance;
};

#endif // PARTIE_HPP
