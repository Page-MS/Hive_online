#ifndef INTERACTIVECASEITEM_H
#define INTERACTIVECASEITEM_H

#include <QGraphicsObject>
#include <QPolygonF>
#include "coords.h"

class InteractiveCaseItem : public QGraphicsObject {
    Q_OBJECT

public:
    explicit InteractiveCaseItem(const Coords& coords, QGraphicsItem* parent = nullptr);

    const Coords& getCoords() const { return coords; }

    void setFillColor(const QColor& color);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    QPainterPath shape() const override;

signals:
    void caseClicked(const Coords& coords);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;//pour survoler les cases
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    Coords coords;
    QPolygonF hexagon;
    QColor fillColor;
    bool selected;

};

#endif // INTERACTIVECASEITEM_H
