#include "menu.h"

#include <QApplication>

Menu* menu;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menu = new Menu;
    menu->show();
    menu->display_menu();
    return a.exec();
}
