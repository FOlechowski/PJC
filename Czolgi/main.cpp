#include "menu.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;
    game.show();
    game.display_menu();
    return a.exec();
}
