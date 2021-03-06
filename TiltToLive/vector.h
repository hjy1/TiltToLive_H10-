#ifndef VECTOR_H
#define VECTOR_H

class Vector{
	double x,y;
	public:
	Vector(const double _x, const double _y);
    Vector(): Vector(0.0,0.0)	{}
	
	double& getx();		const double& getx() const;
	double& gety();		const double& gety() const;

	void reset_xy(const double &_x, const double &_y);
	void reset_pol(const double &lenth, const double &alpha);

	double getlen() const;

	friend Vector operator+(const Vector& v1, const Vector &v2);
	friend Vector operator-(const Vector& v1, const Vector &v2);
	friend Vector operator*(const Vector& v1, const double &v2);
	friend Vector operator/(const Vector& v1, const double &v2);

	Vector& operator+=(const Vector& v1);

    bool is_zero() const;

    //reset the lenth of vector and without changing its direction
    Vector set_lenth(const double &len);
};

#endif
