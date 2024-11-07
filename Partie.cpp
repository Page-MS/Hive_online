#include "Partie.hpp"

Joueur::Joueur(){
    partie = nullptr;
}

bool Joueur::isIa(){
    return false; //à modifier pour savoir si le joueur est une ia
}

void Joueur::setPartie(Partie* partie){
    this->partie = partie;
}

Partie::Partie(){
    tourActuel = 0;
    etat_precedent = MementoPartie();
    plateau = Plateau();
    joueurs[0] = nullptr;
    joueurs[1] = nullptr;
}

Partie::~Partie(){
    delete joueurs[0];
    delete joueurs[1];
}

void Partie::setStartJoueurId(){
    if (joueurs[0]->isIa()){ //nécessite une méthode dans Joueur pour savoir s'il est une Ia
        start_joueur_id = 1; //l'humain commence toujours
    }else if(joueurs[1]->isIa()){
        start_joueur_id = 0;
    }else{ //s'il y a 2 joueurs humains dans la partie
        start_joueur_id = rand() % 2; //on choisit aléatoirement le joueur qui commence
    }
}

void Partie::commencerPartie(){
    tourActuel = 0;
    plateau = Plateau();
    joueurs[0] = new Joueur(); //mettre les bons attributs dans les constructeurs de la classe Joueur
    joueurs[1] = new Joueur();
    joueurs[0]->setPartie(this); //nécessite d'avoir un attribut partie dans Joueur qui est un pointeur vers la partie en cours
    joueurs[1]->setPartie(this); //et une méthode setPartie dans Joueur
    setStartJoueurId(); //méthode qui détermine qui commence la partie
    lancerProchainTour();
    cout << "Debut de la partie" << endl;
}

void Partie::terminerPartie(){
    delete joueurs[0];
    delete joueurs[1];
    cout << "Fin de la partie" << endl;
}

void Partie::sauvegarderEtat(){
    MementoPartie memento(*this);
    etat_precedent = memento;
}

void Partie::lancerProchainTour(){
    etat_precedent = MementoPartie(*this); //on sauvegarde l'état actuel avant de lancer le tour suivant
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

MementoPartie::MementoPartie(const Partie& partie){
    numero_tour = partie.getTourActuel();
    plateau = partie.getPlateau(); //nécessite un constructeur de recopie de Plateau
    joueurs[0] = partie.getJoueur(0); //constructeur de recopie de Joueur
    joueurs[1] = partie.getJoueur(1);
    joueur_courant = nullptr;

    if(&partie.getJoueurCourant() == &partie.getJoueur(0)) {
            joueur_courant = &joueurs[0];
    }else if(&partie.getJoueurCourant() == &partie.getJoueur(1)) {
            joueur_courant = &joueurs[1];
    }else{
            joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans `partie`
    }
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

void Partie::annulerCoup(){
    restaurerEtat(etat_precedent); //annuler un coup revient à restaurer l'état précédent
}
