#ifndef INTERACTIVECASEITEM_H
#define INTERACTIVECASEITEM_H

#include <QGraphicsObject>
#include <QPolygonF>
#include "coords.h"
//InteractiveCaseItem se comporte comme un objet graphique
class InteractiveCaseItem : public QGraphicsObject {
    //macro qui lui permet d'envoyer des signaux
    Q_OBJECT

public:
    //constructeur pour l'affichage
    explicit InteractiveCaseItem(const Coords& coords, QGraphicsItem* parent = nullptr);
    //getter
    const Coords& getCoords() const { return coords; }

    void setFillColor(const QColor& color);

    //fonction qui return la hitbox d'une case
    QRectF boundingRect() const override;
    //affiche la case
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    //definit la forme et la hitbox
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
