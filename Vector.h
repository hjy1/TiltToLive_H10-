#ifndef VECTOR_H
#define VECTOR_H

class Vector{
	double x,y;
	public:
	Vector(const double _x, const double _y);
	Vector(): Vector(0,0)	{}
	
	double& getx();		const double& getx() const;
	double& gety();		const double& gety() const;

	void reset_xy(const double &_x, const double &_y);
	void reset_pol(const double &lenth, const double &alpha);
};

#endif