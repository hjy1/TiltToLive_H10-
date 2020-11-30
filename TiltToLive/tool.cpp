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
    const int r = getr();
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
        const int r = getr();
        const int x = getc().getp().getx(); const int y = getc().getp().gety();
        const int v_x = getv().getx(); const int v_y = getv().gety();
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
    return check_overlap(*this, *arrow_ptr);
}

void Tool::add_scene(QGraphicsScene *scene){
    item = new QGraphicsPixmapItem;
    scene->addItem(item);
    //item->setRect(0, 0, INITIAL_REDPOINT_SIZE * 2, INITIAL_REDPOINT_SIZE * 2);
    int index = static_cast<int>(toolType);
    QPixmap image(tool_image_lookup[index]);
    item->setPixmap(image.scaled(2*TOOL_SIZE, 2*TOOL_SIZE));
    item->setVisible(true);
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

void Tool::operation()
{
    switch(toolType){
     case ToolType::INVINCE: invince(); break;
     case ToolType::FREEZE:  freeze();  break;
     case ToolType::SHOOT:   shoot();   break;
     case ToolType::BOOM:    boom();    break;
     case ToolType::EXPLOSION:explosion(); break;
     case ToolType::SWIRL:   swirl();   break;
     case ToolType::SHOCKWAVE:shockwave(); break;
    }
}

void Tool::invince(){}

void Tool::freeze(){}

void Tool::shoot(){}

void Tool::boom(){}

void Tool::explosion(){}

void Tool::swirl(){}

void Tool::shockwave(){}

void Tool::move_one_tick(){
    Object::move_one_tick();
    set_item_position();
}

