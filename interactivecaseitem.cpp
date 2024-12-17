#include "InteractiveCaseItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QPainterPath>

InteractiveCaseItem::InteractiveCaseItem(const Coords& coords, QGraphicsItem* parent)
    : QGraphicsObject(parent), coords(coords), fillColor(Qt::lightGray), selected(false) {
    setAcceptHoverEvents(true); // Active les événements de survol
    double radius = 25;
    //boucle de creation de l'hexagone
    for (int i = 0; i < 6; ++i) {
        double angle = M_PI / 3 * i;
        hexagon << QPointF(radius * cos(angle), radius * sin(angle));
    }
}

void InteractiveCaseItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsObject::mousePressEvent(event);

    selected = !selected;

    if (selected) {
        setFillColor(Qt::yellow);
    } else {
        setFillColor(Qt::lightGray);
    }

    emit caseClicked(coords);

    qDebug() << "Clicked case at coords:" << coords.getX() << "," << coords.getY() << "Selected:" << selected;
}

QRectF InteractiveCaseItem::boundingRect() const {
    return hexagon.boundingRect();
}

void InteractiveCaseItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //set les options du painter
    painter->setBrush(fillColor);
    painter->setPen(Qt::black);
    //dessine a partir des options precedentes
    painter->drawPolygon(hexagon);
}

void InteractiveCaseItem::setFillColor(const QColor& color) {
    fillColor = color;
    update();
    //verifie que la scene est update
    if (scene()) {
        scene()->invalidate(boundingRect());
    }
}

QPainterPath InteractiveCaseItem::shape() const {
    QPainterPath path;
    path.addPolygon(hexagon); // Ajoute la forme de l'hexagone comme zone interactive
    return path;
}

void InteractiveCaseItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    Q_UNUSED(event);
    if (!selected) { // Change la couleur seulement si la case n'est pas déjà sélectionnée
        setFillColor(Qt::cyan); // Couleur temporaire pour indiquer le survol
    }
}

void InteractiveCaseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    Q_UNUSED(event);
    if (!selected) { // Restaure la couleur seulement si la case n'est pas sélectionnée
        setFillColor(Qt::lightGray);
    }
}
