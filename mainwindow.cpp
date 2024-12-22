#include "mainwindow.h"
#include "clickablepieceitem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    view(new QGraphicsView(this)),
    scene(new QGraphicsScene(this)),
    player1PiecesView(new QGraphicsView(this)),
    player2PiecesView(new QGraphicsView(this)),
    player1Scene(new QGraphicsScene(this)),
    player2Scene(new QGraphicsScene(this)),
    joueur1Nom(new QLineEdit(this)),
    joueur2Nom(new QLineEdit(this)),
    joueur1IA(new QCheckBox("IA", this)),
    joueur2IA(new QCheckBox("IA", this)),
    commencerPartieButton(new QPushButton("Commencer Partie", this)),
    selectedPiece(nullptr) {

    setWindowTitle("Hive Game");
    resize(1000, 800);

    // Configurer l'interface utilisateur
    setupPlayerConfigUI();

    // Connecter le bouton "Commencer Partie"
    connect(commencerPartieButton, &QPushButton::clicked, this, &MainWindow::onCommencerPartieClicked);
}

MainWindow::~MainWindow() {
    // Supprimer les scènes et les vues pour éviter les fuites mémoire
    delete player1Scene;
    delete player2Scene;
    delete scene;

    delete player1PiecesView;
    delete player2PiecesView;
    delete view;

    qDebug() << "MainWindow détruite proprement.";
}

void MainWindow::setupPlayerConfigUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout* joueur1Layout = new QHBoxLayout();
    joueur1Layout->addWidget(new QLabel("Joueur 1 :"));
    joueur1Layout->addWidget(joueur1Nom);
    joueur1Layout->addWidget(joueur1IA);

    QHBoxLayout* joueur2Layout = new QHBoxLayout();
    joueur2Layout->addWidget(new QLabel("Joueur 2 :"));
    joueur2Layout->addWidget(joueur2Nom);
    joueur2Layout->addWidget(joueur2IA);

    mainLayout->addLayout(joueur1Layout);
    mainLayout->addLayout(joueur2Layout);
    mainLayout->addWidget(commencerPartieButton);

    setCentralWidget(centralWidget);
}

void MainWindow::onCommencerPartieClicked() {
    QString pseudo1 = joueur1Nom->text();
    QString pseudo2 = joueur2Nom->text();
    bool ia1 = joueur1IA->isChecked();
    bool ia2 = joueur2IA->isChecked();

    if (pseudo1.isEmpty() || pseudo2.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer les noms des deux joueurs !");
        return;
    }

    // Initialiser la partie
    partie.commencerPartie(pseudo1, pseudo2, ia1, ia2);
    joueur1 = partie.getEtatActuel().getJoueurCourant();
    joueur2 = partie.getEtatActuel().getAutreJoueur();

    // Supprimer les widgets de configuration
    delete joueur1Nom;
    delete joueur2Nom;
    delete joueur1IA;
    delete joueur2IA;
    delete commencerPartieButton;

    // Configurer l'interface de jeu
    setWindowTitle("Hive Game - En jeu");

    // Réduire la taille globale de la fenêtre
    resize(800, 600);

    QWidget* gameWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(gameWidget);

    // Vue principale pour le plateau (grille de jeu)
    view->setScene(scene);
    view->setMinimumHeight(400); // Ajuster la hauteur minimum de la grille
    mainLayout->addWidget(view, 3); // Attribuer plus de poids à la grille (3 parts)

    // Vues pour les pièces des joueurs
    QHBoxLayout* playersLayout = new QHBoxLayout();

    // Labels pour les noms des joueurs
    QVBoxLayout* player1Layout = new QVBoxLayout();
    player1Label = new QLabel(QString("Joueur 1: %1").arg(pseudo1));
    player1Label->setAlignment(Qt::AlignCenter);
    player1Layout->addWidget(player1Label);
    player1PiecesView->setScene(player1Scene);
    player1PiecesView->setFixedHeight(80); // Réduire encore la hauteur des réserves
    player1Layout->addWidget(player1PiecesView);

    QVBoxLayout* player2Layout = new QVBoxLayout();
    player2Label = new QLabel(QString("Joueur 2: %1").arg(pseudo2));
    player2Label->setAlignment(Qt::AlignCenter);
    player2Layout->addWidget(player2Label);
    player2PiecesView->setScene(player2Scene);
    player2PiecesView->setFixedHeight(80); // Réduire encore la hauteur des réserves
    player2Layout->addWidget(player2PiecesView);

    playersLayout->addLayout(player1Layout, 1); // Garder un poids normal pour chaque joueur
    playersLayout->addLayout(player2Layout, 1);
    mainLayout->addLayout(playersLayout, 1); // Réserver moins de place aux réserves (1 part)

    setCentralWidget(gameWidget);

    // Afficher la grille de jeu et les pièces en réserve
    drawBoard();
    updateReserve();
}

void MainWindow::drawBoard() {
    scene->clear(); // Efface tous les éléments existants

    const Plateau& plateau = partie.getEtatActuel().getPlateau();
    const Graphe& graphe = plateau.getGraphe();

    // Dimensions des hexagones
    double hexWidth = 50; // Largeur d'un hexagone
    double hexHeight = hexWidth * 0.866; // Hauteur d'un hexagone basé sur sa largeur

    qDebug() << "Dimensions de l'hexagone : " << hexWidth << "x" << hexHeight;

    // Parcours de la grille pour dessiner les cases
    for (auto it = graphe.getIterator(); !it.atEndColonne(); it.nextColonne()) {
        for (it.firstLigne(); !it.atEndLigne(); it.nextLigne()) {
            const Case& caseInGraphe = it.getCurrent();
            const Coords& coords = caseInGraphe.getCoords();

            // Calcul précis des positions
            double x = coords.getX() * hexWidth * 0.75; // Décalage horizontal
            double y = coords.getY() * hexHeight;

            if (static_cast<int>(coords.getX()) % 2 != 0) {
                y += hexHeight / 2; // Décalage de la moitié de la hauteur
            }

            // Log des positions calculées
            qDebug() << "Case (" << coords.getX() << ", " << coords.getY() << ") : x=" << x << " y=" << y;

            // Créer une case hexagonale interactive
            InteractiveCaseItem* hexItem = new InteractiveCaseItem(coords);
            hexItem->setPos(x, y);

            // Dessiner les pièces si présentes
            if (!caseInGraphe.empty()) {
                const Piece& piece = caseInGraphe.getUpperPiece();
                QColor pieceColor = piece.getCamp() ? Qt::red : Qt::blue;
                hexItem->setBrush(pieceColor);

                QGraphicsTextItem* pieceText = new QGraphicsTextItem(QString::fromStdString(piece.strPiece()));
                pieceText->setDefaultTextColor(Qt::white);
                pieceText->setParentItem(hexItem);

                QRectF hexBounds = hexItem->boundingRect();
                QRectF textBounds = pieceText->boundingRect();
                pieceText->setPos(
                    hexBounds.center().x() - textBounds.width() / 2,
                    hexBounds.center().y() - textBounds.height() / 2
                    );
            }

            connect(hexItem, &InteractiveCaseItem::caseClicked, this, &MainWindow::handleCaseClick);
            scene->addItem(hexItem);
        }
    }

    qDebug() << "Grille dessinée.";
}

void MainWindow::handleCaseClick(const Coords& coords) {
    // Récupérer l'état actuel et le plateau
    EtatDuJeu& etat = partie.getEtatActuel();
    Plateau& plateau = etat.getPlateau();
    Joueur* joueurCourant = etat.getJoueurCourant();

    // Vérifier si une pièce est déjà sélectionnée
    if (selectedPiece) {
        if (plateau.inReserve(selectedPiece)) {
            // La pièce est dans la réserve : tentative de placement
            qDebug() << "Tentative de placement de la pièce depuis la réserve : " << QString::fromStdString(selectedPiece->strPiece());

            bool actionReussie = joueurCourant->jouerCoupCreer(selectedPiece, coords, plateau);

            if (!actionReussie) {
                qWarning() << "Le placement de la pièce depuis la réserve a échoué.";
                return;
            }

            // Action réussie : mise à jour de l'état
            qDebug() << "Pièce placée avec succès depuis la réserve.";
            selectedPiece = nullptr; // Désélectionner la pièce
            clearHighlights();
            drawBoard();             // Rafraîchir le plateau
            updateReserve();         // Mettre à jour les pièces en réserve

            // Passer au joueur suivant
            etat.joueur_courant = etat.getAutreJoueur();
            qDebug() << "C'est maintenant au tour de : " << QString::fromStdString(etat.joueur_courant->getNom());

            // Gérer le tour de l'IA si nécessaire
            if (etat.joueur_courant->getIsIA()) {
                qDebug() << "L'IA joue un coup...";
                jouerCoupIA();
            }

            return;
        } else {
            // La pièce est sur le plateau : tentative de déplacement
            const Coords* currentCoords = plateau.coordsPiece(*selectedPiece);
            if (!currentCoords) {
                qWarning() << "Impossible de trouver les coordonnées actuelles de la pièce sélectionnée.";
                selectedPiece = nullptr;
                clearHighlights();
                return;
            }

            qDebug() << "Tentative de déplacement de la pièce : " << QString::fromStdString(selectedPiece->strPiece())
                     << " de " << currentCoords->getX() << ":" << currentCoords->getY()
                     << " vers " << coords.getX() << ":" << coords.getY();

            Graphe& grapheNonConst = const_cast<Graphe&>(plateau.getGraphe());
            std::vector<Coords> coupsLegaux = selectedPiece->coupsPossibles(&grapheNonConst, *currentCoords);

            // Vérifier si la case est un coup légal
            if (std::find(coupsLegaux.begin(), coupsLegaux.end(), coords) == coupsLegaux.end()) {
                qWarning() << "La position cible " << coords.getX() << ":" << coords.getY() << " n'est pas un coup légal.";
                return;
            }

            bool actionReussie = joueurCourant->jouerCoupDeplacer(selectedPiece, coords, plateau);

            if (!actionReussie) {
                qWarning() << "Le déplacement de la pièce a échoué.";
                selectedPiece = nullptr;
                clearHighlights();
                return;
            }

            // Action réussie : mise à jour de l'état
            qDebug() << "Pièce déplacée avec succès sur le plateau.";
            selectedPiece = nullptr; // Désélectionner la pièce
            clearHighlights();
            drawBoard();             // Rafraîchir le plateau
            updateReserve();         // Mettre à jour les pièces en réserve

            // Passer au joueur suivant
            etat.joueur_courant = etat.getAutreJoueur();
            qDebug() << "C'est maintenant au tour de : " << QString::fromStdString(etat.joueur_courant->getNom());

            // Gérer le tour de l'IA si nécessaire
            if (etat.joueur_courant->getIsIA()) {
                qDebug() << "L'IA joue un coup...";
                jouerCoupIA();
            }

            return;
        }
    }

    // Si aucune pièce n'est sélectionnée, vérifier si une pièce se trouve sur la case cliquée
    const Case& caseCible = plateau.getGraphe().getCase(coords);
    if (!caseCible.empty()) {
        // Une pièce est présente sur cette case
        selectedPiece = &caseCible.getUpperPiece();
        qDebug() << "Pièce sélectionnée sur le plateau : " << QString::fromStdString(selectedPiece->strPiece())
                 << " coord : " << coords.getX() << ":" << coords.getY()
                 << " camp : " << selectedPiece->getCamp();

        // Vérifier si la pièce appartient au joueur courant
        if (selectedPiece->getCamp() != joueurCourant->getCamp()) {
            qWarning() << "Vous ne pouvez pas sélectionner une pièce qui ne vous appartient pas.";
            selectedPiece = nullptr;
            clearHighlights();
            return;
        }

        // Afficher les coups possibles pour cette pièce
        Graphe& grapheNonConst = const_cast<Graphe&>(plateau.getGraphe());
        std::vector<Coords> coupsLegaux = selectedPiece->coupsPossibles(&grapheNonConst, coords);

        clearHighlights();  // Réinitialiser les surbrillances
        afficherCoupsPossibles(coupsLegaux);

        if (coupsLegaux.empty()) {
            qWarning() << "Aucun coup possible pour cette pièce.";
        }
        return;
    }

    // Sélectionner une pièce depuis la réserve
    // Sélectionner une pièce depuis la réserve
    const auto& piecesReserve = joueurCourant->getPieces(); // Récupère toutes les pièces du joueur
    for (const Piece* piece : piecesReserve) {
        if (plateau.inReserve(*piece) && piece == selectedPiece) {
            selectedPiece = piece;
            qDebug() << "Pièce sélectionnée dans la réserve : " << QString::fromStdString(selectedPiece->strPiece());

            // Afficher les coups possibles pour cette pièce
            std::vector<Coords> coupsLegaux = plateau.getGraphe().placableCoords(selectedPiece->getCamp());
            clearHighlights();
            afficherCoupsPossibles(coupsLegaux);

            if (coupsLegaux.empty()) {
                qWarning() << "Aucune position disponible pour placer cette pièce depuis la réserve.";
            }

            return;
        }
    }

    qWarning() << "Aucune pièce sélectionnée ou action valide détectée.";
    clearHighlights();
}

void MainWindow::updateReserve() {
    // Effacer l'ancienne scène
    player1Scene->clear();
    player2Scene->clear();

    // Obtenir les pièces en réserve des joueurs
    const std::vector<const Piece*>& reserve1 = joueur1->getPieces();
    const std::vector<const Piece*>& reserve2 = joueur2->getPieces();

    // Variables pour positionner les pièces dans les scènes
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    const double pieceSize = 50.0;

    // Dessiner la réserve du joueur 1
    for (const Piece* piece : reserve1) {
        if (!partie.getEtatActuel().getPlateau().inReserve(piece)) continue;

        ClickablePieceItem* item = new ClickablePieceItem(piece);
        item->setRect(0, 0, 40, 40);
        item->setBrush(Qt::red);
        item->setPos(x1, y1);
        player1Scene->addItem(item);

        connect(item, &ClickablePieceItem::pieceClicked, this, &MainWindow::selectPiece);

        x1 += pieceSize;
        if (x1 > 300.0) {
            x1 = 0.0;
            y1 += pieceSize;
        }
    }

    // Dessiner la réserve du joueur 2
    for (const Piece* piece : reserve2) {
        if (!partie.getEtatActuel().getPlateau().inReserve(piece)) continue;

        ClickablePieceItem* item = new ClickablePieceItem(piece);
        item->setRect(0, 0, 40, 40);
        item->setBrush(Qt::blue);
        item->setPos(x2, y2);
        player2Scene->addItem(item);

        connect(item, &ClickablePieceItem::pieceClicked, this, &MainWindow::selectPiece);

        x2 += pieceSize;
        if (x2 > 300.0) {
            x2 = 0.0;
            y2 += pieceSize;
        }
    }
}

void MainWindow::selectPiece(const Piece* piece) {
    selectedPiece = piece;
    qDebug() << "Pièce sélectionnée : " << QString::fromStdString(piece->strPiece());
}

void MainWindow::updateCaseDisplay(const Coords& coords, const Piece* piece) {
    for (QGraphicsItem* item : scene->items()) {
        InteractiveCaseItem* caseItem = dynamic_cast<InteractiveCaseItem*>(item);
        if (caseItem && caseItem->getCoords() == coords) {
            // Utiliser boundingRect pour obtenir la taille de la case
            QRectF boundingBox = caseItem->boundingRect();

            // Crée un rectangle pour représenter la pièce
            QGraphicsRectItem* pieceBackground = new QGraphicsRectItem(boundingBox);
            pieceBackground->setBrush(piece->getCamp() ? Qt::red : Qt::blue);
            pieceBackground->setPos(caseItem->scenePos());

            // Ajoute le texte de la pièce
            QGraphicsTextItem* pieceText = new QGraphicsTextItem();
            pieceText->setPlainText(QString::fromStdString(piece->strPiece()));
            pieceText->setDefaultTextColor(Qt::white);
            pieceText->setFont(QFont("Arial", 14));
            pieceText->setPos(caseItem->scenePos() + QPointF(5, 5)); // Décalage pour ne pas couvrir toute la case

            // Ajoute les éléments graphiques à la scène
            scene->addItem(pieceBackground);
            scene->addItem(pieceText);
            return;
        }
    }
}

void MainWindow::closeEvent(QCloseEvent* event) {
    // Boîte de dialogue de confirmation
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Quitter",
                                                               "Voulez-vous vraiment quitter ?",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (resBtn == QMessageBox::Yes) {
        qDebug() << "Fermeture de l'application.";
        event->accept();
    } else {
        qDebug() << "Fermeture annulée.";
        event->ignore();
    }
}

void MainWindow::afficherCoupsPossibles(const std::vector<Coords>& positions) {
    for (const Coords& pos : positions) {
        for (QGraphicsItem* item : scene->items()) {
            InteractiveCaseItem* caseItem = dynamic_cast<InteractiveCaseItem*>(item);
            if (caseItem && caseItem->getCoords() == pos) {
                caseItem->setBrush(Qt::green); // Change la couleur de la case pour la surbrillance
            }
        }
    }
}

void MainWindow::clearHighlights() {
    for (QGraphicsItem* item : scene->items()) {
        InteractiveCaseItem* caseItem = dynamic_cast<InteractiveCaseItem*>(item);
        if (caseItem) {
            caseItem->setBrush(Qt::white); // Remet à la couleur par défaut (blanc, ou autre)
        }
    }
}

void MainWindow::showError(const QString& message) {
    QMessageBox::warning(this, "Erreur", message);
}

void MainWindow::jouerCoupIA() {
    EtatDuJeu& etat = partie.getEtatActuel();
    Plateau& plateau = etat.getPlateau();
    Joueur* ia = etat.joueur_courant;

    // Obtenir les coups possibles pour l'IA
    std::vector<Mouvement> coupsPossibles = etat.coupsPossibles(ia);
    std::vector<const Piece*> reserve = etat.reserveJoueur(ia);

    if (!reserve.empty()) {
        // Si des pièces sont en réserve, choisir une pièce aléatoire et une position aléatoire
        const Piece* piece = reserve[rand() % reserve.size()];
        std::vector<Coords> positionsLegales = plateau.getGraphe().placableCoords(ia->getCamp());

        if (!positionsLegales.empty()) {
            Coords choix = positionsLegales[rand() % positionsLegales.size()];
            ia->jouerCoupCreer(piece, choix, plateau);
            qDebug() << "IA a placé une pièce : " << QString::fromStdString(piece->strPiece()) << " en " << choix.getX() << ":" << choix.getY();
        }
    } else if (!coupsPossibles.empty()) {
        // Si aucune pièce n'est en réserve, déplacer une pièce sur le plateau
        Mouvement choix = coupsPossibles[rand() % coupsPossibles.size()];
        ia->jouerCoupDeplacer(choix.getPiece(), choix.getPosFinal(), plateau);
        qDebug() << "IA a déplacé une pièce : " << QString::fromStdString(choix.getPiece()->strPiece())
                 << " de " << choix.getPosInitial().getX() << ":" << choix.getPosInitial().getY()
                 << " à " << choix.getPosFinal().getX() << ":" << choix.getPosFinal().getY();
    } else {
        qDebug() << "L'IA ne peut pas jouer ce tour.";
    }

    // Mettre à jour l'affichage
    drawBoard();
    updateReserve();

    // Passer au joueur suivant
    etat.joueur_courant = etat.getAutreJoueur();
    qDebug() << "C'est maintenant au tour de : " << QString::fromStdString(etat.joueur_courant->getNom());
}
