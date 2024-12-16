#include "partie.hpp"

//Méthode qui détermine qui commence la partie
void Partie::setStartJoueurId(){
    if (historique_etats[0].joueurs[0]->getIsIA() && !(historique_etats[0].joueurs[1]->getIsIA())){
        start_joueur_id = 1; //l'humain commence toujours
    }else if(historique_etats[0].joueurs[1]->getIsIA() && !(historique_etats[0].joueurs[0]->getIsIA())){
        start_joueur_id = 0; 
    }else{ //s'il y a 2 joueurs humains ou 2 IA dans la partie
        start_joueur_id = rand() % 2; //on choisit aléatoirement le joueur qui commence
    }
}

void Partie::commencerPartie(string pseudo1, string pseudo2, bool IA1, bool IA2){
    Plateau game_plateau = Plateau();
    Joueur* jc = nullptr;
    Joueur* j1 = nullptr;
    Joueur* j2 = nullptr;
    if(IA1 && IA2){ // 2 joueurs IA
        int niv_ia1;
        cout << "Entrez le niveau de difficulté pour " << pseudo1 << " : " << endl;
        cin >> niv_ia1;
        j2 = new IAJoueur(pseudo1, niv_ia1);
        int niv_ia2;
        cout << "Entrez le niveau de difficulté pour " << pseudo2 << " : " << endl;
        cin >> niv_ia2;
        j2 = new IAJoueur(pseudo2, niv_ia2);
    }else if(IA1){ // Une IA et un humain
        int niv_ia;
        cout << "Entrez le niveau de difficulté pour " << pseudo1 << " : " << endl;
        cin >> niv_ia;
        j1 = new IAJoueur(pseudo1, niv_ia);
        j2 = new Joueur(pseudo2);
    }else if(IA2){ // Une IA et un humain
        int niv_ia;
        cout << "Entrez le niveau de difficulté pour " << pseudo2 << " : " << endl;
        cin >> niv_ia;
        j1 = new Joueur(pseudo1);
        j2 = new IAJoueur(pseudo2, niv_ia);
        jc = j1;
    }else{ // 2 joueurs huamins
        j1 = new Joueur(pseudo1);
        j2 = new Joueur(pseudo2);
    }
    setStartJoueurId();
    jc = (start_joueur_id == 0) ? j1 : j2; //On determine qui commence la partie
    EtatDuJeu first_etat(0, game_plateau, j1, j2, jc);
    historique_etats[0] = first_etat;
    for(int i = 1; i < 4; i++){
        historique_etats[i] = historique_etats[0]; //convention : on initialise les 3 états avec le même état initial
    }
    do{
        cout<<"Entrez le nombre de retours en arrière possibles : (Entre 0 et 3)"<<endl; 
        cin>>nb_retour_arriere;
    }while(nb_retour_arriere < 0 || nb_retour_arriere > 3);
    cout << "Debut de la partie" << endl;
}

void Partie::terminerPartie(){
    // appelé par coup gagnant + égalité (on peut plus avancer)
    cout << "Fin de la partie" << endl;
    // afficher le résultat
    // Libérer tout
    // Revenir au menu
}

EtatDuJeu Partie::sauvegarderEtat(){
    EtatDuJeu saved_etat(historique_etats[0].numero_tour, historique_etats[0].plateau,historique_etats[0].joueurs[0], historique_etats[0].joueurs[1], historique_etats[0].joueur_courant);
    return saved_etat;
}

void Partie::restaurerEtat(const EtatDuJeu& etat){
    /*Deux solutions : soit on fait 2 getters pour chaque attributs (exemple avec getNumTour ci dessous, le getter a gauche du = est le getter non const,
     et celui à droite du = est le getter const, soit on met friend class Partie dans EtatDuJeu.
     Friend class est plus simple */
    historique_etats[0].numero_tour = etat.numero_tour;
    historique_etats[0].historique = etat.historique;
    historique_etats[0].plateau = etat.plateau;
    historique_etats[0].joueurs[0] = etat.joueurs[0];
    historique_etats[0].joueurs[1] = etat.joueurs[1];
    if(etat.joueur_courant == etat.joueurs[0]) {
        historique_etats[0].joueur_courant = historique_etats[0].joueurs[0];
    }else if(etat.joueur_courant == etat.joueurs[1]) {
        historique_etats[0].joueur_courant = historique_etats[0].joueurs[1];
    }else{
        historique_etats[0].joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans `etat`
    }
}

void Partie::jouerTour(){
    historique_etats[3] = historique_etats[2];
    historique_etats[2] = historique_etats[1];
    historique_etats[1] = historique_etats[0]; //on sauvegarde l'état actuel avant de lancer le tour suivant
    historique_etats[0].numero_tour++;
    cout << "Tour " << historique_etats[0].numero_tour << endl;
    historique_etats[0].joueur_courant = historique_etats[0].joueurs[start_joueur_id];
    //On affiche le menu d'actions possible pour le prochain tour
    cout << "Que souhaitez-vous faire ? \n";
    int menu = 0;
    while (menu != 4) {
        cout<< "1 - Ajouter une piece \n" << endl;
        cout<< "2 - Déplacer une piece \n" << endl;
        cout<< "3 - Annuler le coup precedant \n" << endl;
        cout<< "4 - Sauvegarder et arreter la partie \n" << endl;
        cin >> menu;
        
        vector<Coords> liste_pos = historique_etats[0].joueur_courant->getPlacementPossibilities(historique_etats[0].plateau);
        vector<Mouvement> liste_coups = historique_etats[0].coupPossibles(historique_etats[0].joueur_courant);
        if(liste_pos.size() == 0 && liste_coups.size() == 0){
            cout<<"Vous n'avez pas de possibilité de jouer ce tour !"<<endl;
            return;
        }
        
        switch (menu) {
            case 1: {
                vector<Piece*> pieces = historique_etats[0].joueur_courant->getPieces(); //BESOIN GETPIECES
                vector<Piece*> reserve;
                int i = 0;
                cout<<"Liste des pieces disponibles : ";
                for (const auto piece : pieces) {
                    if (historique_etats[0].plateau.inReserve(*piece)) {
                        reserve.push_back(const_cast<Piece*>(piece));
                        cout << i << ". " << piece->getType() << "\n";
                        i++;
                    }
                }
                int choix1 = -1;
                while (choix1 <0 || choix1>reserve.size()) {
                    cout << "Quelle piece voulez vous placer ? \n";
                    cin>>choix1;
                }
                vector<Coords> liste_pos = historique_etats[0].joueur_courant->getPlacementPossibilities(historique_etats[0].plateau);
                cout << "Voici vos placements possibles : \n";
                int j = 0;
                for (const auto &pos : liste_pos){
                    cout << j << ". (" << pos.getX() << "," << pos.getY()<< ")";
                    j++;
                }
                int choix2 = -1;
                while (choix2 <0 || choix2>liste_pos.size()) {
                    cout << "Ou souhaitez vous placer votre piece ? \n";
                    cin>>choix2;
                }
                historique_etats[0].joueur_courant->jouerCoupCreer(reserve[choix1], liste_pos[choix2], historique_etats[0].plateau);
            }
            case 2: {
                vector<Mouvement> liste_coups = historique_etats[0].coupPossibles(historique_etats[0].joueur_courant);
                cout << "Voici vos coups possibles : \n";
                int j = 0;
                for (const auto &coup : liste_coups){
                    cout << j << ". " << coup.getPiece()->getType() << " - à (" << coup.getPosInitial().getX() << " , " << coup.getPosInitial().getY() << ") vers (" << coup.getPosFinal().getX() << " , " << coup.getPosFinal().getY() << ") \n";
                    j++;
                }
                int choix = -1;
                while (choix <0 || choix>liste_coups.size()) {
                    cout << "Quelle possibilité souhaitez-vous jouer ? \n";
                    cin>>choix;
                }
                Mouvement coupChoisi = liste_coups.at(choix);
                historique_etats[0].joueur_courant->jouerCoupDeplacer(coupChoisi.getPiece(), coupChoisi.getPosFinal(), historique_etats[0].plateau);
            }
            case 3: {
                //vérifier si le tour actuel est supérieur à 2 (chaque joueur a déjà joué au moins une fois)
                if(historique_etats[0].numero_tour > 2){
                    //vérifier si il reste des retours en arriere pour cette partie
                    if(nb_retour_arriere > 0){
                        annulerDernierMouvement();
                        historique_etats[0].numero_tour = historique_etats[0].numero_tour - 2;
                    }
                    else {
                        cout<<"Il n'y a pas ou plus de retour en arriere possible pour cette partie ! \n";
                    }
                }
                else{
                    cout<<"Il faut qu'au moins chaque joueur aient joué un tour pour revenir en arriere ! \n";
                }
            }
            case 4: {
                sauvegarderPartie();
                cout<<"Votre partie a ete sauvegardee, au revoir ! \n";
                break;
            }
            default:
                cout<<"Valeur invalide, reessayez\n";
        }
    }
}

bool Partie::finPartie()const{
    for(const auto joueur : historique_etats[0].joueurs){
        for(const auto piece : joueur->getPieces()){
            if(piece->getType() == 1){
                const Coords* c = historique_etats[0].plateau.coordsPiece(*piece);
                if (c != nullptr) {
                    if(historique_etats[0].plateau.getGraphe().isSurrounded(*c)) return true;
                }
            }
        }
    }

    if(historique_etats[0].coupPossibles(historique_etats[0].joueurs[0]).size()!=0 || historique_etats[0].coupPossibles(historique_etats[0].joueurs[0]).size()!=0){
        return false;
    }
    return true;
}

void Partie::jouer(){
    string pseudo1, pseudo2;
    bool ia1, ia2;
    cout<<"Entrez le pseudo du premier joueur :"<<endl;
    cin>>pseudo1;
    cout<<"Entrez le pseudo du deuxieme joueur :"<<endl;
    cin>>pseudo2;
    
    int choix = -1;
    while(choix != 0 && choix != 1){
        cout<<"Le joueur 1 est il une Ia ? (1 : oui, 0 : non)"<<endl;
        cin>>choix;
    }
    ia1 = (choix == 0) ? false : true;
    choix = -1;
    while(choix != 0 && choix != 1){
        cout<<"Le joueur 2 est il une Ia ? (1 : oui, 0 : non)"<<endl;
        cin>>choix;
    }
    ia2 = (choix == 0) ? false : true;
    commencerPartie(pseudo1, pseudo2, ia1, ia2);
    while(historique_etats[0].numero_tour < 6 || !finPartie()){
        jouerTour();
        if(historique_etats[0].joueur_courant == historique_etats[0].joueurs[0]){
            historique_etats[0].joueur_courant = historique_etats[0].joueurs[1];
        }else{
            historique_etats[0].joueur_courant = historique_etats[0].joueurs[0];
        }
    }
    
    if(historique_etats[0].coupPossibles(historique_etats[0].joueurs[0]).size()==0 && historique_etats[0].coupPossibles(historique_etats[0].joueurs[0]).size()==0){
        cout<<"Egalite !"<<endl;
        cout<<"Merci d'avoir joue a hive !"<<endl;
    }
    
    for(const auto joueur : historique_etats[0].joueurs){
        for(const auto piece : joueur->getPieces()){
            if(piece->getType() == 1){
                const Coords* c = historique_etats[0].plateau.coordsPiece(*piece);
                if (c != nullptr) {
                    if(historique_etats[0].plateau.getGraphe().isSurrounded(*c)){
                        if(joueur == historique_etats[0].joueurs[0]){
                            cout<<"Le joueur "<<historique_etats[0].joueurs[1]->getNom()<<" a gagne !"<<endl;
                            cout<<"Merci d'avoir joue a Hive !"<<endl;
                        }
                        
                        if(joueur == historique_etats[0].joueurs[1]){
                            cout<<"Le joueur "<<historique_etats[0].joueurs[0]->getNom()<<" a gagne !"<<endl;
                            cout<<"Merci d'avoir joue a Hive !"<<endl;
                        }
                    }
                }
            }
        }
    }
    
    
}

EtatDuJeu::EtatDuJeu(int num_tour, const Plateau& p,  Joueur* j1, Joueur* j2, Joueur* jc){
    numero_tour = num_tour;
    plateau = p;
    joueurs[0] = j1;
    joueurs[1] = j2;
    joueur_courant = nullptr;
    if(jc == j1) {
        joueur_courant = joueurs[0];
    }else if(jc == j2) {
        joueur_courant = joueurs[1];
    }else{
        joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans `partie`
    }
}

void sauvegarderPartie();

EtatDuJeu::EtatDuJeu(){
    numero_tour = 0;
    plateau = Plateau();
    joueurs[0] = new Joueur;
    joueurs[1] = new Joueur;
    joueur_courant = nullptr;
}

EtatDuJeu::EtatDuJeu(const EtatDuJeu& other){
    numero_tour = other.numero_tour;
    plateau = other.plateau; //nécessite un constructeur de recopie de Plateau
    joueurs[0] = other.joueurs[0];
    joueurs[1] = other.joueurs[1];
    if(other.joueur_courant == other.joueurs[0]) joueur_courant = joueurs[0];
    else if(other.joueur_courant == other.joueurs[1]) joueur_courant = joueurs[1];
    else joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans le jeu que l'on recopie
}

EtatDuJeu& EtatDuJeu::operator=(const EtatDuJeu& jeu){
    if(this != &jeu){
        numero_tour = jeu.numero_tour;
        plateau = jeu.plateau; //nécessite un constructeur de recopie de Plateau
        joueurs[0] = jeu.joueurs[0];
        joueurs[1] = jeu.joueurs[1];
        if(jeu.joueur_courant == jeu.joueurs[0]) joueur_courant = joueurs[0];
        else if(jeu.joueur_courant == jeu.joueurs[1]) joueur_courant = joueurs[1];
        else joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans le jeu que l'on recopie
    }
    return *this;
}

const vector<Mouvement> EtatDuJeu::coupPossibles(Joueur* j) const {
    vector<Mouvement> mvt;
    vector<Piece*> pj = j->getPieces();
    for (const Piece* piece : pj) {
        if (!plateau.isPieceStuck(*piece)) {
            const Coords* c = plateau.coordsPiece(*piece);
            if (c != nullptr) {
                const vector<Coords> prochains = piece->coupsPossibles(plateau.getGraphe(), *c);
                for (const Coords &coup : prochains) { // Assurez-vous que 'coup' est du type Coords
                    mvt.emplace_back(piece, *c, coup);
                }
            }
        }
    }
    return mvt;
}

bool EtatDuJeu::coupGagnant() const{
}

void Partie::annulerDernierMouvement(){ //On remonte au tour précédent de chacun des joueurs
    historique_etats[0] = historique_etats[2]; //tour précédent du joueur courant
    historique_etats[1] = historique_etats[3]; //tour précédnt de l'autre joueur
    nb_retour_arriere --;
}

void GameManager::afficher_menu() {
    //Est appelée en début d'execution pour lancer la boucle de gameplay
    //sert à gérer le switch
    int choice =0;
    while (choice != 2) {
        cout<<"\n\n ----------------------------------\n\n"<<"Bienvenue dans Hive, le jeu iconique enfin sous forme virtuelle !\n"
                                                             "Que souhaitez vous faire ?\n"
                                                             "Pour lancer une partie tapez 1\n "
                                                             "Pour quitter, tappez \n"
                                                             "Votre choix :";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "\n Oups ce n'est pas encore implemente\n";
                break;
            case 2:
                cout << "\nAu revoir !";
                break;
            default:
                cout<<"\nValeur invalide, reessayez\n";
        }
    }
}


