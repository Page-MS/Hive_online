#include "interactivecaseitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

InteractiveCaseItem::InteractiveCaseItem(const Coords& coords, QGraphicsItem* parent)
    : QGraphicsObject(parent), coords(coords), fillColor(Qt::lightGray), selected(false) {
    setAcceptHoverEvents(true); // Permet la gestion des événements de survol

    // Crée la forme hexagonale
    double radius = 25; // Taille de l'hexagone
    for (int i = 0; i < 6; ++i) {
        double angle = M_PI / 3 * i;
        hexagon << QPointF(radius * cos(angle), radius * sin(angle));
    }

    m_brush = QBrush(fillColor);
}

void InteractiveCaseItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsObject::mousePressEvent(event); // Appel de la méthode parente

    if (!scene()) {
        qWarning() << "Scène non valide.";
        return;
    }

    // Émettre le signal
    emit caseClicked(coords);
}

QRectF InteractiveCaseItem::boundingRect() const {
    return hexagon.boundingRect();
}

QPainterPath InteractiveCaseItem::shape() const {
    QPainterPath path;
    path.addPolygon(hexagon); // Définit l'hexagone comme zone interactive
    return path;
}

void InteractiveCaseItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(fillColor);
    painter->setPen(Qt::black);
    painter->drawPolygon(hexagon);
}

void InteractiveCaseItem::setFillColor(const QColor& color) {
    fillColor = color;
    update(); // Demande une mise à jour graphique
}

void InteractiveCaseItem::setBrush(const QBrush& brush) {
    m_brush = brush;
    setFillColor(m_brush.color()); // Utilise la couleur du pinceau
}

void InteractiveCaseItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    Q_UNUSED(event);
    if (!selected) {
        setFillColor(Qt::cyan); // Couleur temporaire pour indiquer le survol
    }
}

void InteractiveCaseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    Q_UNUSED(event);
    if (!selected) {
        setFillColor(m_brush.color()); // Restaure la couleur par défaut
    }
}
