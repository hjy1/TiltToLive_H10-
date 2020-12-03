#ifndef GUNBULLET_H
#define GUNBULLET_H

#include "constants.h"
#include "object.h"
#include "arrow.h"
#include "redpoint.h"

class Gunbullet : public Object {
    QGraphicsEllipseItem* item;
    const int num = 2;

    void set_item_position();
public:
    Gunbullet(QGraphicsScene* scene, const double &x, const double &y, const Vector& target);
    Gunbullet(const Gunbullet& gblt);
    ~Gunbullet();
    void reset_v();
    void set_v(const Vector& target);
    void add_scene(QGraphicsScene* scene);
    void move_one_tick();
    void set_color(const int &red, const int &green, const int &blue);
    void set_Zvalue(const int &z);
    bool touch_wall();
};

#endif // GUNBULLET_H
