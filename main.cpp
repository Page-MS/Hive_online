
#include "pieces.cpp"
#include "plateau.cpp"
#include "cases.cpp"
#include "coords.cpp"
//#include <windows.h>
//#include "Joueur.cpp"
//#include "partie.cpp"
#include "legalmoves.cpp"
//#include "gamemanager.cpp"


int main() {
    std::cout << "          _____                    _____                    _____                    _____          \n"
                 "         /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\         \n"
                 "        /::\\____\\                /::\\    \\                /::\\____\\                /::\\    \\        \n"
                 "       /:::/    /                \\:::\\    \\              /:::/    /               /::::\\    \\       \n"
                 "      /:::/    /                  \\:::\\    \\            /:::/    /               /::::::\\    \\      \n"
                 "     /:::/    /                    \\:::\\    \\          /:::/    /               /:::/\\:::\\    \\     \n"
                 "    /:::/____/                      \\:::\\    \\        /:::/____/               /:::/__\\:::\\    \\    \n"
                 "   /::::\\    \\                      /::::\\    \\       |::|    |               /::::\\   \\:::\\    \\   \n"
                 "  /::::::\\    \\   _____    ____    /::::::\\    \\      |::|    |     _____    /::::::\\   \\:::\\    \\  \n"
                 " /:::/\\:::\\    \\ /\\    \\  /\\   \\  /:::/\\:::\\    \\     |::|    |    /\\    \\  /:::/\\:::\\   \\:::\\    \\ \n"
                 "/:::/  \\:::\\    /::\\____\\/::\\   \\/:::/  \\:::\\____\\    |::|    |   /::\\____\\/:::/__\\:::\\   \\:::\\____\\\n"
                 "\\::/    \\:::\\  /:::/    /\\:::\\  /:::/    \\::/    /    |::|    |  /:::/    /\\:::\\   \\:::\\   \\::/    /\n"
                 " \\/____/ \\:::\\/:::/    /  \\:::\\/:::/    / \\/____/     |::|    | /:::/    /  \\:::\\   \\:::\\   \\/____/ \n"
                 "          \\::::::/    /    \\::::::/    /              |::|____|/:::/    /    \\:::\\   \\:::\\    \\     \n"
                 "           \\::::/    /      \\::::/____/               |:::::::::::/    /      \\:::\\   \\:::\\____\\    \n"
                 "           /:::/    /        \\:::\\    \\               \\::::::::::/____/        \\:::\\   \\::/    /    \n"
                 "          /:::/    /          \\:::\\    \\               ~~~~~~~~~~               \\:::\\   \\/____/     \n"
                 "         /:::/    /            \\:::\\    \\                                        \\:::\\    \\         \n"
                 "        /:::/    /              \\:::\\____\\                                        \\:::\\____\\        \n"
                 "        \\::/    /                \\::/    /                                         \\::/    /        \n"
                 "         \\/____/                  \\/____/                                           \\/____/         \n"
                 "                                                                                                    " << std::endl;

    cout<<"\n\n"<<"|)     /|  .      |  |. _ |-|- _     /|  .      ,_ |  |)     _ \n"
                  "|)\\/  /-||`|(|,  _|L|||(/_|_|_(/_,  /-||`|(|  (|||(|  | (|(|(/_\n"
                  "  /                                                       _|   ";
    //GameManager game_manager;
    //game_manager.afficher_menu();

    try {
    Plateau plateau;

    Piece abeille(TYPE_PIECE::Abeille, false);
    Piece fourmi(TYPE_PIECE::Fourmi, false);
    Piece scarabee(TYPE_PIECE::Scarabee, false);
    Piece sauterelle(TYPE_PIECE::Sauterelle, false);
    Piece coccinelle(TYPE_PIECE::Coccinelle, true);
    Piece moustique(TYPE_PIECE::Moustique, true);
    Piece araignee(TYPE_PIECE::Araignee, true);
    plateau.addPieceReserve(abeille);
    plateau.addPieceReserve(fourmi);
    plateau.addPieceReserve(scarabee);
    plateau.addPieceReserve(sauterelle);
    plateau.addPieceReserve(coccinelle);
    plateau.addPieceReserve(moustique);
    plateau.addPieceReserve(araignee);

    cout<<"---- ADD PIECE ----\n";
    plateau.movePiece(abeille, Coords(0, 0));
    plateau.movePiece(fourmi, Coords(0, 2));


    cout<<"\n---- AFFICHAGE ----\n";
    plateau.afficher(true);

    cout<<"---- MOVE PIECE FOURMI TO (0, 0) ----\n";
    plateau.movePiece(fourmi, Coords(0, 0));
    cout<<"\n---- AFFICHAGE ----\n";
    plateau.afficher(true);

    cout<<"---- MOVE PIECE FOURMI TO (1, 1) ----\n";
    plateau.movePiece(fourmi, Coords(1, 1));

    cout<<"\n---- AFFICHAGE ----\n";
    plateau.afficher(true);

    cout<<"---- CAGE QUEEN ----\n";
    //plateau.movePiece(scarabee, Coords(0, 2));
    plateau.movePiece(sauterelle, Coords(0, -2));
    //plateau.movePiece(araignee, Coords(1, -1));
    plateau.movePiece(moustique, Coords(-1, 1));
    plateau.movePiece(coccinelle, Coords(-1, -1));

    cout<<"\n---- AFFICHAGE ----\n";
    Piece abeille2(TYPE_PIECE::Abeille, true);
    Piece fourmi2(TYPE_PIECE::Fourmi, true);
    Piece scarabee2(TYPE_PIECE::Scarabee, true);
    Piece sauterelle2(TYPE_PIECE::Sauterelle, true);
    Piece coccinelle2(TYPE_PIECE::Coccinelle, false);
    Piece moustique2(TYPE_PIECE::Moustique, false);
    Piece araignee2(TYPE_PIECE::Araignee, false);
    Piece araignee3(TYPE_PIECE::Araignee, false);
    plateau.addPieceReserve(abeille2);
    plateau.addPieceReserve(fourmi2);
    plateau.addPieceReserve(scarabee2);
    plateau.addPieceReserve(sauterelle2);
    plateau.addPieceReserve(coccinelle2);
    plateau.addPieceReserve(moustique2);
    plateau.addPieceReserve(araignee2);
    plateau.addPieceReserve(araignee3);
    plateau.afficher(true);

    plateau.movePiece(abeille2, Coords(-2, 0));
    plateau.movePiece(araignee2, Coords(0, 2));
    plateau.movePiece(abeille2, Coords(0, 4));
    plateau.movePiece(scarabee2, Coords(0, 6));
    plateau.movePiece(araignee3, Coords(2, 2));
    plateau.movePiece(fourmi2, Coords(2, 4));

    plateau.afficher(true);

    cout<<"Cases habitees = "<<plateau.getGraphe().getNbInhabitedCases()<<endl;
    cout<<"Ruche brisee si bouge a "<<Coords(0, 2)<<" : "<<plateau.getGraphe().wouldHiveBreak(Coords(0, 2))<<endl;

    Graphe g2= plateau.getGraphe();


    cout<<g2<<endl;

    /*cout<<"\n########Test de la reine abeille########\n\n";
    cout<<g2.hasCase(0,0)<<endl;
    if (not g2.getCase(0,0).empty()) {
        cout << "Type de la piece :" << g2.getCase(0, 6).getUpperPiece().getType() << endl;
        vector<Coords> coups_test = g2.getCase(0, 6).getUpperPiece().coupsPossibles(plateau.getGraphe(),
                                                                                   plateau.getGraphe().getCase(0,
                                                                                                               6).getCoords());
        if (not coups_test.empty()) {
            cout << "\nPremieres coordonnees retournees : " << coups_test[0].getX() << ":" << coups_test[0].getY();
        }
    }
    cout<<"\n########Test du scarabee 1########\n\n";

    cout<<g2.hasCase(0,6)<<endl;
    if (not g2.getCase(0,6).empty()) {
        cout << "Type de la piece :" << g2.getCase(0, 6).getUpperPiece().getType() << endl;
        vector<Coords> coups_test = g2.getCase(0, 6).getUpperPiece().coupsPossibles(plateau.getGraphe(),
                                                                                   plateau.getGraphe().getCase(0,6).getCoords());
        if (not coups_test.empty()) {
            cout << "\nPremieres coordonnees retournees : " << coups_test[0].getX() << ":" << coups_test[0].getY();
        }
    }

        cout<<"\n########Test du scarabee 2########\n\n";
        cout<<g2.hasCase(0,8)<<endl;
        if (not g2.getCase(0,8).empty()) {
            cout << "Type de la piece :" << g2.getCase(0, 8).getUpperPiece().getType() << endl;
            vector<Coords> coups_test = g2.getCase(0, 8).getUpperPiece().coupsPossibles(plateau.getGraphe(),
                                                                                       plateau.getGraphe().getCase(0,8).getCoords());
            if (not coups_test.empty()) {
                cout << "\nPremieres coordonnees retournees : " << coups_test[0].getX() << ":" << coups_test[0].getY();
            }
        }

        cout<<"\n######## Test de l'araignee ########\n\n";
        cout<<g2.hasCase(2,2)<<endl;
        if (not g2.getCase(2,2).empty()) {
            cout << "Type de la piece :" << g2.getCase(2, 2).getUpperPiece().getType() << endl;
            vector<Coords> coups_test = g2.getCase(2, 2).getUpperPiece().coupsPossibles(plateau.getGraphe(),
                                                                                       plateau.getGraphe().getCase(2,2).getCoords());
            if (not coups_test.empty()) {
                for(auto i:coups_test)
                cout << "\nCoordonnees retournees : " << i.getX() << ":" << i.getY();
            }
        }*/

        cout<<"\n######## Test de la fourmi ########\n\n";
        cout<<g2.hasCase(2,4)<<endl;
        if (not g2.getCase(2,4).empty()) {
            cout << "Type de la piece :" << g2.getCase(2, 4).getUpperPiece().getType() << endl;
            vector<Coords> coups_test = g2.getCase(2, 4).getUpperPiece().coupsPossibles(plateau.getGraphe(),
                                                                                        plateau.getGraphe().getCase(2,4).getCoords());
            if (not coups_test.empty()) {
                for(auto i:coups_test)
                    cout << "\nCoordonnees retournees : " << i.getX() << ":" << i.getY();
            }
        }


    }

    catch (const exception& e) {
        cout<<e.what()<<endl;
    }

    cout<<"\n\nTout nickel !"<<endl;
    return 0;
}
