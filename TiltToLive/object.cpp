#include "object.h"
#include "constants.h"

inline double get_rand(const double &mn, const double &mx){
    return mn + qrand() * 1.0 / RAND_MAX * (mx - mn);
}

Object::Object(const double &x, const double &y, const double &r):
    c(x,y,r), v(0,0)    {}
Object::Object(const double &r):
    c(get_rand(r, MAP_SIZE_L - r), get_rand(r, MAP_SIZE_W - r), r), v(0, 0) {}

Object::~Object()   {}

Circle& Object::getc()				{return c;}		
const Circle& Object::getc() const	{return c;}
Vector& Object::getv()				{return v;}	
const Vector& Object::getv() const	{return v;}

const Vector& Object::getp() const	{return c.getp();}
const double& Object::getr() const	{return c.getr();}

void Object::reset_v()	{}
void Object::add_scene(QGraphicsScene *scene)   {}

void Object::move_one_tick(){
	reset_v();
    c.move(v.getx() * ONE_TIK_TIME / 1000, v.gety() * ONE_TIK_TIME / 1000);
}

double get_distance(const Object &o1, const Object &o2)	{	return get_distance(o1.c, o2.c); }

bool check_overlap(const Object &o1, const Object &o2)	{	return check_overlap(o1.c, o2.c);}

bool check_touched(const Object &o1, const Object &o2)  {   return check_touched(o1.c, o2.c);}



