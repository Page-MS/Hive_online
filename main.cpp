#include "partie.hpp"


int main() {

    try {
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

cout<<"\n\n"<<"   ___         ___       _             __     ___     __  __          _______      __  __      ___               \n"
              "  / _ )__ __  / _ | ____(_)__ _    __ / /_ __/ (_)__ / /_/ /____     / __/ (_)__  / /_/ /_    / _ \\___ ____ ____ \n"
              " / _  / // / / __ |/ __/ / _ `/   / // / // / / / -_) __/ __/ -_)   / _// / / _ \\/ __/ __/   / ___/ _ `/ _ `/ -_)\n"
              "/____/\\_, / /_/ |_/_/ /_/\\_,_( )  \\___/\\_,_/_/_/\\__/\\__/\\__/\\__( ) /___/_/_/\\___/\\__/\\__( ) /_/   \\_,_/\\_, /\\__/ \n"
              "     /___/                   |/                                |/                       |/            /___/      ";
    GameManager game;
    game.afficher_menu();
} catch (const exception& e) {
    cout<<e.what()<<endl;
}
cout<<"Tout nickel !"<<endl;
return 0;
}