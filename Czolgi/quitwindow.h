#ifndef QUITWINDOW_H
#define QUITWINDOW_H

#include <QObject>
#include <QDialog>
#include <QGraphicsView>

class QuitWindow : public QDialog
{
    Q_OBJECT
public:
    QuitWindow(QGraphicsView* window, QString ic_path);
    ~QuitWindow();


public slots:


private:

};

#endif // QUITWINDOW_H
