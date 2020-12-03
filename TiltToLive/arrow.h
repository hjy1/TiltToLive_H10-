#ifndef ARROW_H
#define ARROW_H

#include "object.h"
#include "constants.h"

class Arrow: public Object	{
private:
    Vector target;
    Vector pre_v;
    QGraphicsEllipseItem* item;
    void reset_v();
public:
    Arrow(const double &x, const double &y, QGraphicsScene* scene = nullptr);
    Arrow(const Arrow &arrow);
    ~Arrow();

    void set_target(const double &x, const double &y);
    void set_target(const Vector &x);
    void add_scene(QGraphicsScene* scene);
    void set_item_position();
    void move_one_tick();
    Vector get_prev();
    void set_color(const int &red, const int &green, const int &blue);
};

#endif
