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
    enum class ToolType {INVINCE, FREEZE, SHOOT, BOOM, EXPLOSION, SWIRL, SHOCKWAVE} toolType; //seven tools for now
    int time_count = 0;
    double rotate_angle = 0;
    static const int TYPENUM;// = 7;
    static const QString tool_image_lookup[];
        /* = {  ":/resources/tools/invince.png",
                ":/resources/tools/freeze.png",
                ":/resources/tools/shoot.png",
                ":/resources/tools/boom.png",
                ":/resources/tools/explosion.png",
                ":/resources/tools/swirl.png",
                ":/resources/tools/shockwave.png"
             };*/

    void set_item_position();

public:
    Tool(const double &x, const double &y, QGraphicsScene* scene = nullptr, const Object* const arrow = nullptr);
    Tool(const Tool &tool);

    /* Create a tool on random position in game map
     * will call Object(const double &r);
     * ********************************************** */
    Tool(QGraphicsScene* scene = nullptr, const Object* const &arrow = nullptr);

    ~Tool();

    void get_initial_v();
    void reset_v();
    void add_scene(QGraphicsScene* scene);
    void move_one_tick();
    void rotate();
    void clock_change();
    int get_time() const;
    bool arrow_reached() const;

    ToolType operation();

};
#endif // TOOL_H
