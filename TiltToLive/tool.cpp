#include "tool.h"
#include "constants.h"

#include <cmath>
#include <QDebug>
#include <QGraphicsScene>

inline double get_rand(const double &mn, const double &mx){
    return mn + qrand() * 1.0 / RAND_MAX * (mx - mn);
}

Tool::Tool(const double &x, const double &y,QGraphicsScene* scene, const Object* const arrow):
    Object(x,y,INITIAL_REDPOINT_SIZE), arrow_ptr(arrow), item(nullptr)	{
    if(scene != nullptr)    add_scene(scene);
    srand(time(NULL));
    int random_number = rand() % TYPENUM;
    toolType = static_cast<ToolType>(random_number);
    qDebug() << "ToolType: " << random_number;
}

Tool::Tool(const Tool &rdpt):
    Object(rdpt), arrow_ptr(rdpt.arrow_ptr), item(nullptr), toolType(rdpt.toolType), rotate_angle(rdpt.rotate_angle)
{
    if(rdpt.item != nullptr)    add_scene(rdpt.item->scene());
}

Tool::~Tool(){
    if(item != nullptr){
        QGraphicsScene *scene = item->scene();
        if(scene != nullptr)    scene->removeItem(item);
    }
    delete item;
}

void Tool::reset_v()
{
    if(arrow_ptr != nullptr){
        if(check_overlap(*this, *arrow_ptr))
        {
            qDebug() << "Get a Tool!";
            v.reset_xy(0,0);
            operation();
            return ;
        }
        //give it a virtual target and change its direction
        Vector random_vector(get_rand(c.getr(), MAP_SIZE_L - c.getr()), get_rand(c.getr(), MAP_SIZE_W - c.getr()) );
        Vector deltap = random_vector - this->getp();
        v = deltap.set_lenth(REDPOINT_SPEED_MAX * 0.5);
    }
    else {
        v.reset_xy(0,0);
    }

}

void Tool::add_scene(QGraphicsScene *scene){
    item = new QGraphicsPixmapItem;
    scene->addItem(item);
    //item->setRect(0, 0, INITIAL_REDPOINT_SIZE * 2, INITIAL_REDPOINT_SIZE * 2);
    int index = static_cast<int>(toolType);
    QPixmap image(tool_image_lookup[index]);
    item->setPixmap(image.scaled(INITIAL_REDPOINT_SIZE, INITIAL_REDPOINT_SIZE));
    item->setVisible(true);
    set_item_position();
}

void Tool::set_item_position(){
    const double &x = getp().getx(), &y = getp().gety(), &r = getr();
    item->setPos(x - r, y - r);
    rotate();
}


void Tool::rotate()
{
    rotate_angle += 3.6;
    item->setRotation(rotate_angle);
}

void Tool::operation()
{
    switch(toolType){
     case ToolType::INVINCE: invince(); break;
     case ToolType::FRRRZE:  freeze();  break;
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

