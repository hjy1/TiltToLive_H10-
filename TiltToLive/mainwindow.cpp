#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include <QDebug>
#include <QString>
#include "constants.h"
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TiltToLive)
{
    /* Scene
     * ***************** */
    ui->setupUi(this);
    this->resize(MAP_SIZE_L+10, MAP_SIZE_W+110);
    this->setMinimumSize(2 * ARROW_SIZE + 10, 2 * ARROW_SIZE + 110);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

    /* Timer
     * ***************** */
    update_time = new QTimer;
    connect(update_time, SIGNAL(timeout()), this, SLOT(refresh_game_map()));
    update_time->start(ONE_TIK_TIME);

    /* Pause & Resume
     * ***************** */
    pau = ui->menuBar->addAction("Pause");
    res = ui->menuBar->addAction("Resume");
    connect(pau, SIGNAL(triggered()), this, SLOT(game_pause()));
    connect(res, SIGNAL(triggered()), this, SLOT(game_resume()));
    game_pause();

    /* Mouse
     * ***************** */
    ui->graphicsView->setMouseTracking(true);
    connect(ui->graphicsView, &ClickableView::mouseClicked, this, &MainWindow::map_clicked);

    /* Game Prepare
     * ***************** */
    init();
    keybuffer = 0b1111;
    qsrand(time(nullptr));
}

MainWindow::~MainWindow()
{
    delete pau;
    delete res;
    delete update_time;
    delete ui;
}

void MainWindow::refresh_game_map(){
    //static int count = 0;
    //qDebug() << "gamemap refreshed" <<QString::number(count++);
    move_objects();
    if(game_is_end) game_end();
}

void MainWindow::map_clicked(const double &x, const double &y){
    qDebug() << "mouse clicked" << QString::number(x) << QString::number(y);
    arrow.set_target(x,y);
}

void MainWindow::game_pause(){
    gamestage = 0;
    update_time->stop();
    pau->setVisible(false);
    res->setVisible(true);
}

void MainWindow::game_resume(){
    gamestage = 1;
    update_time->start(ONE_TIK_TIME);
    pau->setVisible(true);
    res->setVisible(false);
}

void MainWindow::game_end(){
    QMessageBox::information(nullptr, "Game Over!", "Redpoints have caught you!");
    QApplication::quit();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    int w = this->height(), l = this->width();
    ui->graphicsView->setFixedSize(l, w - 100);
    MAP_SIZE_L = l - 10;
    MAP_SIZE_W = w - 100 - 10;
    ui->graphicsView->setSceneRect(0,0,MAP_SIZE_L, MAP_SIZE_W);
    qDebug() << NUM(MAP_SIZE_L) << NUM(MAP_SIZE_W);
}

void MainWindow::key_controller(){
    double x = arrow.getp().getx() - ARROW_SIZE, y = arrow.getp().gety() - ARROW_SIZE;
    double dx = MAP_SIZE_L - arrow.getp().getx() - ARROW_SIZE, dy = MAP_SIZE_W - arrow.getp().gety() - ARROW_SIZE;
    Vector del;
    switch (keybuffer) {
    case 0b1111: //no key pressed
        arrow.set_target(arrow.getp());
        qDebug() << "no key pressed";
        break;
    case 0b0111: //pressed 'w', up
        arrow.set_target(arrow.getp().getx(), 0 + ARROW_SIZE);
        qDebug() << "pressed 'w', up";
        break;
    case 0b1011: //pressed 'a', left
        arrow.set_target(0 + ARROW_SIZE, arrow.getp().gety());
        qDebug() << "pressed 'a', left";
        break;
    case 0b1101: //pressed 'd', right
        arrow.set_target(MAP_SIZE_L - ARROW_SIZE, arrow.getp().gety());
        qDebug() << "pressed 'd', right";
        break;
    case 0b1110: //pressed 's', down
        arrow.set_target(arrow.getp().getx() ,MAP_SIZE_W - ARROW_SIZE);
        qDebug() << "pressed 's', down";
        break;
    case 0b1100://pressed 'd','s', right down(+,+), (dx,dy)
        del = (dx > dy ? Vector(dx, dx) : Vector(dy, dy));
        arrow.set_target(arrow.getp() + del);
        qDebug() << "pressed 'd','s', right down(+,+), (dx,dy)";
        break;
    case 0b1010://pressed 'a','s', left down(-,+), (x,dy)
        del = (x > dy ? Vector(-x, x) : Vector(-dy, dy));
        arrow.set_target(arrow.getp() + del);
        qDebug() << "pressed 'a','s', left down(-,+), (x,dy)";
        break;
    case 0b0101://pressed 'd','w', right up(+,-), (dx,y)
        del = (dx > y ? Vector(dx,-dx) : Vector(y,-y));
        arrow.set_target(arrow.getp() + del);
        qDebug() << "pressed 'd','w', right up(+,-), (dx,y)";
        break;
    case 0b0011://pressed 'a','w', left up(-,-), (x,y)
        del = (x > y ? Vector(-x,-x) : Vector(-y,-y));
        arrow.set_target(arrow.getp() + del);
        qDebug() << "pressed 'a','w', left up(-,-), (x,y)";
        break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev){
    QWidget::keyPressEvent(ev);
    if(ev->isAutoRepeat())  return ;
    if(ev->key() == Qt::Key_Space)
        gamestage ? game_pause() : game_resume();
    else if(ev->key() == Qt::Key_A || ev->key() == Qt::Key_W || ev->key() == Qt::Key_D || ev->key() == Qt::Key_S)
    {
        int val = (ev->key() == Qt::Key_W ? 3 :
                   ev->key() == Qt::Key_A ? 2 :
                   ev->key() == Qt::Key_D ? 1 :
                   ev->key() == Qt::Key_S ? 0 : -1);
        keybuffer |= (1 << (3 - val));
        keybuffer ^= (1 << val);
        qDebug() << NUM(val) << QString::number(keybuffer,2);
        key_controller();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev){
    QWidget::keyReleaseEvent(ev);
    if(ev->isAutoRepeat())  return ;
    if(ev->key() == Qt::Key_A || ev->key() == Qt::Key_W || ev->key() == Qt::Key_D || ev->key() == Qt::Key_S)
    {
        int val = (ev->key() == Qt::Key_W ? 3 :
                   ev->key() == Qt::Key_A ? 2 :
                   ev->key() == Qt::Key_D ? 1 :
                   ev->key() == Qt::Key_S ? 0 : -1);
        keybuffer |= (1 << val);
        qDebug() << NUM(val) << QString::number(keybuffer,2);
        key_controller();
    }
}
