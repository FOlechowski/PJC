#ifndef MENU_H
#define MENU_H

#include <QGraphicsView>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QDialog>
#include <QMediaPlayer>

#include "credits.h"
#include "quitwindow.h"
#include "button.h"
#include "game.h"

class Menu : public QGraphicsView
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);

    void display();
    void play_music();

    int win_width = 1360;
    int win_height = 800;
    /*
    int up_width = 800;
    int up_height = 400;
    */
    int font_size = 32;

    QString bckg_path = ":/img/img/background_02.png";
    QString icon_path = ":/img/img/icon.png";
    QString win_title = "CZOLGI WARS";

    ~Menu();

public slots:
    void quit_ask();
    void credits();
    void start_game();

private:
    QGraphicsScene* menu;
    QGraphicsTextItem* title;
    QGraphicsTextItem* ver_inf;

    Button* new_game;
    Button* load_game;
    Button* quit_butt;
    Button* info;

    QuitWindow* quit;
    Credits* cr;
    Game* game;
};
#endif // MENU_H
