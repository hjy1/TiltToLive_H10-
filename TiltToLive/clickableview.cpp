#include <QMouseEvent>
#include <QDebug>
#include <QString>

#include "clickableview.h"
#include "constants.h"

ClickableView::ClickableView(QWidget *parent):QGraphicsView(parent) {}

void ClickableView::mousePressEvent(QMouseEvent *event) {
    // TODO: take the x, y position, convert to grid index and send the signal mouseClicked to GameWindow
    // NOTE the coordinate system:
    // +----------> x
    // |
    // |
    // |
    // v
    // y
    // Size of the image is 16x16
    // useful docs: https://doc.qt.io/qt-5/qmouseevent.html
    // convert window coordinate to scene coordinate: https://doc.qt.io/qt-5/qgraphicsview.html#mapToScene
    // send signal: emit mouseClicked(int, int);
    QPointF p = QGraphicsView::mapToScene(event->pos());
    //QPoint p = event->pos();
    qDebug() << QString::number(p.x()) << " " << QString::number(p.y()) << '\n';
    emit mouseClicked(p.x(), p.y());
}
