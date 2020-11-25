#include "Redpoint.h"
#include "Constants.h"

#include <cmath>

Redpoint::Redpoint(const double &x, const double &y, const Object* const &target):
	Object(x,y,INITIAL_REDPOINT_SIZE), target(target)	{}

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