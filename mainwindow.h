#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "interactivecaseitem.h"
#include "partie.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
//un slot est unne fonction executée en réponse à l'envoi d'un signal
private slots:
    void handleCaseClick(const Coords& coords);

private:
    //afiche la vue principale du plateau
    QGraphicsView* view;
    //garde la manière dont sont ordonnées tout les éléments de la vue
    QGraphicsScene* scene;
    Partie partie;

private:
    QGraphicsView* player1PiecesView;
    QGraphicsView* player2PiecesView;
    QGraphicsScene* player1Scene;
    QGraphicsScene* player2Scene;

    Piece* selectedPiece; // Pièce actuellement sélectionnée pour placement
    Joueur* joueur1;
    Joueur* joueur2;

    void drawPlayerPieces(); // Dessiner les pièces disponibles
    void updatePieceSelection(Piece* piece); // Mettre à jour la sélection de pièce

    void drawBoard();//dessiner le plateau
};

#endif // MAINWINDOW_H
