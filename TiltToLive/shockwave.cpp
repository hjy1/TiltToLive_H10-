#include "shockwave.h"
#include "constants.h"
#include <QDebug>

ShockWave::ShockWave(const double &x, const double &y, QGraphicsScene* scene):
    Object (x,y,ARROW_SIZE*2),to_be_destroyed(false)
{
    if(scene != nullptr)    add_scene(scene);
}
ShockWave::ShockWave(const ShockWave &x):
    Object (x), to_be_destroyed(false)
{
    if(x.item != nullptr)   add_scene(x.item->scene());
}

ShockWave::~ShockWave(){
    if(item != nullptr){
        QGraphicsScene *scene = item->scene();
        if(scene != nullptr)    scene->removeItem(item);
    }
    delete item;
}

void ShockWave::add_scene(QGraphicsScene *scene){
    item = new AnnulusItem(0, 0, getr() * 2, getr() * 2, WAVELENTH);
    scene->addItem(item);
    item->setZValue(200);
    item->setBrush(QBrush(WAVE_COLOR));
    item->setVisible(true);
    set_item_position();
}

void ShockWave::set_item_position(){
    item->setRect(0,0, getr() * 2, getr() * 2);
    item->setPos(getp().getx() - getr(), getp().gety() - getr());
}

void ShockWave::move_one_tick(){
    this->getc().getr() += WAVESPEED * ONE_TIK_TIME / 1000;
    Vector v1(0, 0), v2(MAP_SIZE_L,0), v3(0, MAP_SIZE_W), v4(MAP_SIZE_L, MAP_SIZE_W);
    const Vector &c = getc().getp();
    using namespace std;
    double mxdis = max( max( (c - v1).getlen(), (c - v2).getlen() ) , max( (c - v3).getlen(), (c - v4).getlen() ) );
    if(getr() - WAVELENTH > mxdis){
        to_be_destroyed = true;
    }
    else set_item_position();
}
