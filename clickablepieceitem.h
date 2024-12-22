#ifndef CLICKABLEPIECEITEM_H
#define CLICKABLEPIECEITEM_H

#include <QGraphicsRectItem>
#include <QObject>
#include "pieces.h"

class ClickablePieceItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    explicit ClickablePieceItem(const Piece* piece, QGraphicsItem* parent = nullptr);

signals:
    void pieceClicked(const Piece* piece);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    const Piece* piece;
    QGraphicsTextItem* textItem;
};

#endif // CLICKABLEPIECEITEM_H
