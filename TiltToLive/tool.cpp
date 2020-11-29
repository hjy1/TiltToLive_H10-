#include "tool.h"
#include "constants.h"

#include <cmath>
#include <QDebug>
#include <QGraphicsScene>

Tool::Tool(const double &x, const double &y,QGraphicsScene* scene, const Object* const &target):
    Object(x,y,2*INITIAL_REDPOINT_SIZE), target(target), item(nullptr)	{
    if(scene != nullptr)    add_scene(scene);
    srand(time(NULL));
    int random_number = rand() % TYPENUM;
    toolType = static_cast<ToolType>(random_number);
    qDebug() << "ToolType: " << random_number;
}

Tool::Tool(const Tool &rdpt):
    Object(rdpt), target(rdpt.target), item(nullptr), toolType(rdpt.toolType), rotate_angle(rdpt.rotate_angle)
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
    if(target != nullptr){
        if(check_overlap(*this, *target))
        {
            qDebug() << "Get a Tool!";
            v.reset_xy(0,0);
            operation();
            return ;
        }
        //give it a virtual target and change its direction.
        srand(time(NULL));
        int random_x = rand() % MAP_SIZE_W;
        int random_y = rand() % MAP_SIZE_L;
        Vector random_vector(random_x, random_y);
        Vector deltap = random_vector - this->getp();
        v = deltap.set_lenth(REDPOINT_SPEED_MAX);

    }
    else {
        v.reset_xy(0,0);
    }

}
void Tool::add_scene(QGraphicsScene *scene){
    item = new QGraphicsPixmapItem;
    scene->addItem(item);
    //item->setRect(0, 0, INITIAL_REDPOINT_SIZE * 2, INITIAL_REDPOINT_SIZE * 2);
    QPixmap image(":/images/freeze1.jpeg");
    item->setPixmap(image.scaled(10, 10));
    item->setVisible(true);
    set_item_position();
}

void Tool::set_item_position(){
    const double &x = getp().getx(), &y = getp().gety(), &r = getr();
    item->setPos(y - r, x - r);
    //no need to change the size
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

void Tool::invince()
{


}

void Tool::freeze()
{

}

void Tool::shoot()
{

}

void Tool::boom()
{

}

void Tool::explosion()
{


}

void Tool::swirl()
{

}

void Tool::shockwave()
{

}





void Tool::move_one_tick(){
    Object::move_one_tick();
    set_item_position();
}
