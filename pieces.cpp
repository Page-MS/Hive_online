//
// Created by page on 06/11/2024.
//

#include "pieces.h"
Piece* Piece::createPiece(int choice) {
    //we should be careful with using this going forward as the delete must be done in the function that create the Piece
    if (choice == 1) {
        return new Abeille();
    } else if (choice == 2) {
        return new Fourmi();
    }
    else if (choice == 3) {
        return new Scarabee();
    }
    else if (choice == 4) {
        return new Sauterelle();
    }
    else if (choice == 5) {
        return new Araignee();
    }
    else if (choice == 6) {
        return new Moustique();
    }
    else if (choice == 7) {
        return new Coccinelle();
    }
    else {
        std::cout<<"Attention choix de piece invalide";
        return nullptr;  }

}
int** Abeille::coupsPossibles() {
    // Placeholder
    return nullptr;
}

int** Fourmi::coupsPossibles() {
    // Placeholder
    return nullptr;
}

int** Scarabee::coupsPossibles() {
    // Placeholder
    return nullptr;
}

int** Moustique::coupsPossibles() {
    // Placeholder
    return nullptr;
}

int** Araignee::coupsPossibles() {
    // Placeholder
    return nullptr;
}

int** Sauterelle::coupsPossibles() {
    // Placeholder
    return nullptr;
}

int** Coccinelle::coupsPossibles() {
    // Placeholder
    return nullptr;
}