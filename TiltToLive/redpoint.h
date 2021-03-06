#ifndef REDPOINT_H
#define REDPOINT_H

#include "object.h"
#include "constants.h"

class Redpoint: public Object{
private:
    const Vector* target;
    QGraphicsEllipseItem* item;
    int num;
    bool freeze = false;
    bool reversed = false;
    void set_item_position();

public:
    Redpoint(const double &x, const double &y, QGraphicsScene* scene = nullptr, const Vector* target = nullptr);
    Redpoint(const Redpoint &rdpt);

    /* Create a redpoint on random position in game map
     * will call Object(const double &r);
     * ********************************************** */
    Redpoint(QGraphicsScene* scene = nullptr, const Vector *target = nullptr);

    ~Redpoint();

    void reset_v();
    void add_scene(QGraphicsScene* scene);
    void move_one_tick();
    bool target_reached() const;
    void merge(const Redpoint& rp2);
    void set_color(const int &red, const int &green, const int &blue);
    void set_Zvalue(const int &z);
    void set_target(const Vector* tar);
    void set_freeze();
    void un_freeze();
};

#endif
