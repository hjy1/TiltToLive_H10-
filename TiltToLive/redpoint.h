#ifndef REDPOINT_H
#define REDPOINT_H

#include "object.h"

class Redpoint: public Object{
private:
	const Object* const target;
    QGraphicsEllipseItem* item;

public:
    Redpoint(const double &x, const double &y, QGraphicsScene* scene = nullptr, const Object* const &target = nullptr);
    Redpoint(const Redpoint &rdpt);
    ~Redpoint();

    void reset_v();
    void add_scene(QGraphicsScene* scene);
    void move_one_tick();
    void set_item_position();

	void merge(const Redpoint& rp2);
};

#endif
