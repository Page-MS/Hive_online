#ifndef PARTIE_HPP
#define PARTIE_HPP

#include <iostream>
#include "Joueur.h"

using namespace std;

class EtatDuJeu {
    private:
        Plateau plateau;               // plateau avec les pièces
        vector<Mouvement> historique;  // liste des coups
        vector<Joueur*> joueurs;             // liste des joueurs
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
        Joueur* getJoueurCourant() const {return joueur_courant;}
        Joueur* getAutreJoueur() const ;
        const int getNumTour() const {return numero_tour;}
        vector<Mouvement>& getHistorique() {return historique;}
        const vector<const Piece*> reserveJoueur(Joueur* j) const;//Retourne les pieces de la reserve d'un joueur

        void afficher() const { plateau.afficher(joueur_courant->getCamp(), joueur_courant->getNom(), getAutreJoueur()->getNom()); }
};

class Partie{
    private :
        //attributs :
        //int nb_retour_arriere; //nombre de retours en arriere possibles pour toute la partie (tous joueurs confondus)
        //EtatDuJeu historique_etats[15]; //historique des etats du jeu : convention : 0 = etat actuel, 1 = etat precedent, 2 = etat d'avant precedent, 3 = etat d'avant avant-precedent

        std::vector<EtatDuJeu*> historique;
        EtatDuJeu* etat_actuel;
        int start_joueur_id; //position du joueur qui commence le tour dans le tableau de 2 joueurs
    
        //constructeurs de recopie et d'affectation prives :
        Partie& operator=(const Partie& partie);
        Partie(const Partie& partie);

    public:
        Partie();
        ~Partie();
        EtatDuJeu& getEtatActuel() { return *historique.at(historique.size()-1);}
        void setStartJoueurId();//Méthode qui détermine qui commence la partie
        void commencerPartie(); //Gere les initialisations
        void annulerDernierMouvement();
        void jouerTour(); //Gere le deroulement d'un tour
        void lancerPartie(); //Gere le deroulement de la partie
        bool finPartie(); //Verifie si des conditions d'arret de la partie sont remplies
};

class GameManager{
    static GameManager* instance;

    Partie partie_active;
    GameManager()=default;

    public:
        static GameManager& getInstance();
        void afficher_menu();
        //void chargerJeu(); //Appelee pour charger une partie a partir d'un fichier
};

#endif

