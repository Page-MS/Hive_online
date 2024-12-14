#include "mainwindow.h"
#include "clickablepieceitem.h"
#include <QDebug>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    view(new QGraphicsView(this)),
    scene(new QGraphicsScene(this)),
    player1PiecesView(new QGraphicsView(this)),
    player2PiecesView(new QGraphicsView(this)),
    player1Scene(new QGraphicsScene(this)),
    player2Scene(new QGraphicsScene(this)),
    selectedPiece(nullptr) {

    setWindowTitle("Hive Game");
    resize(1000, 800);

    // Configurer la vue du plateau
    view->setScene(scene);
    view->setGeometry(10, 10, 700, 600);
    setCentralWidget(view);

    // Configurer les joueurs
    joueur1 = new Joueur("Joueur 1", false);
    joueur2 = new Joueur("Joueur 2", false);

    // Configurer les vues pour les pièces
    player1PiecesView->setScene(player1Scene);
    player1PiecesView->setGeometry(720, 10, 250, 200);
    player2PiecesView->setScene(player2Scene);
    player2PiecesView->setGeometry(720, 220, 250, 200);

    drawBoard();
    drawPlayerPieces();
}

MainWindow::~MainWindow() {}

void MainWindow::drawBoard() {
    double hexWidth = 50;
    double hexHeight = hexWidth * 0.866;

    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            double x = col * hexWidth * 0.75;
            double y = row * hexHeight;

            if (col % 2 != 0) {
                y += hexHeight / 2;
            }

            Coords coords(col, row);
            InteractiveCaseItem* hexItem = new InteractiveCaseItem(coords);
            hexItem->setPos(x, y);

            connect(hexItem, &InteractiveCaseItem::caseClicked, this, &MainWindow::handleCaseClick);

            scene->addItem(hexItem);
        }
    }
}

void MainWindow::handleCaseClick(const Coords& coords) {
    if (selectedPiece) {
        try {
            // Récupérer le joueur courant
            Joueur* joueurCourant = (partie.getEtatActuel().getJoueurCourant() == joueur1) ? joueur1 : joueur2;

            // Poser la pièce
            joueurCourant->jouerCoup(selectedPiece, coords, partie.getEtatActuel().getPlateau());

            // Réinitialiser la sélection et mettre à jour l'affichage
            selectedPiece = nullptr;
            drawBoard();
            drawPlayerPieces();
        } catch (const std::invalid_argument& e) {
            qDebug() << "Invalid move:" << e.what();
        }
    } else {
        qDebug() << "No piece selected to place.";
    }
}

void MainWindow::drawPlayerPieces() {
    player1Scene->clear();
    player2Scene->clear();

    // Dessiner les pièces du joueur 1
    int xOffset = 0;
    for (auto* piece : joueur1->getPieces()) {
        ClickablePieceItem* pieceItem = new ClickablePieceItem(piece);
        pieceItem->setRect(0, 0, 40, 40); // Définir la taille de la pièce
        pieceItem->setBrush(Qt::red); // Couleur pour joueur 1
        pieceItem->setPos(xOffset, 0);
        player1Scene->addItem(pieceItem);

        connect(pieceItem, &ClickablePieceItem::pieceClicked, this, &MainWindow::updatePieceSelection);

        xOffset += 50; // Espacement horizontal
    }

    // Dessiner les pièces du joueur 2
    xOffset = 0;
    for (auto* piece : joueur2->getPieces()) {
        ClickablePieceItem* pieceItem = new ClickablePieceItem(piece);
        pieceItem->setRect(0, 0, 40, 40); // Définir la taille de la pièce
        pieceItem->setBrush(Qt::blue); // Couleur pour joueur 2
        pieceItem->setPos(xOffset, 0);
        player2Scene->addItem(pieceItem);

        connect(pieceItem, &ClickablePieceItem::pieceClicked, this, &MainWindow::updatePieceSelection);

        xOffset += 50;
    }
}

void MainWindow::updatePieceSelection(Piece* piece) {
    selectedPiece = piece;
    qDebug() << "Piece selected:" << piece->getType();
}
