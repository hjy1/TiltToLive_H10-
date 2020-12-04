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
    Vector del = target - c.getp();
    if(del.is_zero()) {
        v.reset_xy(0.0,0.0);
        return ;
    }
    else if(del.getlen() < ARROW_SPEED * ONE_TIK_TIME / 1000)    v = del / ONE_TIK_TIME * 1000;
    else v = del.set_lenth(ARROW_SPEED);
    pre_v = v;
}

void Arrow::set_target(const double &x, const double &y){
    target.reset_xy(x,y);
}
void Arrow::set_target(const Vector &x){
    target = x;
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
    if(getp().getx() < getr()){
        getc().getp().getx() = getr();
        target.getx() = getr();
    }
    else if(getp().getx() > MAP_SIZE_L - getr()){
        getc().getp().getx() = MAP_SIZE_L - getr();
        target.getx() = MAP_SIZE_L - getr();
    }
    if(getp().gety() < getr()){
        getc().getp().gety() = getr();
        target.gety() = getr();
    }
    else if(getp().gety() > MAP_SIZE_W - getr()){
        getc().getp().gety() = MAP_SIZE_W - getr();
        target.gety() = MAP_SIZE_W - getr();
    }

    set_item_position();
}

Vector Arrow::get_prev() {
    return pre_v;
}

void Arrow::set_color(const int &red, const int &green, const int &blue){
    if(item == nullptr || item->scene() == nullptr) return ;
    item->setBrush(QBrush(QColor(red,green,blue)));
}
