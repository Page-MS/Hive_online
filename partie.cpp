#include "partie.hpp"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>

GameManager* GameManager::instance = nullptr;

GameManager& GameManager::getInstance() {
    if (instance==nullptr) {
        instance = new GameManager;
    }
    return *instance;
}



EtatDuJeu::EtatDuJeu(int num_tour, Plateau p,  Joueur* j1, Joueur* j2, Joueur* jc){
    numero_tour = num_tour;
    plateau = p;
    joueurs.at(0) = j1;
    joueurs.at(1) = j2;
    joueur_courant = nullptr;
    if(jc == j1) {
        joueur_courant = joueurs.at(0);
    }else if(jc == j2) {
        joueur_courant = joueurs.at(1);
    }
}

EtatDuJeu::~EtatDuJeu() {
    //Destruction des joueurs
    for (auto joueur : joueurs) {
        if(joueur) {
            delete joueur;
            joueur= nullptr;
        }
    }
    joueur_courant = nullptr;
}

EtatDuJeu::EtatDuJeu(){
    numero_tour = 0;
    plateau = Plateau();
    joueurs.push_back(nullptr);
    joueurs.push_back(nullptr);
    joueur_courant = nullptr;
}

EtatDuJeu::EtatDuJeu(const EtatDuJeu& other){
    numero_tour = other.numero_tour;
    plateau = other.plateau;

    for (auto joueur:other.joueurs) {
        joueurs.push_back(new Joueur(*joueur));
    }

    if(other.joueur_courant == other.joueurs.at(0))
        joueur_courant = joueurs.at(0);
    else if(other.joueur_courant == other.joueurs.at(1))
        joueur_courant = joueurs.at(1);
    else joueur_courant = nullptr;

}


EtatDuJeu& EtatDuJeu::operator=(const EtatDuJeu& jeu){
    if(this != &jeu){
        numero_tour = jeu.numero_tour;
        plateau = jeu.plateau;


        for (auto joueur:joueurs) {
            delete joueur;
        }
        for (auto joueur:jeu.joueurs) {
        joueurs.push_back(new Joueur(*joueur));
        }

        if(jeu.joueur_courant == jeu.joueurs.at(0))
            joueur_courant = joueurs.at(0);
        else if(jeu.joueur_courant == jeu.joueurs.at(1))
            joueur_courant = joueurs.at(1);
        else joueur_courant = nullptr;

        historique = jeu.historique;
        joueur_courant = jeu.joueur_courant;
        plateau.piecesCoherence(joueurs.at(0)->getPieces(), joueurs.at(1)->getPieces());
    }
    return *this;
}

Joueur* EtatDuJeu::getAutreJoueur() const {
    if (joueurs.at(0)==joueur_courant) return joueurs.at(1);
    return joueurs.at(0);
}

const vector<Mouvement> EtatDuJeu::coupsPossibles(Joueur* j) const {
    if (j!=joueurs.at(0) && j!=joueurs.at(1)) throw runtime_error("ERROR EtatDuJeu::coupsPossibles : Joueur pas dans etat du jeu.");

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


Partie::Partie() : start_joueur_id(0) {
    EtatDuJeu* etat = new EtatDuJeu();
    historique.push_back(etat);
}

Partie::~Partie() {
    for (auto i:historique)
        delete i;
}

//Méthode qui détermine qui commence la partie
void Partie::setStartJoueurId(){
    srand(static_cast<int>(time(0)));
   start_joueur_id = rand() % 2;
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

    Joueur* j1;
    Joueur* j2;

    // création des joueurs selon si IA ou non
    if (ia1) {
        j1 = new IAJoueur(pseudo1, true);
    }
    else  {
        j1 = new Joueur(pseudo1, true);
    }
    if (ia2) {
        j2 = new IAJoueur(pseudo2, false);
    }
    else  {
        j2 = new Joueur(pseudo2, false);
    }

    getEtatActuel().joueurs.at(0)=j1;
    getEtatActuel().joueurs.at(1)=j2;

    getEtatActuel().numero_tour = 0;

    //On determine qui commence la partie
    setStartJoueurId();
    getEtatActuel().joueur_courant = getEtatActuel().joueurs.at(start_joueur_id);

    for (Joueur *joueur: getEtatActuel().joueurs) {
        getEtatActuel().plateau.fillReserve(joueur->getPieces());
    }

    cout << "Debut de la partie" << endl;
}

const vector<const Piece*> EtatDuJeu::reserveJoueur(Joueur* j) const{
    return plateau.piecesReserve(j->getCamp());
}

void Partie::annulerDernierMouvement(){ //On remonte au tour précédent de chacun des joueurs
    if (historique.size()<4) throw runtime_error("ERROR EtatDuJeu::reserveJoueur : Pas assez d'etats sauvegardes.");

    // suppression du tour actuel
    delete historique.at(historique.size()-1);
    historique.pop_back();
    // suppression du tour du joueur adverse
    delete historique.at(historique.size()-1);
    historique.pop_back();
    // suppression du dernier tour du joueur courant
    delete historique.at(historique.size()-1);
    historique.pop_back();

    getEtatActuel().afficher();

}

void Partie::jouerTour(){

    //Initialisation du tour
    bool tour_fini = false;
    EtatDuJeu* etat = new EtatDuJeu(getEtatActuel());
    etat->plateau.piecesCoherence(etat->joueurs.at(0)->getPieces(), etat->joueurs.at(1)->getPieces());
    etat->numero_tour++;

    historique.push_back(etat);

    //Affichage du jeu
    cout << "Tour " << getEtatActuel().numero_tour << endl;

    cout <<"Etat actuel du plateau : " << endl;
    getEtatActuel().afficher();

    cout << "C'est au joueur " << getEtatActuel().joueur_courant->getNom() << " de jouer." << endl;

    //Si il n'y a plus de piece en reserve, ni de coups possible : on passe le tour
    vector <const Piece*> reserve = getEtatActuel().reserveJoueur(getEtatActuel().joueur_courant);

    vector<Mouvement> liste_coups = getEtatActuel().coupsPossibles( (getEtatActuel().getJoueurCourant()));

    for (auto it = liste_coups.begin(); it != liste_coups.end(); ) {
        if (getEtatActuel().plateau.getGraphe().wouldHiveBreak(it->getPosInitial())) {
            it = liste_coups.erase(it);
        } else {
            ++it;
        }
    }

    if(reserve.size() == 0 && liste_coups.size() == 0){
        cout<<"Vous n'avez pas de possibilite de jouer ce tour !"<<endl;
        return;
    }
    vector<Coords> liste_pos = getEtatActuel().plateau.getGraphe().placableCoords(getEtatActuel().joueur_courant->getCamp());

    //Actions si une IA joue le prochain tour
    if (getEtatActuel().joueur_courant->getIsIA()) {
        if (reserve.empty()) { //Si il ne reste plus de piece en reserve, on en deplace une aleatoirement
            const int coups = rand()%liste_coups.size() +1;//Choix aleatoire d'un deplacement de piece a effectuer
            getEtatActuel().joueur_courant->jouerCoupDeplacer(liste_coups.at(coups).getPiece(), liste_coups.at(coups).getPosFinal(), getEtatActuel().plateau);
        }
        else { //Si il reste des pieces en reserve, on en ajoute une aleatoirement
            srand(static_cast<int>(time(0)));
            if (getEtatActuel().numero_tour == 7 || getEtatActuel().numero_tour == 8) { //Si l'abeille n'a pas ete posee au 4eme tour de l'IA
                for (const auto* piece : reserve) {
                    if (piece->getType() == Abeille) {
                        if (liste_pos.empty()) {
                            cout << "Erreur : L'IA ne peut pas poser l'Abeille, mais cela est obligatoire.\n";
                            return;
                        }
                        const int pos = rand()%liste_pos.size(); //Choix aleatoire d'une position pour l'abeille
                        getEtatActuel().joueur_courant->jouerCoupCreer(piece, liste_pos.at(pos), getEtatActuel().plateau);
                    }
                }
            }
            else {
                const int piece = rand()%reserve.size(); //Choix aleatoire d'une piece de la reserve a ajouter
                const int pos = rand()%liste_pos.size();//Choix aleatoire d'une position pour la piece
                getEtatActuel().joueur_courant->jouerCoupCreer(reserve.at(piece), liste_pos.at(pos), getEtatActuel().plateau);
            }
        }
        return;
    }

    //Si l'abeille n'a pas ete posee au 4eme tour du joueur
    if (getEtatActuel().numero_tour == 7 || getEtatActuel().numero_tour == 8) {
        for (const auto *piece : getEtatActuel().reserveJoueur(getEtatActuel().joueur_courant)) {
            if (piece->getType() == Abeille) {
                cout << "Vous devez poser l'Abeille dans ce tour : aucune autre action permise."<<endl;
                if (liste_pos.empty()) {
                    cout << "Erreur : Impossible de poser l'Abeille, mais cela est obligatoire.\n";
                    return;
                }
                cout << "Voici vos placements possibles : \n";
                int j = 0;
                for (const auto &pos : liste_pos){
                    cout << j << ". "<<pos<<endl;
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
                tour_fini = getEtatActuel().joueur_courant->jouerCoupCreer(piece, liste_pos.at(choix), getEtatActuel().plateau);
                return;
            }
        }
    }

    //Si l'abeille n'a toujours pas été posée au 4eme tour du joueur
    if (getEtatActuel().numero_tour == 7 || getEtatActuel().numero_tour == 8) {
        for (const auto *piece : getEtatActuel().reserveJoueur(getEtatActuel().joueur_courant)) {
            if (piece->getType() == Abeille) {
                cout << "Vous devez poser l'Abeille dans ce tour : aucune autre action permise."<<endl;
                cout << "Voici vos placements possibles : \n";
                int j = 0;
                for (const auto &pos : liste_pos){
                    cout << j << ". "<<pos<<endl;
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
                tour_fini = getEtatActuel().joueur_courant->jouerCoupCreer(piece, liste_pos.at(choix), getEtatActuel().plateau);
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
        cout<< "3 - Annuler le coup precedent " << endl;
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
                tour_fini = getEtatActuel().joueur_courant->jouerCoupCreer(reserve.at(choix1), liste_pos.at(choix2), getEtatActuel().plateau);
                break;
                }
            case 2: { //Deplacement d'une piece du plateau
                if ((getEtatActuel().getNumTour() == 1 || getEtatActuel().getNumTour() == 2)) {
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
                    cout << j << ". " << coup.getPiece()->strPiece() << " - de (" << coup.getPosInitial().getX() << " , " << coup.getPosInitial().getY() << ") vers (" << coup.getPosFinal().getX() << " , " << coup.getPosFinal().getY() << ") \n";
                    j++;
                }
                int choix = -1;
                while (choix <0 || choix>liste_coups.size()) {
                    cout << "Quelle possibilite souhaitez-vous jouer ? \n";
                    cin >> choix;
                }
                Mouvement coupChoisi = liste_coups.at(choix);
                if (coupChoisi.getPiece() != nullptr) {
                    tour_fini = getEtatActuel().joueur_courant->jouerCoupDeplacer(coupChoisi.getPiece(), coupChoisi.getPosFinal(), getEtatActuel().plateau);
                } else {
                    cout << "Erreur: La pièce sélectionnée est vide." << endl;
                }
                break;
                }
            case 3: {
                //vérifier si le tour actuel est supérieur à 2 (chaque joueur a déjà joué au moins une fois)
                if ((getEtatActuel().getNumTour() <= 2)) {
                    cout<<"Vous ne pouvez pas faire cette action durant votre premier tour !"<<endl;
                }
                //annuler si suffisamment d'états sauvegardés en réserve
                else if(historique.size() >= 4){
                    annulerDernierMouvement();
                    cout<<"Voici le nouvel etat du plateau : \n";
                    getEtatActuel().afficher();
                    tour_fini = true;

                }
                else {
                    cout<<"Il n'y a pas ou plus de retour en arriere possible pour cette partie ! \n";
                }
                break;
            }
            default:
                cout<<"Valeur invalide, reessayez\n";
        }
    }
}

bool Partie::finPartie() {
    //Si l'abeille est entouree

    for(const auto joueur : getEtatActuel().joueurs){
        for(const auto piece : joueur->getPieces()){
            if(piece->getType() == 1 && !getEtatActuel().plateau.inReserve(piece)){
                const Coords* c = getEtatActuel().plateau.coordsPiece(*piece);
                if (c != nullptr) {
                    if(getEtatActuel().plateau.getGraphe().isSurrounded(*c)) {
                        return true;
                    }
                }
            }
        }
    }
    //Si les deux joueurs n'ont plus de coups possibles et de pièce en réserve
    if(getEtatActuel().reserveJoueur(getEtatActuel().joueurs.at(0)).empty()
        && getEtatActuel().reserveJoueur(getEtatActuel().joueurs.at(0)).empty()
        && getEtatActuel().coupsPossibles(getEtatActuel().joueurs.at(1)).empty()
        && getEtatActuel().coupsPossibles(getEtatActuel().joueurs.at(1)).empty()) {
        return true;
    }
    return false;
}

void Partie::lancerPartie() {
    commencerPartie();

    // Si aucune condition d'arret de partie n'est verifiee, on joue le tour et passe au joueur suivant
    while(!finPartie()){
        jouerTour();
        cout<<"Fin du tour"<<endl<<endl;
        if(getEtatActuel().joueur_courant == getEtatActuel().joueurs.at(0)){
            getEtatActuel().joueur_courant = getEtatActuel().joueurs.at(1);
        }else{
            getEtatActuel().joueur_courant = getEtatActuel().joueurs.at(0);
        }
    }

    cout<< "Plateau en fin de partie :"<<endl;
    getEtatActuel().afficher();

    cout << "Fin de la partie :" << endl; //On est sorti de la boucle while : une condition d'arret est verifiee

    //On cherche a determiner quelle condition d'arret de la partie a ete remplie
    //Cas 1 : les joueurs n'ont plus de coup possible et plus de piece en reserve : egalite
    if(getEtatActuel().coupsPossibles(getEtatActuel().joueurs.at(0)).empty() && getEtatActuel().coupsPossibles(getEtatActuel().joueurs.at(0)).empty()) {
        if(getEtatActuel().reserveJoueur(getEtatActuel().joueurs.at(0)).empty() && getEtatActuel().reserveJoueur(getEtatActuel().joueurs.at(0)).empty()){
            cout<<"Egalite !"<<endl;
        }
    }
    //Cas 2 : une abeille est entouree
    for(const auto joueur : getEtatActuel().joueurs){
        for(const auto piece : joueur->getPieces()){
            if(piece->getType() == 1){
                const Coords* c = getEtatActuel().plateau.coordsPiece(*piece);
                if (c != nullptr) {
                    if(getEtatActuel().plateau.getGraphe().isSurrounded(*c)){
                        if(joueur == getEtatActuel().joueurs.at(0)){
                            cout<<"Le joueur "<<getEtatActuel().joueurs.at(1)->getNom()<<" a gagne !"<<endl;
                        }
                        if(joueur == getEtatActuel().joueurs.at(1)){
                            cout<<"Le joueur "<<getEtatActuel().joueurs.at(0)->getNom()<<" a gagne !"<<endl;
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