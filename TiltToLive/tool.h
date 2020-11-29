#ifndef TOOL_H
#define TOOL_H

#include <cstdlib>
#include "object.h"
#include "constants.h"
#include <time.h>

class Tool: public Object{
private:
    const Object* const arrow_ptr;
    QGraphicsPixmapItem* item;
    enum class ToolType {INVINCE, FRRRZE, SHOOT, BOOM, EXPLOSION, SWIRL, SHOCKWAVE} toolType; //seven tools for now
    double rotate_angle{0};
    const int TYPENUM = 7;
    const QString tool_image_lookup[7] = { ":/resources/tools/invince.jpg",
                                           ":/resources/tools/freeze.jpg",
                                           ":/resources/tools/shoot.jpg",
                                           ":/resources/tools/boom.jpg",
                                           ":/resources/tools/explosion.jpg",
                                           ":/resources/tools/swirl.jpg",
                                           ":/resources/tools/shockwave.jpg",
                                         };

    void set_item_position();

public:
    Tool(const double &x, const double &y, QGraphicsScene* scene = nullptr, const Object* const arrow = nullptr);
    Tool(const Tool &tool);

    /* Create a redpoint on random position in game map
     * will call Object(const double &r);
     * ********************************************** */
    Tool(QGraphicsScene* scene = nullptr, const Object* const &target = nullptr);

    ~Tool();

    void reset_v();
    void add_scene(QGraphicsScene* scene);
    void move_one_tick();
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
