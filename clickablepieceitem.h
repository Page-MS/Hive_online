#ifndef CLICKABLEPIECEITEM_H
#define CLICKABLEPIECEITEM_H

#include <QGraphicsRectItem>
#include <QObject>
#include "pieces.h"
//classe des pieces sous forme rectangle dans la pioche
class ClickablePieceItem : public QObject, public QGraphicsRectItem {
    //pour les signaux
    Q_OBJECT

public:
    //constructeur
    explicit ClickablePieceItem(Piece* piece, QGraphicsItem* parent = nullptr);

signals:
    void pieceClicked(Piece* piece);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    //stocke un pointeur vers la piece
    Piece* piece;
    QGraphicsTextItem* textItem;
};

#endif // CLICKABLEPIECEITEM_H
