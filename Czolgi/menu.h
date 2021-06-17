#ifndef MENU_H
#define MENU_H

#include <QGraphicsView>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QDialog>
#include <QMediaPlayer>

#include "button.h"
#include "game.h"

class Menu : public QGraphicsView
{
    Q_OBJECT

public:
    Menu(Game *parent = nullptr);
    ~Menu();

    void display();
    void play_music();

public slots:
    void quit_ask();
    void credits();
    void start_game();
    void quit_all();

private:
    QGraphicsScene* menu = nullptr;
    QGraphicsView* dialog_view = nullptr;
    QGraphicsView* cr_dialog_view = nullptr;
    QMediaPlayer* intro = nullptr;

    QDialog* dialog = nullptr;
    QDialog* cr_dialog = nullptr;
    QGraphicsTextItem *ver_inf = nullptr;
    QGraphicsTextItem *title = nullptr;
    Game* game = nullptr;

    Button *new_game = nullptr;
    Button *load_game = nullptr;
    Button *info = nullptr;
    Button *quit_butt = nullptr;
    Button *stay = nullptr;
    Button *leave = nullptr;

    int font_size = 32;
};
#endif // MENU_H
