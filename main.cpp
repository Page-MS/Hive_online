
#include "pieces.cpp"
#include "plateau.cpp"
#include "cases.cpp"
#include "coords.cpp"
//#include <windows.h>
//#include "Joueur.cpp"
//#include "partie.cpp"
//#include "legalmoves.cpp"
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
    cout<<"\n\n"<<" ______     __   __        __  __     ______     __  __     ______        ______     ______     __    __     ______   __  __     ______   ______     ______    \n"
                  "/\\  __ \\   /\\ \"-.\\ \\      /\\ \\_\\ \\   /\\  __ \\   /\\ \\/\\ \\   /\\  == \\      /\\  ___\\   /\\  __ \\   /\\ \"-./  \\   /\\  == \\ /\\ \\/\\ \\   /\\__  _\\ /\\  ___\\   /\\  == \\   \n"
                  "\\ \\ \\/\\ \\  \\ \\ \\-.  \\     \\ \\____ \\  \\ \\ \\/\\ \\  \\ \\ \\_\\ \\  \\ \\  __<      \\ \\ \\____  \\ \\ \\/\\ \\  \\ \\ \\-./\\ \\  \\ \\  _-/ \\ \\ \\_\\ \\  \\/_/\\ \\/ \\ \\  __\\   \\ \\  __<   \n"
                  " \\ \\_____\\  \\ \\_\\\\\"\\_\\     \\/\\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\     \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\ \\_\\  \\ \\_\\    \\ \\_____\\    \\ \\_\\  \\ \\_____\\  \\ \\_\\ \\_\\ \n"
                  "  \\/_____/   \\/_/ \\/_/      \\/_____/   \\/_____/   \\/_____/   \\/_/ /_/      \\/_____/   \\/_____/   \\/_/  \\/_/   \\/_/     \\/_____/     \\/_/   \\/_____/   \\/_/ /_/ \n"
                  "                                                                                                                                                               ";

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
    plateau.addPieceReserve(abeille2);
    plateau.addPieceReserve(fourmi2);
    plateau.addPieceReserve(scarabee2);
    plateau.addPieceReserve(sauterelle2);
    plateau.addPieceReserve(coccinelle2);
    plateau.addPieceReserve(moustique2);
    plateau.addPieceReserve(araignee2);
    //plateau.movePiece(araignee2, Coords(0, 4));
    plateau.movePiece(abeille2, Coords(-2, 0));


    plateau.afficher(true);

    cout<<"Cases habitees = "<<plateau.getGraphe().getNbInhabitedCases()<<endl;
    cout<<"Ruche brisee si bouge a "<<Coords(0, 0)<<" : "<<plateau.getGraphe().wouldHiveBreak(Coords(0, 0))<<endl;
    
    } catch (const exception& e) {
        cout<<e.what()<<endl;
    }

    cout<<"\n\nTout nickel !"<<endl;
    return 0;
}
