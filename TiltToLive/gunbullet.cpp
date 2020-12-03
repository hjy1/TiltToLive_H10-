#include <QDebug>

#include "gunbullet.h"
#include "constants.h"

Gunbullet::Gunbullet(QGraphicsScene* scene, const double &x, const double &y, const Vector& target)
    : Object(x, y, INITIAL_BULLET_SIZE){
    set_v(target);
    if(scene != nullptr) add_scene(scene);
}

Gunbullet::Gunbullet(const Gunbullet& gblt) : Object(gblt), item(nullptr), num(gblt.num) {
    if(gblt.item != nullptr) add_scene(gblt.item->scene());
}

Gunbullet::~Gunbullet(){
    if(item != nullptr){
        QGraphicsScene *scene = item->scene();
        if(scene != nullptr)    scene->removeItem(item);
    }
    delete item;
}

void Gunbullet::reset_v(){}

void Gunbullet::set_v(const Vector& target) {
    //only set once
    const double v_x = target.getx(); const double v_y = target.gety();
    Vector v_new(v_x, v_y);
    v = v_new.set_lenth(INITIAL_BULLET_SPEED);
}

void Gunbullet::add_scene(QGraphicsScene *scene) {
    item = new QGraphicsEllipseItem;
    scene->addItem(item);
    //item->setRect(0, 0, INITIAL_REDPOINT_SIZE * 2, INITIAL_REDPOINT_SIZE * 2);
    item->setBrush(QBrush(GUNBULLET_COLOR));
    item->setVisible(true);
    set_item_position();
}

void Gunbullet::set_item_position(){
    const double &x = getp().getx(), &y = getp().gety(), &r = getr();
    item->setPos(x - r, y - r);
    item->setRect(0, 0, r*2, r*2);
    item->setZValue(num);
}

void Gunbullet::move_one_tick(){
    qDebug() << "successfully in";
    Object::move_one_tick();
    qDebug() << "successfully moved";
    qDebug() << MAP_SIZE_L << " " << MAP_SIZE_W;
    qDebug() << getp().getx() << " " << getp().gety();
    if(!touch_wall()) {
        qDebug() << "why?";
        set_item_position();
    }

    qDebug() << "successfully set pos";
}

void Gunbullet::set_color(const int &red, const int &green, const int &blue){
    if(item == nullptr || item->scene() == nullptr) return ;
    item->setBrush(QBrush(QColor(red,green,blue)));
}

void Gunbullet::set_Zvalue(const int &z){
    if(item == nullptr || item->scene() == nullptr) return ;
    item->setZValue(z);
}

bool Gunbullet::touch_wall() {
    const double r = getr();
    const double x = getp().getx(); const double y = getp().gety();
    if( x <= r || x >= MAP_SIZE_L - r || y <= r || y >= MAP_SIZE_W - r)
        return true;
    return false;
}
