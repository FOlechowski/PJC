#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QLineEdit>
#include "button.h"
#include "map.h"
#include "player.h"


enum difficulty{easy, medium, hard};

class Menu;

class Game: public QWidget
{
    Q_OBJECT
public:
    Game(Menu* mn);

    void create_player(QString name);
    void draw_interface(Player* player);

public slots:
    void set_baron();
    void set_kabaczek();
    void set_fiolet();

private:

    int diffic = 0;

    Menu* menu;
    Player* player;
    Map* map;

    QLineEdit* username;

    QGraphicsView* init_view;
    QGraphicsView* map_view;
    QGraphicsView* game_interfece;

    QGraphicsScene* init_scene;

    Button* red_baron;
    Button* kabaczek;
    Button* fiolet;

};

#endif // GAME_H
