#include "Main_Widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QIcon>

Main_Widget::Main_Widget(QWidget *parent, int w_size, int h_size)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(w_size,h_size));
    this->setWindowTitle("Czolgi Wars");
    this->setWindowIcon(QIcon(":/images/icon.png"));

    QPixmap bground_img(":/images/background_02.png");

    bground_img = bground_img.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bground_img);
    this->setPalette(palette);


}

Main_Widget::~Main_Widget()
{
    delete ui;
}

