#include "Vector.h"

#include<cmath>
#include<algorithm>

using std::abs;

const double EPSILON = 0.0000001;
inline bool is_zero(const double& v)	{return abs(v) < EPSILON;}

Vector::Vector(const double _x, const double _y):
	x(_x), y(_y)	{}

double& Vector::getx()				{return x;}		
const double& Vector::getx() const	{return x;}
double& Vector::gety()				{return y;}
const double& Vector::gety() const	{return y;}

void Vector::reset_xy(const double& _x, const double& _y)	{x = _x, y = _y;}
void Vector::reset_pol(const double& lenth, const double& alpha){
	reset_xy(lenth * cos(alpha), lenth * sin(alpha));
}
