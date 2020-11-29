#ifndef OBJECT_H
#define OBJECT_H

#include "circle.h"
#include "vector.h"
#include <QGraphicsItem>
#include <QGraphicsScene>

class Object{
protected:
	Circle c;
    Vector v;
    virtual void reset_v();

public:
    Object(const double &x, const double &y, const double &r);

    /* create a object with a random position in gamemap:
     * r < x < MAP_SIZE_L - r, r < y < MAP_SIZE_W - r
     * **************************** */
    Object(const double &r);

    virtual ~Object();

	Circle& getc();		const Circle& getc() const;
	Vector& getv();		const Vector& getv() const;
						const Vector& getp() const;
						const double& getr() const;


    virtual void move_one_tick();
    virtual void add_scene(QGraphicsScene *scene) = 0;


	friend double get_distance(const Object &o1, const Object &o2);
	friend bool check_overlap(const Object &o1,const Object &o2);

};

#endif
