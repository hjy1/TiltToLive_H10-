#ifndef SWIRL_H
#define SWIRL_H

#include "object.h"
#include "constants.h"

class Swirl : public Object
{
    QGraphicsEllipseItem* item;
    const int num = 2;
    int sig = 1;
    double times = Swirl_TIME;

    void set_item_position();
public:
    Swirl(const double &x, const double &y, QGraphicsScene* scene = nullptr);
    Swirl(const Swirl& gblt);
    ~Swirl();
    void reset_v();
    void add_scene(QGraphicsScene* scene);
    void move_one_tick();
    void set_color(const int &red, const int &green, const int &blue);
    void set_Zvalue(const int &z);
    void change_sig();
    void hold();
    bool squeezing()const;
    bool holding()const;

};

#endif // SWIRL_H
