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

    void change_color(Qt::GlobalColor color);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    ~Button();

    QGraphicsTextItem* text;

signals:
    void clicked();

private:

};

#endif // BUTTON_H
