#include "arrow.h"
#include "constants.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QDebug>
#include <QString>

Arrow::Arrow(const double &x, const double &y, QGraphicsScene* scene):
    Object(x, y, ARROW_SIZE), target(x,y), item(nullptr)
{
    if(scene != nullptr)   add_scene(scene);
}

Arrow::Arrow(const Arrow &arrow):
    Object(arrow), item(nullptr)
{
    if(arrow.item != nullptr)
        add_scene(arrow.item->scene());
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
    item->setRect(0, 0, ARROW_SIZE * 2, ARROW_SIZE * 2);
    item->setBrush(QBrush(ARROW_COLOR));
    item->setVisible(true);
    set_item_position();
    item->setZValue(1000000);
}

void Arrow::set_item_position(){
    const double &x = getp().getx(), &y = getp().gety(), &r = getr();
    item->setPos(x - r, y - r);
}

void Arrow::move_one_tick(){
    Object::move_one_tick();
    set_item_position();
}
