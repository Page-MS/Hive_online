//
// Created by page on 28/11/2024.
//

#include "gamemanager.h"
void GameManager::afficher_menu() {
    ///Est appelée en début d'execution pour lancer la boucle de gameplay
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

