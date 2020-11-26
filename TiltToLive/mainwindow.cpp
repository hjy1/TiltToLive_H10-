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
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    //ui->graphicsView->fitInView(0, 0, MAP_SIZE_W, MAP_SIZE_L);
    ui->graphicsView->show();

    init();
    act = ui->menuBar->addAction("Close");
    connect(act, SIGNAL(triggered()), this, SLOT(end_game()));

    update_time = new QTimer;
    connect(update_time, SIGNAL(timeout()), this, SLOT(refresh_game_map()));
    update_time->start(ONE_TIK_TIME);
    connect(ui->graphicsView, SIGNAL(ClickableView::mouseClicked()), this, SLOT(map_clicked()));
    //connect(ui->menuClose, SIGNAL(about_to_show()), QApplication, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete act;
    delete update_time;
    delete ui;
}

void MainWindow::refresh_game_map(){
    static int count = 0;
    qDebug() << "gamemap refreshed" <<QString::number(count++);
    move_objects();
}

void MainWindow::map_clicked(const double &x, const double &y){
    qDebug() << "mouse clicked" << QString::number(x) << QString::number(y);
    arrow.set_target(x,y);
}

void MainWindow::end_game(){
    update_time->stop();
    QApplication::quit();
}
