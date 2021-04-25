#include "game.h"
#include <QIcon>
#include "menu.h"

Game::Game(Menu* mn)
{
    menu = mn;

    setFixedSize(QSize(mn->win_width, mn->win_height));
    setWindowTitle(mn->win_title);
    setWindowIcon(QIcon(mn->icon_path));

    layout = new QGridLayout(this);

    map_view = new QGraphicsView;
    map_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map_view->setFixedSize(QSize(mn->win_width, mn->win_height-100));

    game_interfece = new QGraphicsView;
    game_interfece->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_interfece->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_interfece->setFixedSize(QSize(mn->win_width, 100));

    layout->addWidget(map_view, 0, 0, 0, 2);
    layout->addWidget(game_interfece, 1, 0, 1, 2);

    this->show();

}

int Game::df_level()
{
   return 0;
}

void Game::create_player()
{

}

void Game::draw_map()
{

}
