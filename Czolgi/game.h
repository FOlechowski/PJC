#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include "button.h"
#include "map.h"
#include "player.h"

class Menu;

class Game: public QWidget
{
    Q_OBJECT
public:
    Game(Menu* mn);
    int df_level();
    void create_player();
    void draw_map();

private:
    Menu* menu;

    QGridLayout* layout;
    QGraphicsView* map_view;
    QGraphicsView* game_interfece;

    Button* red_baron;
    Button* kabaczek;
    Button* fiolet;


};

#endif // GAME_H
