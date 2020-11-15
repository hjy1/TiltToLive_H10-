#ifndef CIRCLE_H
#define CIRCLE_H

class Circle{
	double x,y,r;

	public:
	Circle(const double &_x = 0, const double &_y = 0, const double &_r = 0);

	double& getx();		const double& getx() const;
	double& gety();		const double& gety() const;
	double& getr();		const double& getr() const;

	void reset(double _x, double _y, double _r);
	void move(double deltax, double deltay);

	friend double get_distance(const Circle& c1, const Circle& c2);
	friend bool check_overlap(const Circle& c1, const Circle& c2);
};

#endif