#include "ClickablePieceItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QBrush>
#include <QFont>

ClickablePieceItem::ClickablePieceItem(const Piece* piece, QGraphicsItem* parent)
    : QObject(), QGraphicsRectItem(parent), piece(piece) {

    // Configurer l'élément graphique
    setRect(0, 0, 40, 40); // Taille de la pièce
    setBrush(Qt::lightGray);

    // Ajouter un texte descriptif
    textItem = new QGraphicsTextItem(this);

    QString symbol;
    switch (piece->getType()) {
    case Araignee: symbol = "Ar"; break;
    case Scarabee: symbol = "Sc"; break;
    case Fourmi: symbol = "Fo"; break;
    case Sauterelle: symbol = "Sa"; break;
    case Moustique: symbol = "Mo"; break;
    case Coccinelle: symbol = "Co"; break;
    case Abeille: symbol = "Ab"; break;
    }

    textItem->setPlainText(symbol);
    textItem->setDefaultTextColor(Qt::black);
    textItem->setFont(QFont("Arial", 10, QFont::Bold));
    textItem->setPos(5, 5); // Position du texte dans le rectangle
}

void ClickablePieceItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    emit pieceClicked(piece);  // Émettre la pièce liée à cet élément
    QGraphicsRectItem::mousePressEvent(event);  // Appeler le parent
}
