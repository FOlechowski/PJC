#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Main_Widget : public QWidget
{
    Q_OBJECT

public:
    Main_Widget(QWidget *parent = nullptr, int w_size = 600 , int h_size = 800);

    ~Main_Widget();

private:
    Ui::Widget *ui;

};
#endif // MAIN_WIDGET_H
