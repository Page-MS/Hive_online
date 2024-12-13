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

private slots:
    void handleCaseClick(const Coords& coords);

private:
    QGraphicsView* view;
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

    void drawBoard();
};

#endif // MAINWINDOW_H
