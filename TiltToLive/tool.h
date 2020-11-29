#ifndef TOOL_H
#define TOOL_H

#include <cstdlib>
#include "object.h"
#include "arrow.h"
#include "vector.h"
#include <time.h>

class Tool: public Object{
private:
    const Object* const target;
    QGraphicsPixmapItem* item;
    enum class ToolType {INVINCE, FRRRZE, SHOOT, BOOM, EXPLOSION, SWIRL, SHOCKWAVE} toolType; //seven tools for now
    double rotate_angle{0};
    const int TYPENUM = 7;

public:
    Tool(const double &x, const double &y, QGraphicsScene* scene = nullptr, const Object* const &target = nullptr);
    Tool(const Tool &tool);
    ~Tool();

    void reset_v();
    void add_scene(QGraphicsScene* scene);
    void move_one_tick();
    void set_item_position();
    void rotate();

    void operation();

    void invince();
    void freeze();
    void shoot();
    void boom();
    void explosion();
    void swirl();
    void shockwave();

};



#endif // TOOL_H
