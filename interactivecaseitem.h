#ifndef INTERACTIVECASEITEM_H
#define INTERACTIVECASEITEM_H

#include <QGraphicsObject>
#include <QPolygonF>
#include <QBrush>
#include "coords.h"

class InteractiveCaseItem : public QGraphicsObject {
    Q_OBJECT

public:
    explicit InteractiveCaseItem(const Coords& coords, QGraphicsItem* parent = nullptr);

    const Coords& getCoords() const { return coords; }
    void setFillColor(const QColor& color); // Définit la couleur de remplissage
    void setBrush(const QBrush& brush);     // Définit le pinceau pour la case

    QRectF boundingRect() const override;  // Délimite la zone de dessin
    QPainterPath shape() const override;   // Définit la forme pour les interactions
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

signals:
    void caseClicked(const Coords& coords);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    Coords coords;             // Coordonnées logiques de la case
    QPolygonF hexagon;         // Forme de l'hexagone
    QBrush m_brush;            // Pinceau pour la case
    QColor fillColor;          // Couleur de remplissage
    bool selected;             // Indique si la case est sélectionnée
};

#endif // INTERACTIVECASEITEM_H
