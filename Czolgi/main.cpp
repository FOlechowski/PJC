#include "game.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;
    game.show();
    game.displayMenu();
    return a.exec();
}
