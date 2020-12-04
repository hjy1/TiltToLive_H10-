#include <QDebug>

#include "swirl.h"
#include "constants.h"

Swirl::Swirl(QGraphicsScene* scene, const double &x, const double &y)
    : Object(x, y, INITIAL_Swirl_SIZE){
    if(scene != nullptr) add_scene(scene);
}

Swirl::Swirl(const Swirl& gblt) : Object(gblt), item(nullptr), num(gblt.num) {
    if(gblt.item != nullptr) add_scene(gblt.item->scene());
}

Swirl::~Swirl(){
    if(item != nullptr){
        QGraphicsScene *scene = item->scene();
        if(scene != nullptr)    scene->removeItem(item);
    }
    delete item;
}

void Swirl::reset_v(){}

void Swirl::add_scene(QGraphicsScene *scene) {
    item = new QGraphicsEllipseItem;
    scene->addItem(item);
    //item->setRect(0, 0, INITIAL_REDPOINT_SIZE * 2, INITIAL_REDPOINT_SIZE * 2);
    item->setVisible(true);
    set_item_position();
}

void Swirl::set_item_position(){
    const double &x = getp().getx(), &y = getp().gety(), &r = getr();
    item->setPos(x - r, y - r);
    item->setRect(0, 0, r*2, r*2);
    item->setZValue(num);
    item->setBrush(QBrush(Swirl_COLOR));
}

void Swirl::move_one_tick(){
    const double r = getr();
    qDebug() << "opop: " << sig;
    Object::getc().reset(r + Swirl_R_CHANGE_SPEED * sig);
    set_item_position();
    if(sig == 0) {
        times += ONE_TIK_TIME;
        if(times >= Swirl_TIME) change_sig();
    }
    qDebug() << "successfully set pos";
}

void Swirl::set_color(const int &red, const int &green, const int &blue){
    if(item == nullptr || item->scene() == nullptr) return ;
    item->setBrush(QBrush(QColor(red,green,blue)));
}

void Swirl::set_Zvalue(const int &z){
    if(item == nullptr || item->scene() == nullptr) return ;
    item->setZValue(z);
}

void Swirl::change_sig() {
    --sig;
}

bool Swirl::squeezing() {
    return sig < 0;
}

bool Swirl::holding() {
    return times < Swirl_TIME;
}

void Swirl::hold() {
    times = 0;
}
