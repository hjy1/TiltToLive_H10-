#include "arrow.h"
#include "constants.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QDebug>
#include <QString>

Arrow::Arrow(const double &x, const double &y, QGraphicsScene* scene):
    Object(x, y, ARROW_SIZE), target(0,0), item(nullptr)
{
    if(scene != nullptr)   add_scene(scene);
}

Arrow::~Arrow(){
    if(item != nullptr){
        QGraphicsScene *scene = item->scene();
        if(scene != nullptr)    scene->removeItem(item);
    }
    delete item;
}

void Arrow::reset_v(){
    v = target - c.getp();
    if(v.is_zero()) v.reset_xy(0.0,0.0);
    else if(v.getlen() < ARROW_SPEED * ONE_TIK_TIME / 1000)    v = v / ONE_TIK_TIME * 1000;
    else v.set_lenth(ARROW_SPEED);
}

void Arrow::set_target(const double &x, const double &y){
    target.reset_xy(x,y);
}

void Arrow::add_scene(QGraphicsScene *scene){
    item = new QGraphicsEllipseItem();
    scene->addItem(item);
    item->setRect(getp().getx(), getp().gety(), ARROW_SIZE, ARROW_SIZE);
    item->setBrush(QBrush(QColor(0, 160, 230)));
    item->setVisible(true);
}

void Arrow::move_one_tick(){
    Object::move_one_tick();
    item->setPos(getp().getx(), getp().gety());
    qDebug() << QString::number(getp().getx()) << QString::number(getp().gety());
}
