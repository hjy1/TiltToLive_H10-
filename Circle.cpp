#include "Circle.h"
#include <cmath>
#include <algorithm>

Circle::Circle(const double &_x, const double &_y, const double &_r):
	x(_x), y(_y), r(_r)	{}

double& Circle::getx()				{return x;}		
const double& Circle::getx() const	{return x;}
double& Circle::gety()				{return y;}
const double& Circle::gety() const	{return y;}
double& Circle::getr()				{return r;}
const double& Circle::getr() const	{return r;}

void Circle::reset(double _x, double _y, double _r)		{x = _x, y = _y, r = _r;}
void Circle::move(double deltax, double deltay)			{x += deltax, y += deltay;}

double get_distance(const Circle& c1, const Circle& c2)
{
	double dx = c1.x - c2.x, dy = c1.y - c2.y;
	return sqrt(dx*dx + dy*dy);
}

bool check_overlap(const Circle& c1, const Circle& c2)
{
	double dis = get_distance(c1,c2);
	return std::max(c1.r, c2.r) > dis;
}