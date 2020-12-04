#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "gameengine.h"
#include "clickableview.h"
#include <QKeyEvent>
#include <QResizeEvent>

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
    QAction *res, *pau, *scorer;
    int keybuffer; // 1111 : wads, 1->released, 0->pressed
    bool gamestage; // 0 : pausing, 1: running
    void game_end();
    void key_controller(); //update arrow velocity when using keyboard to countrol.
    void resizeEvent ( QResizeEvent * event ) override;
    void keyPressEvent (QKeyEvent* ev) override;
    void keyReleaseEvent (QKeyEvent *ev) override;

private slots:
    void refresh_game_map();
    void map_clicked(const double &x, const double &y);
    void game_pause();
    void game_resume();
};

#endif // MAINWINDOW_H
