#include <QDebug>

#include "boom.h"
#include "constants.h"

Boom::Boom(QGraphicsScene* scene, const double &x, const double &y)
    : Object(x, y, INITIAL_BOOM_SIZE){
    if(scene != nullptr) add_scene(scene);
}

Boom::Boom(const Boom& gblt) : Object(gblt), item(nullptr), num(gblt.num) {
    if(gblt.item != nullptr) add_scene(gblt.item->scene());
}

Boom::~Boom(){
    if(item != nullptr){
        QGraphicsScene *scene = item->scene();
        if(scene != nullptr)    scene->removeItem(item);
    }
    delete item;
}

void Boom::reset_v(){}

void Boom::add_scene(QGraphicsScene *scene) {
    item = new QGraphicsEllipseItem;
    scene->addItem(item);
    //item->setRect(0, 0, INITIAL_REDPOINT_SIZE * 2, INITIAL_REDPOINT_SIZE * 2);
    item->setVisible(true);
    set_item_position();
}

void Boom::set_item_position(){
    const double &x = getp().getx(), &y = getp().gety(), &r = getr();
    item->setPos(x - r, y - r);
    item->setRect(0, 0, r*2, r*2);
    item->setZValue(num);
    item->setBrush(QBrush(BOOM_COLOR));
}

void Boom::move_one_tick(){
    const double r = getr();
    qDebug() << "opop: " << sig;
    Object::getc().reset(r + BOOM_R_CHANGE_SPEED * sig);
    set_item_position();
    if(sig == 0) {
        times += ONE_TIK_TIME;
        if(times >= BOOM_TIME) change_sig();
    }
    qDebug() << "successfully set pos";
}

void Boom::set_color(const int &red, const int &green, const int &blue){
    if(item == nullptr || item->scene() == nullptr) return ;
    item->setBrush(QBrush(QColor(red,green,blue)));
}

void Boom::set_Zvalue(const int &z){
    if(item == nullptr || item->scene() == nullptr) return ;
    item->setZValue(z);
}

void Boom::change_sig() {
    --sig;
}

bool Boom::squeezing() {
    return sig < 0;
}

bool Boom::holding() {
    return times < BOOM_TIME;
}

void Boom::hold() {
    times = 0;
}
