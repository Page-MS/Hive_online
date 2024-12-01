#include "partie.hpp"

//méthode qui détermine qui commence la partie
void Partie::setStartJoueurId(){
    if (etat_actuel.joueurs[0].getIsIA()){
        start_joueur_id = 1; //l'humain commence toujours
    }else if(etat_actuel.joueurs[1].getIsIA()){
        start_joueur_id = 0; 
    }else{ //s'il y a 2 joueurs humains dans la partie
        start_joueur_id = rand() % 2; //on choisit aléatoirement le joueur qui commence
    }
}

void Partie::commencerPartie(string pseudo1, string pseudo2, bool IA1, bool IA2){
    Joueur* joueur1 = new Joueur(pseudo1, IA1);
    Joueur* joueur2 = new Joueur(pseudo2, IA2);
    etat_precedent = NULL;
    etat_actuel.numero_tour = 0;
    etat_actuel.joueurs[0] = joueur1;
    etat_actuel.joueurs[1] = joueur2;
    setStartJoueurId();
    lancerProchainTour();
    cout << "Debut de la partie" << endl;
}

void Partie::terminerPartie(){
    // Appeler une fonction de EtatDuJeu qui considère si un coup est gagnant
    cout << "Fin de la partie" << endl;
    // retourner le gagnant et l'afficher
}

void Partie::sauvegarderEtat(){
    MementoPartie memento(this->tourActuel, this->plateau,*this->joueurs[0], *this->joueurs[1], *this->joueur_courant);  
    etat_precedent = memento;
}

void Partie::restaurerEtat(const MementoPartie& etat){
    tourActuel = etat.numero_tour;
    plateau = etat.plateau; //nécessite un constructeur de recopie de Plateau
    *joueurs[0] = etat.joueurs[0];
    *joueurs[1] = etat.joueurs[1];
    if(etat.joueur_courant == &etat.joueurs[0]) {
            joueur_courant = joueurs[0]; 
    }else if(etat.joueur_courant == &etat.joueurs[1]) {
            joueur_courant = joueurs[1]; 
    }else{
            joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans `etat`
    }
}

void Partie::lancerProchainTour(){
    etat_precedent = MementoPartie(this->tourActuel, this->plateau,*this->joueurs[0], *this->joueurs[1], *this->joueur_courant); //on sauvegarde l'état actuel avant de lancer le tour suivant
    tourActuel++;
    cout << "Tour " << tourActuel << endl;
    joueur_courant = joueurs[start_joueur_id];
    //première chose à faire : voir si le joueur veut revenir en arrière
    if(nb_retour_arriere > 0){
        string choice = "";
        do {
            cout << "Voulez-vous revenir en arrière ? (Y/N)" << endl;
            cin >> choice;
        } while (choice != "Y" && choice != "N");
            if(choice == "Y"){
                nb_retour_arriere--;
                annulerCoup();
            }
        }
    //faire le tour 
}

Partie& Partie::operator=(const Partie& partie){}

Partie(const Partie& partie){
    
}

MementoPartie::MementoPartie(int num_tour, const Plateau& p, const Joueur& j1, const Joueur& j2, const Joueur& jc){
    numero_tour = num_tour;
    plateau = p; //nécessite un constructeur de recopie de Plateau
    joueurs[0] = j1; //constructeur de recopie de Joueur
    joueurs[1] = j2;
    joueur_courant = nullptr;

    if(&jc == &j1) {
        joueur_courant = &joueurs[0];
    }else if(&jc == &j2) {
        joueur_courant = &joueurs[1];
    }else{
        joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans `partie`
    }
}

MementoPartie::MementoPartie(){
    numero_tour = 0;
    plateau = Plateau();
    joueurs[0] = Joueur(); //constructeur de recopie de Joueur
    joueurs[1] = Joueur();
    joueur_courant = nullptr;
}


MementoPartie& MementoPartie::operator=(const MementoPartie& memento){
    if(this != &memento){
        numero_tour = memento.numero_tour;
        plateau = memento.plateau; //nécessite un constructeur de recopie de Plateau
        joueurs[0] = memento.joueurs[0]; //constructeur de recopie de Joueur
        joueurs[1] = memento.joueurs[1];
        if(memento.joueur_courant == &memento.joueurs[0]) {
            joueur_courant = &joueurs[0];
        }else if(memento.joueur_courant == &memento.joueurs[1]) {
            joueur_courant = &joueurs[1];
        }else{
            joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans le memento que l'on recopie
        }
    }
    return *this;
}

EtatDuJeu(int num_tour, const Plateau& p,  const Joueur& j1, const Joueur& j2, const Joueur& jc){
    numero_tour = num_tour;
    plateau = p; //nécessite un constructeur de recopie de Plateau
    joueurs[0] = j1; //constructeur de recopie de Joueur
    joueurs[1] = j2;
    joueur_courant = nullptr;

    if(&jc == &j1) {
        joueur_courant = &joueurs[0];
    }else if(&jc == &j2) {
        joueur_courant = &joueurs[1];
    }else{
        joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans `partie`
    }
}

EtatDuJeu::EtatDuJeu(){
    numero_tour = 0;
    plateau = Plateau();
    joueurs[0] = Joueur(); //constructeur de recopie de Joueur
    joueurs[1] = Joueur();
    joueur_courant = nullptr;
}


EtatDuJeu& EtatDuJeu::operator=(const EtatDuJeu& jeu){
    if(this != &jeu){
        numero_tour = jeu.numero_tour;
        plateau = jeu.plateau; //nécessite un constructeur de recopie de Plateau
        joueurs[0] = jeu.joueurs[0]; //constructeur de recopie de Joueur
        joueurs[1] = jeu.joueurs[1];
        
        if(jeu.joueur_courant == &jeu.joueurs[0]) joueur_courant = &joueurs[0];

        else if(jeu.joueur_courant == &jeu.joueurs[1]) joueur_courant = &joueurs[1];

        else joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans le jeu que l'on recopie
    }
    return *this;
}

vector<Mouvement> EtatDuJeu::coupPossibles(Joueur& j){
    
}

bool EtatDuJeu::FinDuJeu() const{

}

void EtatDuJeu::annulerDernierMouvement(){

}

