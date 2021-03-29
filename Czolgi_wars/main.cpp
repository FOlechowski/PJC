#include "Main_Widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Main_Widget Main_Window;
    Main_Window.show();
    return a.exec();
}
