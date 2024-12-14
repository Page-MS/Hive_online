//
// Created by page on 28/11/2024.
//

#ifndef LO21_GAMEMANAGER_H
#define LO21_GAMEMANAGER_H
#include "partie.hpp"

class GameManager{
    //Partie partie_active;
    MementoPartie** sauvegardes;
    static GameManager* instance;
public:
    void afficher_menu();

};
#endif //LO21_GAMEMANAGER_H
