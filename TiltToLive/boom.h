#ifndef BOOM_H
#define BOOM_H

#include "object.h"
#include "constants.h"

class Boom : public Object
{
    QGraphicsEllipseItem* item;
    const int num = 1000;
    int sig = 1;
    //double times = BOOM_TIME;

    void set_item_position();
public:
    Boom(const double &x, const double &y, QGraphicsScene* scene);
    Boom(const Boom& gblt);
    ~Boom();
    void reset_v();
    void add_scene(QGraphicsScene* scene);
    void move_one_tick();
    void set_color(const int &red, const int &green, const int &blue);
    void set_Zvalue(const int &z);
    void change_sig();
    void hold();
    bool squeezing();
    bool holding();
    void set_visible();
    void set_invisible();

    bool to_be_destroyed;

};

#endif // BOOM_H
