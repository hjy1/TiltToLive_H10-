/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <clickableview.h>

QT_BEGIN_NAMESPACE

class Ui_TiltToLive
{
public:
    QWidget *centralWidget;
    ClickableView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TiltToLive)
    {
        if (TiltToLive->objectName().isEmpty())
            TiltToLive->setObjectName(QStringLiteral("TiltToLive"));
        TiltToLive->resize(378, 770);
        TiltToLive->setMouseTracking(true);
        centralWidget = new QWidget(TiltToLive);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        graphicsView = new ClickableView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 361, 641));
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMouseTracking(true);
        TiltToLive->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TiltToLive);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 378, 21));
        TiltToLive->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TiltToLive);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TiltToLive->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TiltToLive);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TiltToLive->setStatusBar(statusBar);

        retranslateUi(TiltToLive);

        QMetaObject::connectSlotsByName(TiltToLive);
    } // setupUi

    void retranslateUi(QMainWindow *TiltToLive)
    {
        TiltToLive->setWindowTitle(QApplication::translate("TiltToLive", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TiltToLive: public Ui_TiltToLive {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
