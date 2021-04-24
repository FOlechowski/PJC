#ifndef MENU_H
#define MENU_H

#include <QGraphicsView>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QDialog>
#include <QMediaPlayer>
#include "credits.h"
#include "button.h"
#include "map.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);

    void display_menu();
    void play_music();

    int win_width = 1360;
    int win_height = 800;
    int up_width = 800;
    int up_height = 400;
    int font_size = 32;

    QString bckg_path = ":/img/img/background_02.png";
    QString icon_path = ":/img/img/icon.png";

    ~Game();

public slots:
    void quit_ask();
    void credits();
    void display_map();

private:

    QString win_title = "CZOLGI WARS";

    QMediaPlayer* intro;

    QGraphicsScene* menu;
    QGraphicsTextItem* title;
    QGraphicsTextItem* ver_inf;

    Button* new_game;
    Button* load_game;
    Button* quit_butt;
    Button* info;
    Button* leave;
    Button* stay;

    Credits* cr;
    Map* mp;

    QDialog* dialog = new QDialog(this);
    QGraphicsView* dialog_view = new QGraphicsView(dialog);
    QGraphicsScene* dialog_scene = new QGraphicsScene;

};
#endif // MENU_H
