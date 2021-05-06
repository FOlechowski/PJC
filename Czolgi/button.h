#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QGraphicsTextItem>
#include <QFont>

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Button(int width, int height, QString name, QObject *parent = nullptr);

    ~Button();

signals:
    void clicked();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    QGraphicsTextItem* text;
};

#endif // BUTTON_H
