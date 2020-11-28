#include "Redpoint.h"
#include "Constants.h"

#include <cmath>
#include <QDebug>
#include <QGraphicsScene>

Redpoint::Redpoint(const double &x, const double &y,QGraphicsScene* scene, const Object* const &target):
    Object(x,y,INITIAL_REDPOINT_SIZE), target(target), item(nullptr), num(1)	{
    if(scene != nullptr)    add_scene(scene);
}

Redpoint::Redpoint(QGraphicsScene *scene, const Object* const &target):
    Object(INITIAL_REDPOINT_SIZE), target(target), item(nullptr), num(1)  {
    if(scene != nullptr)    add_scene(scene);
}

Redpoint::Redpoint(const Redpoint &rdpt):
    Object(rdpt), target(rdpt.target), item(nullptr), num(rdpt.num)
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

double get_suitable_v(const double &crtv, const double &dis){
    //v <= min_v -> return min_v
    if(crtv < REDPOINT_SPEED_MIN){
        return REDPOINT_SPEED_MIN;
    }
    // v^2 - min_v^2 <= 2*a*dis -> return v - at;
    if(crtv * crtv - REDPOINT_SPEED_MIN * REDPOINT_SPEED_MIN >= 2 * REDPOINT_DECCELERATION * dis){
        return crtv - ONE_TIK_TIME / 1000.0 * REDPOINT_DECCELERATION;
    }
    //v >= max_v -> return max_v
    if(REDPOINT_SPEED_MAX - crtv <= EPSILON){
        return REDPOINT_SPEED_MAX;
    }
    //return v+at
    return crtv + ONE_TIK_TIME / 1000.0 * REDPOINT_ACCELERATION;
}

void Redpoint::reset_v()
{
	if(target != nullptr)
    {
        Vector deltap = target->getp() - this->getp();
        if(deltap.is_zero())    v.reset_xy(0,0);
        else {
            double vlen = get_suitable_v(v.getlen(), deltap.getlen() - getr() - target->getr() - SAFE_TIME / 1000 * REDPOINT_SPEED_MIN);
            //qDebug() << NUM(vlen);
            v = deltap.set_lenth(vlen);
        }
	}
    else {
        v.reset_xy(0,0);
    }
}

bool Redpoint::target_reached() const{
    return check_overlap(*this, *target);
}

void Redpoint::merge(const Redpoint &p){
    //x1,y1,m1 x2,y2,m2    l1 = m2/(m1+m2)*(x2-x1) x' = l1+x1 = x2*m2/(m1+m2) + x1*m1/(m1+m2)
    double m1 = this->getr() * this->getr(), m2 = p.getr() * p.getr();
    c.getp().getx() = getp().getx() * m1 / (m1+m2) + p.getp().getx() * m2 / (m1+m2);
    c.getp().gety() = getp().gety() * m1 / (m1+m2) + p.getp().gety() * m2 / (m1+m2);
    c.getr() = sqrt(m1 + m2);
    num += p.num;
}

void Redpoint::add_scene(QGraphicsScene *scene){
    item = new QGraphicsEllipseItem;
    scene->addItem(item);
    //item->setRect(0, 0, INITIAL_REDPOINT_SIZE * 2, INITIAL_REDPOINT_SIZE * 2);
    item->setBrush(QBrush(REDPOINT_COLOR));
    item->setVisible(true);
    set_item_position();
}

void Redpoint::set_item_position(){
    const double &x = getp().getx(), &y = getp().gety(), &r = getr();
    item->setPos(y - r, x - r);
    item->setRect(0, 0, r*2, r*2);
    item->setZValue(num);
}

void Redpoint::move_one_tick(){
    Object::move_one_tick();
    set_item_position();
}

void Redpoint::set_color(const int &red, const int &green, const int &blue){
    if(item == nullptr || item->scene() == nullptr) return ;
    item->setBrush(QBrush(QColor(red,green,blue)));
}

void Redpoint::set_Zvalue(const int &z){
    if(item == nullptr || item->scene() == nullptr) return ;
    item->setZValue(z);
}
