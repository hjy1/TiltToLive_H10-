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

void MainWindow::keyPressEvent(QKeyEvent *ev){
    QWidget::keyPressEvent(ev);
    if(ev->key() == Qt::Key_Space && !ev->isAutoRepeat())
        gamestage ? game_pause() : game_resume();
}
