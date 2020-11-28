#include "Vector.h"

#include<cmath>
#include<algorithm>
#include<constants.h>

using std::abs;


inline bool is_zero(const double& v)	{return abs(v) < EPSILON;}

Vector::Vector(const double _x, const double _y):
	x(_x), y(_y)	{}

double& Vector::getx()				{return x;}		
const double& Vector::getx() const	{return x;}
double& Vector::gety()				{return y;}
const double& Vector::gety() const	{return y;}

void Vector::reset_xy(const double& _x, const double& _y)	{x = _x; y = _y;}
void Vector::reset_pol(const double& lenth, const double& alpha){
	reset_xy(lenth * cos(alpha), lenth * sin(alpha));
}

double Vector::getlen() const{
	return sqrt(x*x + y*y);
}

Vector operator+(const Vector &v1, const Vector &v2){
	return Vector(v1.x + v2.x, v1.y + v2.y);
}

Vector operator-(const Vector &v1, const Vector &v2){
	return Vector(v1.x - v2.x, v1.y - v2.y);
}

Vector operator*(const Vector &v1, const double &v2){
	return Vector(v1.x * v2, v1.y * v2);
}

Vector operator/(const Vector &v1, const double &v2){
	return Vector(v1.x / v2, v1.y / v2);
}

Vector& Vector::operator+=(const Vector &v1){
    x += v1.x; y += v1.y;	return *this;
}

bool Vector::is_zero() const{
    return getlen() < EPSILON;
}

Vector Vector::set_lenth(const double &len){
    *this = *this / getlen() * len;
    return *this;
}
