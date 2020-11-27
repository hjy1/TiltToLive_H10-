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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TiltToLive)
{
    /* Scene
     * ***************** */
    ui->setupUi(this);
    ui->graphicsView->setGeometry(9,9,MAP_SIZE_L+10, MAP_SIZE_W+10);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setSceneRect(0,0,MAP_SIZE_L, MAP_SIZE_W);
    ui->graphicsView->show();

    /* Pause & Resume
     * ***************** */
    pau = ui->menuBar->addAction("Pause");
    pau->setVisible(true);
    res = ui->menuBar->addAction("Resume");
    res->setVisible(false);
    connect(pau, SIGNAL(triggered()), this, SLOT(game_pause()));
    connect(res, SIGNAL(triggered()), this, SLOT(game_resume()));

    /* Timer
     * ***************** */
    update_time = new QTimer;
    connect(update_time, SIGNAL(timeout()), this, SLOT(refresh_game_map()));
    update_time->start(ONE_TIK_TIME);

    /* Mouse
     * ***************** */
    ui->graphicsView->setMouseTracking(true);
    connect(ui->graphicsView, &ClickableView::mouseClicked, this, &Mainwindow::map_clicked));

    /* Game Prepare
     * ***************** */
    init();
    game_pause();
}

MainWindow::~MainWindow()
{
    delete pau;
    delete res;
    delete update_time;
    delete ui;
}

void MainWindow::refresh_game_map(){
    static int count = 0;
    //qDebug() << "gamemap refreshed" <<QString::number(count++);
    move_objects();
}

void MainWindow::map_clicked(const double &x, const double &y){
    qDebug() << "mouse clicked" << QString::number(x) << QString::number(y);
    arrow.set_target(x,y);
}

void MainWindow::game_pause(){
    update_time->stop();
    pau->setVisible(false);
    res->setVisible(true);
}

void MainWindow::game_resume(){
    update_time->start(ONE_TIK_TIME);
    pau->setVisible(true);
    res->setVisible(false);
}
