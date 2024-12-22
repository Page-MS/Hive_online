#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QObject>
#include <QLabel>
#include "interactivecaseitem.h"
#include "partie.hpp"

class Partie;

class MainWindow : public QMainWindow {
    Q_OBJECT

signals:
    void caseClicked(const Coords& coords); // Signal pour gérer les clics sur les cases du plateau.


public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    // Afficher les coups possibles pour une pièce ou une action.
    void afficherCoupsPossibles(const std::vector<Coords>& positions);

    // Effacer les mises en évidence des cases.
    void clearHighlights();

    // Afficher un message d'erreur à l'utilisateur.
    void showError(const QString& message);

    void drawBoard();
    void updateReserve();
    const Piece* getSelectedPiece() const {return selectedPiece;}
    Partie partie;

    QString getPseudo1() const { return joueur1Nom->text(); }
    QString getPseudo2() const { return joueur2Nom->text(); }
    bool isIA1() const { return joueur1IA->isChecked(); }
    bool isIA2() const { return joueur2IA->isChecked(); }
    void jouerCoupIA();


private slots:
    void onCommencerPartieClicked(); // Slot pour commencer la partie
    void handleCaseClick(const Coords& coords);
    void updateCaseDisplay(const Coords& coords, const Piece* piece);

    void selectPiece(const Piece* piece);


protected:
    void closeEvent(QCloseEvent* event) override;

private:
    bool highlightLegalPlacement(const Piece* piece, Plateau& plateau);
    bool highlightLegalMoves(const Piece* piece, Plateau& plateau);
    void updateAfterAction();

    Joueur* joueur1 = nullptr; // Joueur 1
    Joueur* joueur2 = nullptr; // Joueur 2
    QGraphicsView* view;
    QGraphicsScene* scene;

    QLabel* player1Label;
    QLabel* player2Label;


    QGraphicsView* player1PiecesView;
    QGraphicsView* player2PiecesView;
    QGraphicsScene* player1Scene;
    QGraphicsScene* player2Scene;

    QLineEdit* joueur1Nom;
    QLineEdit* joueur2Nom;
    QCheckBox* joueur1IA;
    QCheckBox* joueur2IA;
    QPushButton* commencerPartieButton;

    const Piece* selectedPiece;

    void setupPlayerConfigUI();

};

#endif // MAINWINDOW_H
