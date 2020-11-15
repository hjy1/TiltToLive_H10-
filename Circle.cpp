#include "Circle.h"
#include <cmath>
#include <algorithm>

Circle::Circle(const double &_x, const double &_y, const double &_r):
	p(_x,_y), r(_r)	{}
Circle::Circle(const Vector &_p, const double &_r):
	p(_p), r(_r)	{}

Vector& Circle::getp()				{return p;}		
const Vector& Circle::getp() const	{return p;}
double& Circle::getr()				{return r;}
const double& Circle::getr() const	{return r;}

void Circle::reset(const double &_x, const double &_y, const double &_r){
	p.getx() = _x, p.gety() = _y, r = _r;
}
void Circle::reset(const Vector &_p, const double &_r){
	p = _p, r = _r;
}
void Circle::move(const double &deltax, const double &deltay){
	p.getx() += deltax, p.gety() += deltay;
}
void Circle::move(const Vector &deltap){
	p += deltap;
}

double get_distance(const Circle& c1, const Circle& c2)
{
	return (c1.p - c2.p).getlen();
}

bool check_overlap(const Circle& c1, const Circle& c2)
{
	double dis = get_distance(c1,c2);
	return std::max(c1.r, c2.r) > dis;
}