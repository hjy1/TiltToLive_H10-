#include "Redpoint.h"
#include "Constants.h"

#include <cmath>

Redpoint::Redpoint(const double &x, const double &y, const Object* const &target):
    Object(x,y,INITIAL_REDPOINT_SIZE), target(target), item(nullptr)	{}
Redpoint::~Redpoint(){
    if(item != nullptr){
        QGraphicsScene *scene = item->scene();
        if(scene != nullptr)    scene->removeItem(item);
        delete item;
    }
}

void Redpoint::reset_v()
{
	if(target != nullptr)
	{
		if(check_overlap(*this, *target))	return ;
		Vector deltap = target->getp() - this->getp();
		v = deltap / deltap.getlen() * v.getlen();
	}
}

void Redpoint::merge(const Redpoint &p){
	c.getr() = sqrt(this->getr() * this->getr() + p.getr() * p.getr());
}


void Redpoint::add_scene(QGraphicsScene *scene){
    item = new QGraphicsEllipseItem;
    scene->addItem(item);
    item->setRect(getp().getx(), getp().gety(), INITIAL_REDPOINT_SIZE, INITIAL_REDPOINT_SIZE);
    item->setVisible(true);
}

void Redpoint::move_one_tick(){
    Object::move_one_tick();
    item->setPos(getp().getx(), getp().gety());
}
