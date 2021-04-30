#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QObject>
#include <QTimer>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Player();

    void setPlayerName(QString Pname);
    void shot();

    void keyPressEvent(QKeyEvent * event);

public slots:
    void reload();

private:

    QTimer *timer = new QTimer;

    int bullets = 50;

    bool is_loading = false;

    QString name;
    qreal angle = 0;
    qreal speed = 5;
};

#endif // PLAYER_H
