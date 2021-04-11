#ifndef BUTTON_H
#define BUTTON_H

#include "menu.h"
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit button(int width, int height, QString name, QObject *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    ~button();

    QGraphicsTextItem* text;

signals:
    void clicked();

private:

};

#endif // BUTTON_H
