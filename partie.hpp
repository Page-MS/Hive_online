#ifndef PARTIE_HPP
#define PARTIE_HPP

#include <iostream>
#include "Joueur.h"

using namespace std;
class Joueur;
class Mouvement;

class EtatDuJeu {
    private:
        Plateau plateau;               // plateau avec les pièces
        vector<Mouvement> historique;  // liste des coups
        Joueur* joueurs[2];             // liste des joueurs
        int numero_tour;
        Joueur* joueur_courant;
        friend class Partie;
    public:
        EtatDuJeu(int num_tour, Plateau p,  Joueur* j1, Joueur* j2, Joueur* jc);
        EtatDuJeu(); //Pour initialiser historique_etats dans Partie
        EtatDuJeu(const EtatDuJeu& other);
        ~EtatDuJeu();
        EtatDuJeu& operator=(const EtatDuJeu& jeu);
        const vector<Mouvement> coupsPossibles(Joueur* j) const;  // coups possibles
        void ajouterMouvement(const Mouvement& mvt) {historique.push_back(mvt);} // ajoute un coup à l'historique
        Plateau getPlateau() {return plateau;} // accès au plateau
        Joueur** getJoueurs() {return joueurs;}
        Joueur* getJoueurCourant() {return joueur_courant;}
        const int getNumTour() const {return numero_tour;}
        vector<Mouvement>& getHistorique() {return historique;}
        const vector<Piece*> reserveJoueur(Joueur* j) const;//Retourne les pieces de la reserve d'un joueur
};

class Partie{
    private :
        //attributs :
        int nb_retour_arriere; //nombre de retours en arriere possibles pour toute la partie (tous joueurs confondus)
        EtatDuJeu historique_etats[4]; //historique des etats du jeu : convention : 0 = etat actuel, 1 = etat precedent, 2 = etat d'avant precedent, 3 = etat d'avant avant-precedent
        int start_joueur_id; //position du joueur qui commence le tour dans le tableau de 2 joueurs
    
        //constructeurs de recopie et d'affectation prives :
        Partie& operator=(const Partie& partie);
        Partie(const Partie& partie);

    public:
        Partie() : nb_retour_arriere(0), start_joueur_id(0) {}
        EtatDuJeu& getEtatActuel(){return historique_etats[0];}
        void setStartJoueurId();//Méthode qui détermine qui commence la partie
        void commencerPartie(); //Gere les initialisations
        void annulerDernierMouvement();
        void jouerTour(); //Gere le deroulement d'un tour
        void lancerPartie(); //Gere le deroulement de la partie
        bool finPartie()const; //Verifie si des conditions d'arret de la partie sont remplies
        //void sauvegarderPartie(ofstream& outFile) const;
        //void restaurerPartie(ifstream& inFile);
};

class GameManager{
    Partie partie_active;
    static GameManager* instance;
    
    public:
        void afficher_menu();
        //void chargerJeu(); //Appelee pour charger une partie a partir d'un fichier
};

#endif

