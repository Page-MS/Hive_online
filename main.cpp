
#include "pieces.cpp"
//#include "cases.cpp"
//#include "coords.cpp"
//#include "Joueur.cpp"
//#include "partie.cpp"
//#include "plateau.cpp"
//#include "legalmoves.cpp"
#include "gamemanager.cpp"


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
    
    cout<<"\n\n"<<"|)     |  |. _ |-|- _     /|  .     [~|.  |-|-    ,_ |  |)     _ \n"
                  "|)\\/  _|L|||(/_|_|_(/_,  /-||`|(|,  [_||()|_|_  (|||(|  | (|(|(/_\n"
                  "  /                                                         _|   ";

    GameManager game_manager;
    game_manager.afficher_menu();
    return 0;
}
