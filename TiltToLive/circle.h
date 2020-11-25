#ifndef CIRCLE_H
#define CIRCLE_H

#include "Vector.h"

class Circle{
	Vector p;
	double r;

	public:
	Circle(const double &_x, const double &_y, const double &_r);
	Circle(const Vector &_p, const double &_r);
	Circle(): Circle(0,0,0)	{}

	Vector& getp();		const Vector& getp() const;
	double& getr();		const double& getr() const;

	void reset(const double &_x, const double &_y, const double &_r);
	void reset(const Vector &_p, const double &_r);
	void move(const double &deltax, const double &deltay);
	void move(const Vector &deltap);

	friend double get_distance(const Circle& c1, const Circle& c2);
	friend bool check_overlap(const Circle& c1, const Circle& c2);
};

#endif
