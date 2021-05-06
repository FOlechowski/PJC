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

    void display();
    void play_music();

    int font_size = 32;

public slots:
    void quit_ask();
    void credits();
    void start_game();
    void quit_all();

private:
    QGraphicsScene* menu;
    QGraphicsView* dialog_view;
    QGraphicsView* cr_dialog_view;

    QDialog* dialog;
    QDialog* cr_dialog;

    Game* game;
};
#endif // MENU_H
