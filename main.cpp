
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
    Graphe& g = plateau.getMutableGraphe();

    Piece abeille(TYPE_PIECE::Abeille, false);
    Piece fourmi(TYPE_PIECE::Fourmi, false);
    Piece scarabee(TYPE_PIECE::Scarabee, false);
    Piece sauterelle(TYPE_PIECE::Sauterelle, false);
    Piece coccinelle(TYPE_PIECE::Coccinelle, true);
    Piece moustique(TYPE_PIECE::Moustique, true);
    Piece araignee(TYPE_PIECE::Araignee, true);

    cout<<abeille.strPiece()<<endl;

    cout<<"---- ADD PIECE ----\n";
    g.addPiece(abeille, Coords(0, 0));
    g.addPiece(fourmi, Coords(0, 2));


    cout<<"\n---- AFFICHAGE ----\n";
    cout<<g<<endl;

    cout<<"---- DELETE THEN ADD Fourmi ----"<<endl;
    g.supprPiece(Coords(0, 2));
    g.addPiece(fourmi, Coords(0, 2));

    cout<<"\n---- AFFICHAGE ----\n";
    cout<<g<<endl;

    cout<<"---- MOVE PIECE FOURMI TO (0, 0) ----\n";
    g.movePiece(fourmi, Coords(0, 0));
    cout<<"\n---- AFFICHAGE ----\n";
    cout<<g<<endl;

    cout<<"---- MOVE PIECE FOURMI TO (1, 1) ----\n";
    g.movePiece(fourmi, Coords(1, 1));

    cout<<"\n---- AFFICHAGE ----\n";
    cout<<g<<endl;

    cout<<"---- CAGE QUEEN ----\n";
    g.addPiece(scarabee, Coords(0, 2));
    g.addPiece(sauterelle, Coords(0, -2));
    g.addPiece(araignee, Coords(1, -1));
    g.addPiece(moustique, Coords(-1, 1));
    g.addPiece(coccinelle, Coords(-1, -1));

    cout<<"\n---- AFFICHAGE ----\n";
    Piece abeille2(TYPE_PIECE::Abeille, true);
    Piece fourmi2(TYPE_PIECE::Fourmi, true);
    Piece scarabee2(TYPE_PIECE::Scarabee, true);
    Piece sauterelle2(TYPE_PIECE::Sauterelle, false);
    Piece coccinelle2(TYPE_PIECE::Coccinelle, false);
    Piece moustique2(TYPE_PIECE::Moustique, false);
    Piece araignee2(TYPE_PIECE::Araignee, false);
    plateau.addPieceReserve(abeille2);
    plateau.addPieceReserve(fourmi2);
    plateau.addPieceReserve(scarabee2);
    plateau.addPieceReserve(sauterelle2);
    plateau.addPieceReserve(coccinelle2);
    plateau.addPieceReserve(moustique2);
    plateau.addPieceReserve(araignee2);
    plateau.movePiece(araignee2, Coords(0, 4));
    plateau.movePiece(abeille2, Coords(0, 6));


    plateau.afficher(true);



    cout<<"Cases habitees = "<<g.getNbInhabitedCases()<<endl;
    cout<<"Ruche brisee si bouge a "<<Coords(0, 2)<<" : "<<g.wouldHiveBreak(Coords(0, 2))<<endl;

    Graphe g2= g;

    cout<<g<<endl;
    cout<<g2<<endl;
    cout<<g.hasCase(0,0)<<endl;
    if (not g.getCase(0,0).empty()){
        cout<<"Type de la piece :"<<g.getCase(0,6).getUpperPiece().getType()<<endl;
        vector<Coords> coups_test=g.getCase(0,6).getUpperPiece().coupsPossibles(plateau.getGraphe(),plateau.getGraphe().getCase(0,6).getCoords());
        cout<<"\nCoordonnees retournees : "<<coups_test[0].getX()<<":"<<coups_test[0].getY();   }
    } catch (const exception& e) {
        cout<<e.what()<<endl;
    }

    cout<<"\n\nTout nickel !"<<endl;

    return 0;
}
