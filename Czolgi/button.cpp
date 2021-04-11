#include "button.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QGraphicsTextItem>


button::button( int width, int height, QString name, QObject *parent) : QObject(parent)
{
    //creating rectangle button

        setRect(0, 0, width, height);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkGreen);
        setBrush(brush);

        //adding text
        text = new QGraphicsTextItem(name, this);
        text->setDefaultTextColor(Qt::white);
        text->setFont(QFont("calibri", 24));
        int xPos = this->rect().width()/2 - text->boundingRect().width()/2;
        int yPos = this->rect().height()/2 - text->boundingRect().height()/2;
        text -> setPos(xPos, yPos);


        //allow responding to hover events
        this->setAcceptHoverEvents(true);
}

void button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);
}

void button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGreen);
    setBrush(brush);
}


button::~button()
{

}
