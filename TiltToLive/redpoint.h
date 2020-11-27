#ifndef REDPOINT_H
#define REDPOINT_H

#include "object.h"

class Redpoint: public Object{
private:
	const Object* const target;
    QGraphicsEllipseItem* item;

public:
    Redpoint(const double &x, const double &y, QGraphicsScene* scene = nullptr, const Object* const &target = nullptr);
    ~Redpoint();

    void reset_v();
    void add_scene(QGraphicsScene* scene);
    void move_one_tick();

	void merge(const Redpoint& rp2);
};

#endif
