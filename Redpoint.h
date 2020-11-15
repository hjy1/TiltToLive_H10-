#include "Object.h"

class Redpoint: public Object{
	const Object* const target;

	public:
	Redpoint(const double &x, const double &y, const Object* const &target = nullptr);

	void reset_v() final;
};