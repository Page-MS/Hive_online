#include "partie.hpp"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>

EtatDuJeu::EtatDuJeu(int num_tour, Plateau p,  Joueur* j1, Joueur* j2, Joueur* jc){
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

EtatDuJeu::~EtatDuJeu() {
    //Destruction des joueurs
    //TODO resoudre le segmentation fault causé ici, peut être que les pointeurs ont déjà été supprimés par la suppression d'un autre été du jeu
    /*for (auto joueur : joueurs) {
        if(joueur) {
            delete joueur;
            joueur= nullptr;
        }
    }
    joueur_courant = nullptr;*/
}

EtatDuJeu::EtatDuJeu(){
    numero_tour = 0;
    plateau = Plateau();
    joueurs[0] = new Joueur;
    joueurs[1] = new Joueur;
    joueur_courant = nullptr;
}

EtatDuJeu::EtatDuJeu(const EtatDuJeu& other){
    numero_tour = other.numero_tour;
    plateau = other.plateau;
    joueurs[0] = other.joueurs[0];
    joueurs[1] = other.joueurs[1];
    if(other.joueur_courant == other.joueurs[0]) joueur_courant = joueurs[0];
    else if(other.joueur_courant == other.joueurs[1]) joueur_courant = joueurs[1];
    else joueur_courant = nullptr; // Au cas où `joueurCourant` est nul dans le jeu que l'on recopie
}


EtatDuJeu& EtatDuJeu::operator=(const EtatDuJeu& jeu){
    if(this != &jeu){
        numero_tour = jeu.numero_tour;
        plateau = jeu.plateau;
        joueurs[0] = jeu.joueurs[0];
        joueurs[1] = jeu.joueurs[1];
        historique = jeu.historique;
        plateau.piecesCoherence(joueurs[0]->getPieces(), joueurs[1]->getPieces());
        if(jeu.joueur_courant == jeu.joueurs[0]) joueur_courant = joueurs[0];
        else if(jeu.joueur_courant == jeu.joueurs[1]) joueur_courant = joueurs[1];
        else joueur_courant = nullptr; // Au cas où joueur_courant est nul dans le jeu que l'on recopie
    }
    return *this;
}

Joueur* EtatDuJeu::getAutreJoueur() {
    if (joueurs[0]==joueur_courant) return joueurs[1];
    return joueurs[0];
}

const vector<Mouvement> EtatDuJeu::coupsPossibles(Joueur* j) const {
    vector<Mouvement> mvt;
    vector<const Piece*> pj = j->getPieces();

    for (const Piece* piece : pj) {
        if (!plateau.isPieceStuck(*piece)) {
            const Coords* c = plateau.coordsPiece(*piece);
            if (c != nullptr) {
                Graphe copygraphe = plateau.getGraphe();
                const vector<Coords> prochains = piece->coupsPossibles(&copygraphe, *c);
                for (const Coords &coup : prochains) { // Assurez-vous que 'coup' est du type Coords
                    mvt.emplace_back(piece, *c, coup);
                }
            }
        }
    }
    return mvt;
}

//Méthode qui détermine qui commence la partie
void Partie::setStartJoueurId(){
    srand(static_cast<int>(time(0)));
    if (historique_etats[0].joueurs[0]->getIsIA() && !(historique_etats[0].joueurs[1]->getIsIA())){
        start_joueur_id = 1; //l'humain commence toujours
    }else if(historique_etats[0].joueurs[1]->getIsIA() && !(historique_etats[0].joueurs[0]->getIsIA())){
        start_joueur_id = 0;
    }else{ //s'il y a 2 joueurs humains ou 2 IA dans la partie
        start_joueur_id = rand() % 2; //on choisit aléatoirement le joueur qui commence
    }
}

void Partie::commencerPartie() {
    string pseudo1, pseudo2;
    cout << "Entrez le pseudo du premier joueur :" << endl;
    cin >> pseudo1;
    cout << "Entrez le pseudo du deuxieme joueur :" << endl;
    cin >> pseudo2;

    bool ia1, ia2;
    int choix = -1;
    while (true) {
        cout << "Le joueur 1 est il une IA ? (1 : oui, 0 : non)" << endl;
        cin >> choix;
        if (cin.fail()) { // Gestion input invalide
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Retire input invalide du buffer
            cout << "\nValeur invalide, reessayez\n";
            continue; // Re effectue la boucle
        }
        if (choix == 0 || choix == 1) {
            // Valid choice
            break;
        }
    }
    ia1 = (choix == 0) ? false : true;
    choix = -1;
    while (true) {
        cout << "Le joueur 2 est il une IA ? (1 : oui, 0 : non)" << endl;
        cin >> choix;
        if (cin.fail()) { // Gestion input invalide
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Retire input invalide du buffer
            cout << "\nValeur invalide, reessayez\n";
            continue; // Re effectue la boucle
        }
        if (choix == 0 || choix == 1) {
            // Valid choice
            break;
        }
    }
    ia2 = (choix == 0) ? false : true;
    if (ia1 && ia2) { // 2 joueurs IA
        historique_etats[0].joueurs[0] = new IAJoueur(pseudo1, true);
        historique_etats[0].joueurs[1] = new IAJoueur(pseudo2, false);
    } else if (ia1) { // Une IA et un humain
        historique_etats[0].joueurs[0] = new IAJoueur(pseudo1, true);
        historique_etats[0].joueurs[1] = new Joueur(pseudo2, false);
    } else if (ia2) { // Une IA et un humain
        historique_etats[0].joueurs[0] = new Joueur(pseudo1, true);
        historique_etats[0].joueurs[1] = new IAJoueur(pseudo2, false);
    } else { // 2 joueurs huamins
        historique_etats[0].joueurs[0] = new Joueur(pseudo1, true);
        historique_etats[0].joueurs[1] = new Joueur(pseudo2, false);
    }

    historique_etats[0].plateau = Plateau();
    historique_etats[0].numero_tour = 0;

    //On determine qui commence la partie
    setStartJoueurId();
    historique_etats[0].joueur_courant = (start_joueur_id == 0) ? historique_etats[0].joueurs[0]
                                                                : historique_etats[0].joueurs[1];

    for (Joueur *joueur: historique_etats[0].joueurs) {
        historique_etats[0].plateau.fillReserve(joueur->getPieces());
    }

    for (int i = 1; i < 4; i++) {
        historique_etats[i] = historique_etats[0]; //convention : on initialise les 3 autres états avec le même état initial
    }
    do {

        nb_retour_arriere = 4;
        while (true) {
            cout << "Entrez le nombre de retours en arriere possibles : (Entre 0 et 3)" << endl;
            cin >> nb_retour_arriere;
            if (cin.fail()) { // Gestion input invalide
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Retire input invalide du buffer
                cout << "\nValeur invalide, reessayez\n";
                continue; // Re effectue la boucle
            }
            if (nb_retour_arriere <= 3 && nb_retour_arriere >= 0) {
                // Valid choice
                break;
            }
        }

    } while (nb_retour_arriere < 0 || nb_retour_arriere > 3);
    {
        cout << "Debut de la partie" << endl;
    }
}

const vector<const Piece*> EtatDuJeu::reserveJoueur(Joueur* j) const{
    return plateau.piecesReserve(j->getCamp());
}

void Partie::annulerDernierMouvement(){ //On remonte au tour précédent de chacun des joueurs
    historique_etats[0] = historique_etats[2]; //tour précédent du joueur courant
    historique_etats[1] = historique_etats[3]; //tour précédent de l'autre joueur
    nb_retour_arriere --;
}

void Partie::jouerTour(){
    //Initialisation du tour
    bool tour_fini = false;
    historique_etats[3] = historique_etats[2];
    historique_etats[2] = historique_etats[1];
    historique_etats[1] = historique_etats[0]; //on sauvegarde l'etat actuel avant de lancer le tour suivant
    historique_etats[0].numero_tour++;

    //Affichage du jeu
    cout << "Tour " << historique_etats[0].numero_tour << endl;
    if (historique_etats[0].numero_tour > 1) {
        cout <<"Etat actuel du plateau : " << endl;
        historique_etats[0].plateau.afficher(historique_etats[0].joueur_courant->getCamp(), historique_etats[0].joueur_courant->getNom(), historique_etats[0].getAutreJoueur()->getNom());
    }
    cout << "C'est au joueur " << historique_etats[0].joueur_courant->getNom() << " de jouer." << endl;

    //Si il n'y a plus de piece en reserve, ni de coups possible : on passe le tour
    vector <const Piece*> reserve = historique_etats[0].reserveJoueur(historique_etats[0].joueur_courant);

    //TODO FIx ça de manière plus clean que d'aller chercher l'autre joueur
    vector<Mouvement> liste_coups = historique_etats[0].coupsPossibles( (historique_etats[0].getJoueurCourant()));

    for (auto it = liste_coups.begin(); it != liste_coups.end(); ) {
        if (historique_etats[0].plateau.getGraphe().wouldHiveBreak(it->getPosInitial())) {
            it = liste_coups.erase(it);
        } else {
            ++it;
        }
    }

    if(reserve.size() == 0 && liste_coups.size() == 0){
        cout<<"Vous n'avez pas de possibilite de jouer ce tour !"<<endl;
        return;
    }
    vector<Coords> liste_pos = historique_etats[0].plateau.getGraphe().placableCoords(historique_etats[0].joueur_courant->getCamp());

    //Actions si une IA joue le prochain tour
    if (historique_etats[0].joueur_courant->getIsIA()) {
        if (reserve.empty()) { //Si il ne reste plus de piece en reserve, on en deplace une aleatoirement
            const int coups = rand()%liste_coups.size() +1;//Choix aleatoire d'un deplacement de piece a effectuer
            historique_etats[0].joueur_courant->jouerCoupDeplacer(liste_coups[coups].getPiece(), liste_coups[coups].getPosFinal(), historique_etats[0].plateau);
        }
        else { //Si il reste des pieces en reserve, on en ajoute une aleatoirement
            srand(static_cast<int>(time(0)));
            if (historique_etats[0].numero_tour == 7 || historique_etats[0].numero_tour == 8) { //Si l'abeille n'a pas ete posee au 4eme tour de l'IA
                for (const auto* piece : reserve) {
                    if (piece->getType() == Abeille) {
                        if (liste_pos.empty()) {
                            cout << "Erreur : L'IA ne peut pas poser l'Abeille, mais cela est obligatoire.\n";
                            return;
                        }
                        const int pos = rand()%liste_pos.size(); //Choix aleatoire d'une position pour l'abeille
                        historique_etats[0].joueur_courant->jouerCoupCreer(piece, liste_pos[pos], historique_etats[0].plateau);
                    }
                }
            }
            else {
                const int piece = rand()%reserve.size(); //Choix aleatoire d'une piece de la reserve a ajouter
                const int pos = rand()%liste_pos.size();//Choix aleatoire d'une position pour la piece
                historique_etats[0].joueur_courant->jouerCoupCreer(reserve[piece], liste_pos[pos], historique_etats[0].plateau);
            }
        }
        return;
    }

    //Si l'abeille n'a pas ete posee au 4eme tour du joueur
    if (historique_etats[0].numero_tour == 7 || historique_etats[0].numero_tour == 8) {
        for (const auto *piece : historique_etats[0].reserveJoueur(historique_etats[0].joueur_courant)) {
            if (piece->getType() == Abeille) {
                cout << "Vous devez poser l'Abeille dans ce tour : aucune autre action permise."<<endl;
                if (liste_pos.empty()) {
                    cout << "Erreur : Impossible de poser l'Abeille, mais cela est obligatoire.\n";
                    return;
                }
                cout << "Voici vos placements possibles : \n";
                int j = 0;
                for (const auto &pos : liste_pos){
                    cout << j << ". (" << pos.getX() << "," << pos.getY()<< ")";
                    j++;
                }
                cout<<endl;
                int choix = -1;
                while (choix <0 || choix>liste_pos.size()) {
                    cout << "Ou souhaitez vous placer votre piece ? \n";
                    cin>>choix;
                    if (cin.fail()) { // Gestion input invalide
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Retire input invalide du buffer
                        cout << "\nValeur invalide, reessayez\n";
                        continue; // Re effectue la boucle
                    }
                }
                tour_fini = historique_etats[0].joueur_courant->jouerCoupCreer(piece, liste_pos[choix], historique_etats[0].plateau);
                break;
            }
        }
        return;
    }

    //Si l'abeille n'a toujours pas été posée au 4eme tour du joueur
    if (historique_etats[0].numero_tour == 7 || historique_etats[0].numero_tour == 8) {
        for (const auto *piece : historique_etats[0].reserveJoueur(historique_etats[0].joueur_courant)) {
            if (piece->getType() == Abeille) {
                cout << "Vous devez poser l'Abeille dans ce tour : aucune autre action permise."<<endl;
                cout << "Voici vos placements possibles : \n";
                int j = 0;
                for (const auto &pos : liste_pos){
                    cout << j << ". (" << pos.getX() << "," << pos.getY()<< ")";
                    j++;
                }
                cout<<endl;
                int choix = -1;
                while (choix <0 || choix>liste_pos.size()) {
                    cout << "Ou souhaitez vous placer votre piece ? \n";
                    cin>>choix;
                    if (cin.fail()) { // Gestion input invalide
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Retire input invalide du buffer
                        cout << "\nValeur invalide, reessayez\n";
                        continue; // Re effectue la boucle
                    }
                }
                tour_fini = historique_etats[0].joueur_courant->jouerCoupCreer(piece, liste_pos[choix], historique_etats[0].plateau);
                break;
            }
        }
        if (liste_pos.empty()) {
            cout << "Erreur : Impossible de poser l'Abeille.\n";
        }
    }

    //Menu d'actions possible pour que le joueur humain joue le prochain tour
    cout << "Que souhaitez-vous faire ? \n";
    int menu = 0;
    while ((!tour_fini) || (menu<1) || (menu>3)) {
        cout<< "1 - Ajouter une piece " << endl;
        cout<< "2 - Deplacer une piece " << endl;
        cout<< "3 - Annuler le coup precedant " << endl;
        cin >> menu;
        if (cin.fail()) { // Gestion input invalide
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Retire input invalide du buffer
            cout << "\nValeur invalide, reessayez\n";
            continue; // Re effectue la boucle
        }

        switch (menu) {
            case 1: { //Ajout d'une piece de la reserve sur le plateau
                if (reserve.size() == 0) {
                    cout<<"Vous n'avez plus de pieces à poser. \n";
                    break;
                }
                if (liste_pos.size() == 0) {
                    cout<<"Vous n'avez pas d'endroit disponible ou ajouter une nouvelle piece. \n";
                    break;
                }
                int i = 0;
                cout<<"Liste des pieces disponibles : "<<endl;
                for (const auto piece : reserve) {
                    cout << i << ". " << piece->strPiece() << "\n";
                    i++;
                }
                int choix1 = -1;
                while (choix1 <0 || choix1>reserve.size()) {
                    cout << "Quelle piece voulez vous placer ? (Entrez son indice) \n";
                    cin>>choix1;
                    if (cin.fail()) { // Gestion input invalide
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Retire input invalide du buffer
                        cout << "\nValeur invalide, reessayez\n";
                        continue; // Re effectue la boucle
                    }
                }
                cout << "Voici vos placements possibles : \n";
                int j = 0;
                for (const auto &pos : liste_pos){
                    cout << j << ". (" << pos.getX() << "," << pos.getY()<< ")";
                    j++;
                }
                cout<<endl;
                int choix2 = -1;
                while (choix2 <0 || choix2>liste_pos.size()) {
                    cout << "Ou souhaitez vous placer votre piece ? \n";
                    cin>>choix2;
                    if (cin.fail()) { // Gestion input invalide
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Retire input invalide du buffer
                        cout << "\nValeur invalide, reessayez\n";
                        continue; // Re effectue la boucle
                    }
                }
                tour_fini = historique_etats[0].joueur_courant->jouerCoupCreer(reserve[choix1], liste_pos[choix2], historique_etats[0].plateau);
                break;
            }
            case 2: { //Deplacement d'une piece du plateau
                if ((historique_etats[0].getNumTour() == 1 || historique_etats[0].getNumTour() == 2)) {
                    cout<<"Vous ne pouvez pas faire cette action durant votre premier tour !"<<endl;
                    break;
                }
                if (liste_coups.size() == 0) {
                    cout<<"Vous n'avez pas de coups à jouer. \n";
                    break;
                }
                cout << "Voici vos coups possibles : \n";
                int j = 0;
                for (const auto &coup : liste_coups){
                    cout << j << ". " << coup.getPiece()->getType() << " - a (" << coup.getPosInitial().getX() << " , " << coup.getPosInitial().getY() << ") vers (" << coup.getPosFinal().getX() << " , " << coup.getPosFinal().getY() << ") \n";
                    j++;
                }
                int choix = -1;
                while (choix <0 || choix>liste_coups.size()) {
                    cout << "Quelle possibilite souhaitez-vous jouer ? \n";
                    cin >> choix;
                }
                Mouvement coupChoisi = liste_coups.at(choix);
                if (coupChoisi.getPiece() != nullptr) {
                    tour_fini = historique_etats[0].joueur_courant->jouerCoupDeplacer(coupChoisi.getPiece(), coupChoisi.getPosFinal(), historique_etats[0].plateau);
                } else {
                    cout << "Erreur: La pièce sélectionnée est vide." << endl;
                }
                break;
            }
            case 3: {
                if ((historique_etats[0].getNumTour() == 1 || historique_etats[0].getNumTour() == 2)) {
                    cout<<"Vous ne pouvez pas faire cette action durant votre premier tour !"<<endl;
                    break;
                }
                //vérifier si le tour actuel est supérieur à 2 (chaque joueur a déjà joué au moins une fois)
                if(historique_etats[0].numero_tour > 2){
                    //vérifier si il reste des retours en arriere pour cette partie
                    if(nb_retour_arriere > 0){
                        annulerDernierMouvement();
                        cout<<"Voici le nouvel etat du plateau : \n";
                        historique_etats[0].plateau.afficher(historique_etats[0].joueur_courant->getCamp(), historique_etats[0].joueur_courant->getNom(), historique_etats[0].getAutreJoueur()->getNom());
                    }
                    else {
                        cout<<"Il n'y a pas ou plus de retour en arriere possible pour cette partie ! \n";
                    }
                }
                else{
                    cout<<"Il faut qu'au moins chaque joueur ait joue un tour pour revenir en arriere ! \n";
                }
                break;
            }
            default:
                cout<<"Valeur invalide, reessayez\n";
        }
    }
}

bool Partie::finPartie()const{
    //Si l'abeille est entouree
    for(const auto joueur : historique_etats[0].joueurs){
        for(const auto piece : joueur->getPieces()){
            if(piece->getType() == 1 && !historique_etats[0].plateau.inReserve(piece)){
                const Coords* c = historique_etats[0].plateau.coordsPiece(*piece);
                if (c != nullptr) {
                    if(historique_etats[0].plateau.getGraphe().isSurrounded(*c)) {
                        return true;
                    }
                }
            }
        }
    }
    //Si les deux joueurs n'ont plus de coups possibles et de pièce en réserve
    if(historique_etats[0].reserveJoueur(historique_etats[0].joueurs[0]).empty() && historique_etats[0].reserveJoueur(historique_etats[0].joueurs[0]).empty()) {
        if(historique_etats[0].coupsPossibles(historique_etats[0].joueurs[0]).empty() && historique_etats[0].coupsPossibles(historique_etats[0].joueurs[0]).empty()) {
            return true;
        }
    }
    return false;
}

void Partie::lancerPartie() {
    commencerPartie();

    // Si aucune condition d'arret de partie n'est verifiee, on joue le tour et passe au joueur suivant
    while(!finPartie()){
        jouerTour();
        cout<<"Fin du tour"<<endl<<endl;
        if(historique_etats[0].joueur_courant == historique_etats[0].joueurs[0]){
            historique_etats[0].joueur_courant = historique_etats[0].joueurs[1];
        }else{
            historique_etats[0].joueur_courant = historique_etats[0].joueurs[0];
        }
    }

    cout<< "Plateau en fin de partie : "<<endl;
    historique_etats[0].plateau.afficher(historique_etats[0].getJoueurCourant()->getCamp(), historique_etats[0].getJoueurCourant()->getNom(), historique_etats[0].getAutreJoueur()->getNom());

    cout << "Fin de la partie : " << endl; //On est sorti de la boucle while : une condition d'arret est verifiee

    //On cherche a determiner quelle condition d'arret de la partie a ete remplie
    //Cas 1 : les joueurs n'ont plus de coup possible et plus de piece en reserve : egalite
    if(historique_etats[0].coupsPossibles(historique_etats[0].joueurs[0]).empty() && historique_etats[0].coupsPossibles(historique_etats[0].joueurs[0]).empty()) {
        if(historique_etats[0].reserveJoueur(historique_etats[0].joueurs[0]).empty() && historique_etats[0].reserveJoueur(historique_etats[0].joueurs[0]).empty()){
            cout<<"Egalite !"<<endl;
        }
    }
    //Cas 2 : une abeille est entouree
    for(const auto joueur : historique_etats[0].joueurs){
        for(const auto piece : joueur->getPieces()){
            if(piece->getType() == 1){
                const Coords* c = historique_etats[0].plateau.coordsPiece(*piece);
                if (c != nullptr) {
                    if(historique_etats[0].plateau.getGraphe().isSurrounded(*c)){
                        if(joueur == historique_etats[0].joueurs[0]){
                            cout<<"Le joueur "<<historique_etats[0].joueurs[1]->getNom()<<" a gagne !"<<endl;
                        }
                        if(joueur == historique_etats[0].joueurs[1]){
                            cout<<"Le joueur "<<historique_etats[0].joueurs[0]->getNom()<<" a gagne !"<<endl;
                        }
                    }
                }
            }
        }
    }
    cout<<"Merci d'avoir joue a Hive !"<<endl;
}

void GameManager::afficher_menu() {
    //Est appelée en début d'execution pour lancer la boucle de gameplay
    //sert à gérer le switch
    int choice =0;
    while (choice != 2) {

        cout<<"\n\n ----------------------------------\n\n"<<"Bienvenue dans Hive, le jeu iconique, enfin sous forme virtuelle !\n"
                                                             "Que souhaitez vous faire ?\n"
                                                             " 1. Lancer une nouvelle partie\n "
                                                             "2. Quitter le jeu\n "
                                                             "Votre choix :";
        cin >> choice;
        // Gestion input invalide
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Retire input invalide du buffer
            cout << "\nValeur invalide, reessayez\n";
            continue; // Re effectue la boucle
        }
        switch (choice) {
            case 1:
                cout << "\n Vous avez lance une nouvelle partie\n";
                partie_active.lancerPartie();
                break;
            case 2:
                cout << "\n Au revoir ! \n";
                break;
            default:
                cout<<"\nValeur invalide, reessayez\n";
        }
        }
}