#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "Gameengine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public GameEngine
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    QTimer *update_time;

private slots:
    void update_game();
};

#endif // MAINWINDOW_H
