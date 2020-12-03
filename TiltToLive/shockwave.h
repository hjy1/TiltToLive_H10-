#ifndef SHOCKWAVE_H
#define SHOCKWAVE_H

#include "object.h"
#include "annulusitem.h"

class ShockWave: public Object
{
public:
    ShockWave(const double &x, const double &y, QGraphicsScene *scene = nullptr);
    ShockWave(const ShockWave &x);
    ~ShockWave();
    void add_scene(QGraphicsScene* scene) override;
    void move_one_tick() override;
    void set_item_position();

    bool to_be_destroyed;

private:
    AnnulusItem *item;
};

#endif // SHOCKWAVE_H
