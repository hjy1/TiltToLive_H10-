#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Constants.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    update_time = new QTimer;
    connect(update_time, SIGNAL(timeout()), this, SLOT(update_game()));
    update_time->start(ONE_TIK_TIME);
}

MainWindow::~MainWindow()
{
    delete ui;
}
