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

enum difficulty
{easy,
medium,
hard};


class Map;

class Player;

class Menu;

class Game: public QWidget
{
    Q_OBJECT
public:
    Game();

    void create_player(QString name);
    void displayMenu();
    void draw_interface(Player* player);
    void newGame();

    int diffic = 0;

    QString bckg_path = ":/img/img/background_02.png";
    QString icon_path = ":/img/img/icon.png";
    QString win_title = "CZOLGI WARS";

public slots:
    void set_baron();
    void set_kabaczek();
    void set_fiolet();

private:
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

protected:

    int win_width = 1360;
    int win_height = 800;
};

#endif // GAME_H
