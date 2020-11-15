#include "Object.h"
#include "Constants.h"

Object::Object(const double &x, const double &y, const double &r):
	c(x,y,r), v(0,0)	{}

Circle& Object::getc()				{return c;}		
const Circle& Object::getc() const	{return c;}
Vector& Object::getv()				{return v;}	
const Vector& Object::getv() const	{return v;}

void Object::reset_v()	{}

void Object::move_one_tik(){
	reset_v();
	c.move(v.getx() * ONE_TIK_TIME, v.gety() * ONE_TIK_TIME);
}