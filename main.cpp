#include "pieces.cpp"
#include "plateau.cpp"
#include "cases.cpp"
#include "coords.cpp"
//#include <windows.h>
//#include "Joueur.cpp"
//#include "partie.cpp"
#include "legalmoves.cpp"
//#include "gamemanager.cpp"
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
