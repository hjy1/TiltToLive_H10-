#include "tool.h"
#include "constants.h"

#include <cmath>
#include <QDebug>
#include <QGraphicsScene>

inline double get_rand(const double &mn, const double &mx){
    return mn + qrand() * 1.0 / RAND_MAX * (mx - mn);
}

Tool::Tool(const double &x, const double &y,QGraphicsScene* scene, const Object* const arrow):
    Object(x,y,TOOL_SIZE), arrow_ptr(arrow), item(nullptr)	{
    
    int random_number = qrand() % TYPENUM;
        
    toolType = static_cast<ToolType>(random_number);
    qDebug() << "ToolType: " << random_number;
        
    if(scene != nullptr)    add_scene(scene);
    get_initial_v();
}

Tool::Tool(const Tool &rdpt):
    Object(rdpt), arrow_ptr(rdpt.arrow_ptr), item(nullptr), toolType(rdpt.toolType), rotate_angle(rdpt.rotate_angle)
{
    if(rdpt.item != nullptr)    add_scene(rdpt.item->scene());
}

Tool::Tool(QGraphicsScene *scene, const Object * const &arrow):
    Object(TOOL_SIZE), arrow_ptr(arrow), item(nullptr)
{
    int random_number = qrand() % TYPENUM;
    toolType = static_cast<ToolType>(random_number);
    qDebug() << "ToolType: " << random_number;
    if(scene != nullptr)    add_scene(scene);
    get_initial_v();
}

Tool::~Tool(){
    if(item != nullptr){
        QGraphicsScene *scene = item->scene();
        if(scene != nullptr)    scene->removeItem(item);
    }
    delete item;
}

void Tool::get_initial_v()
{
    const double r = getr();
    Vector random_vector(get_rand(r, MAP_SIZE_L - r), get_rand(r, MAP_SIZE_W - r));
    v = random_vector.set_lenth(TOOL_SPEED);
}

void Tool::reset_v()
{
    if(arrow_ptr != nullptr){
        if( arrow_reached() )
        {
            qDebug() << "Get a Tool!";
            v.reset_xy(0,0);
            operation();
            return;
        }
        //if it hits the wall, then bounce back according to physical equation
        const double r = getr();
        const double x = getc().getp().getx(); const double y = getc().getp().gety();
        const double v_x = getv().getx(); const double v_y = getv().gety();
        if( x <= r || x >= MAP_SIZE_L - r){
        Vector v_new( -v_x, v_y );
        v = v_new.set_lenth(TOOL_SPEED);
        }
        if( y <= r || y >= MAP_SIZE_W - r){
          Vector v_new( v_x, -v_y );
          v = v_new.set_lenth(TOOL_SPEED);
        }
    }
    else {
        v.reset_xy(0,0);
    }
}

bool Tool::arrow_reached() const{
    return check_touched(*this, *arrow_ptr);
}

void Tool::add_scene(QGraphicsScene *scene){
    item = new QGraphicsEllipseItem;

    QGraphicsPixmapItem *nitem = new QGraphicsPixmapItem(item);
    int index = static_cast<int>(toolType);
    QPixmap image(tool_image_lookup[index]);
    nitem->setPixmap(image.scaled(TOOL_SIZE * 1.5, TOOL_SIZE * 1.5));
    nitem->setPos(TOOL_SIZE * 0.25, TOOL_SIZE * 0.25);

    item->setBrush(QBrush(QColor(255,255,255)));
    item->setVisible(true);
    scene->addItem(item);
    item->setRect(0, 0, TOOL_SIZE * 2, TOOL_SIZE * 2);
    item->setTransformOriginPoint(TOOL_SIZE, TOOL_SIZE);
    item->setZValue(5000);
    set_item_position();
}

void Tool::set_item_position(){
    const double &x = getp().getx(), &y = getp().gety(), &r = getr();
    item->setPos(x - r, y - r);
    rotate();
}

void Tool::rotate()
{
    rotate_angle += 1.8;
    item->setRotation(rotate_angle);
}

void Tool::clock_change() { time_count += ONE_TIK_TIME; }
int Tool::get_time() const { return time_count; }

Tool::ToolType Tool::operation()
{
    return toolType;
}

void Tool::move_one_tick(){
    Object::move_one_tick();
    set_item_position();
}

