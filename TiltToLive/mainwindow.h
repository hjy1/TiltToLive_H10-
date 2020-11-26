#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "gameengine.h"
#include "clickableview.h"

namespace Ui {
class TiltToLive;
}

class MainWindow : public QMainWindow, public GameEngine
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::TiltToLive *ui;
    QTimer *update_time;
    QAction *act;

private slots:
    void refresh_game_map();
    void map_clicked(const double &x, const double &y);
    void end_game();
};

#endif // MAINWINDOW_H
