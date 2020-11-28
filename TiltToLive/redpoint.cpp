#include "Redpoint.h"
#include "Constants.h"

#include <cmath>
#include <QDebug>
#include <QGraphicsScene>

Redpoint::Redpoint(const double &x, const double &y,QGraphicsScene* scene, const Object* const &target):
    Object(x,y,INITIAL_REDPOINT_SIZE), target(target), item(nullptr)	{
    if(scene != nullptr)    add_scene(scene);
}

Redpoint::Redpoint(const Redpoint &rdpt):
    Object(rdpt), target(rdpt.target), item(nullptr)
{
    if(rdpt.item != nullptr)    add_scene(rdpt.item->scene());
}

Redpoint::~Redpoint(){
    if(item != nullptr){
        QGraphicsScene *scene = item->scene();
        if(scene != nullptr)    scene->removeItem(item);
    }
    delete item;
}

void Redpoint::reset_v()
{
	if(target != nullptr)
	{
        if(check_overlap(*this, *target))
        {
            qDebug() << "OVERLAP!";
            v.reset_xy(0,0);
            return ;
        }
		Vector deltap = target->getp() - this->getp();
        v = deltap.set_lenth(REDPOINT_SPEED_MAX);
	}
    else {
        v.reset_xy(0,0);
    }
}

void Redpoint::merge(const Redpoint &p){
    c.getr() = sqrt(this->getr() * this->getr() + p.getr() * p.getr());
}

void Redpoint::add_scene(QGraphicsScene *scene){
    item = new QGraphicsEllipseItem;
    scene->addItem(item);
    //item->setRect(0, 0, INITIAL_REDPOINT_SIZE * 2, INITIAL_REDPOINT_SIZE * 2);
    item->setBrush(QBrush(QColor(100, 0, 0)));
    item->setVisible(true);
    set_item_position();
}

void Redpoint::set_item_position(){
    const double &x = getp().getx(), &y = getp().gety(), &r = getr();
    item->setPos(y - r, x - r);
    item->setRect(0, 0, r*2, r*2);
}

void Redpoint::move_one_tick(){
    Object::move_one_tick();
    set_item_position();
}
