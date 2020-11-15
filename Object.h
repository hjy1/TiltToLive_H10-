#ifndef OBJECT_H
#define OBJECT_H

#include "Circle.h"
#include "Vector.h"

class Object{
	Circle c;
	Vector v;

	public:
	Object(const double &x, const double &y, const double &r);

	Circle& getc();		const Circle& getc() const;
	Vector& getv();		const Vector& getv() const;

	virtual void reset_v();
	void move_one_tik();
};

#endif