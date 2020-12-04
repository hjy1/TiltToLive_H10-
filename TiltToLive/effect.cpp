#include <QDebug>

#include "effect.h"
#include "gameengine.h"
#include "object.h"
#include "constants.h"

/* class Effect
 * ********************* */
Effect::Effect(GameEngine* parent):
    parent(parent)  {}
Effect::~Effect()   {}


/* Invince Effect
 * ********************* */
Invince_Effect::Invince_Effect(GameEngine* parent):
    Effect (parent){
    if(parent == nullptr)   return ;
    parent->arrow.set_color(0, 0, 0);
    parent->invince = true;
    time_duration = INVINCE_MAX_TIME;
}
Invince_Effect::~Invince_Effect()   {
    parent->arrow.set_color(ARROW_COLOR.red(), ARROW_COLOR.green(), ARROW_COLOR.blue());
    parent->invince = false;
}
void Invince_Effect::operation() {
    time_duration -= ONE_TIK_TIME;
}

bool Invince_Effect::to_be_destroyed() const {
    return time_duration <= 0;
}

/* Freeze Effect
 * ********************* */
Freeze_Effect::Freeze_Effect(GameEngine* parent):
    Effect (parent){
    if(parent == nullptr)   return ;
    for (auto it = parent->redpoints.begin(); it != parent->redpoints.end(); ++it) {
        (*it).set_freeze();
    }
    parent->freeze = true;
    time_duration = FREEZE_MAX_TIME;
}
Freeze_Effect::~Freeze_Effect()   {
    for (auto it = parent->redpoints.begin(); it != parent->redpoints.end(); ++it) {
        (*it).un_freeze();
    }
    parent->freeze = false;
}
void Freeze_Effect::operation() {
    time_duration -= ONE_TIK_TIME;
}

bool Freeze_Effect::to_be_destroyed() const {
    return time_duration <= 0;
}

/* Shoot_Effect:
 * ******************** */
Shoot_Effect::Shoot_Effect(GameEngine* parent):
    Effect (parent){
    if(parent == nullptr)   return ;
    remain_bullet = INITIAL_BULLET_AMOUNT;
}
Shoot_Effect::~Shoot_Effect()   {
}
void Shoot_Effect::operation() {
    if(remain_bullet > 0) {
        Gunbullet tmp(&parent->scene, parent->arrow.getp().getx(), parent->arrow.getp().gety(), parent->arrow.get_prev());
        gunbullets.push_back(tmp);
    }
    for(list<Gunbullet>::iterator it = gunbullets.begin(); it != gunbullets.end(); ) {
        (*it).move_one_tick();
        if((*it).touch_wall()) {
            it = gunbullets.erase(it);
            --remain_bullet;
            qDebug() << "delete a bullet when it touched the wall";
            continue;
        }
        bool flag = false;
        for (auto j = parent->redpoints.begin(); j != parent->redpoints.end(); ) {
            if(check_touched((*it), (*j))) {
                qDebug() << "delete a redpoint when a bullet hits it";
                j = parent->redpoints.erase(j);
                flag = true;
                continue;
            }
            ++j;
        }
        if(flag) {
            it = gunbullets.erase(it);
            --remain_bullet;
            qDebug() << "delete a bullet when it hits a redpoint";
            continue;
        }
        it++;
    }
}
bool Shoot_Effect::to_be_destroyed() const {
    return gunbullets.empty();
}

/* Explosion_Effect :
 * ************************ */
Explosion_Effect::Explosion_Effect(const double &x, const double &y, GameEngine* parent):
    Effect (parent){
    if(parent == nullptr)   return ;
    static const double dx[12] = {0, 0.5, 0.86602, 1, 0.86602, 0.5, 0,
                                      -0.5, -0.86602, -1, -0.86602, -0.5};
    static const double dy[12] = {-1, -0.86602, -0.5, 0, 0.5, 0.86602, 1,
                                      0.86602, 0.5, 0, -0.5, -0.86602};
    for(int i = 0; i < 12; ++i) {
        Gunbullet tmp(&parent->scene, x, y, Vector(dx[i], dy[i]));
        gunbullets.push_back(tmp);
    }
}
Explosion_Effect::~Explosion_Effect()   {
}
void Explosion_Effect::operation() {

    for(list<Gunbullet>::iterator it = gunbullets.begin(); it != gunbullets.end(); ) {
        (*it).move_one_tick();
        if((*it).touch_wall()) {
            it = gunbullets.erase(it);
            continue;
        }
        bool flag = false;
        for (auto j = parent->redpoints.begin(); j != parent->redpoints.end(); ) {
            if(check_touched((*it), (*j))) {
                j = parent->redpoints.erase(j);
                flag = true;
                continue;
            }
            ++j;
        }
        if(flag) {
            it = gunbullets.erase(it);
            continue;
        }
        it++;
    }
}
bool Explosion_Effect::to_be_destroyed() const {
    return gunbullets.empty();
}

/* Swirl_Effect ：
 * ******************* */
int Swirl_Effect::excisting_effects = 0;
Swirl_Effect::Swirl_Effect(const double &x, const double &y, GameEngine* parent):
    Effect (parent), swirl(x,y){
    if(parent == nullptr)   return ;
    swirl.add_scene(&parent->scene);
    for(auto it = parent->redpoints.begin(); it != parent->redpoints.end(); ++it) {
        (*it).set_target(&swirl.getp());
    }
    excisting_effects ++;
    parent->redpoint_target = &swirl.getc().getp();
}
Swirl_Effect::~Swirl_Effect()   {
    if(parent != nullptr){
        excisting_effects --;
        if(!excisting_effects)
            for(auto it = parent->redpoints.begin(); it != parent->redpoints.end(); ++it) {
                (*it).set_target(&parent->arrow.getp());
            }
        parent->redpoint_target = &parent->arrow.getc().getp();
    }
}
void Swirl_Effect::operation() {
    swirl.move_one_tick();
    if(swirl.getr() >= Swirl_MAX_SIZE && !swirl.holding() && !swirl.squeezing()) {
        swirl.change_sig();
        swirl.hold();
    }
}
bool Swirl_Effect::to_be_destroyed() const {
    return swirl.getr() <= INITIAL_Swirl_SIZE && swirl.squeezing();
}

/* class ShockWave_Effect
 * ************************ */
ShockWave_Effect::ShockWave_Effect(const double &x, const double &y, GameEngine* parent):
    Effect (parent), item(x,y)
{
    if(parent != nullptr)   item.add_scene(&parent->scene);
}
ShockWave_Effect::~ShockWave_Effect()   {}
void ShockWave_Effect::operation(){
    if(parent == nullptr)   return ;
    item.move_one_tick();
    for(list<Redpoint>::iterator it = parent->redpoints.begin(); it != parent->redpoints.end();it ++){
        Redpoint &pt = *it;
        double len = (pt.getp() - item.getp()).getlen();
        if(len < item.getr() && len > item.getr() - 2 * WAVESPEED * ONE_TIK_TIME / 1000)
            parent->redpoints.erase(it);
    }
}
bool ShockWave_Effect::to_be_destroyed() const{    return item.to_be_destroyed; }

/* Other Effects
 * *********************** */
Boom_Effect::Boom_Effect(const double &x, const double &y, GameEngine* parent):
    Effect (parent), c(x, y, BOOM_MAX_SIZE){
    if(parent == nullptr)   return ;
    static const double dx[8] = {0, BOOM_SPECIAL_EFFECT, 0, -BOOM_SPECIAL_EFFECT, BOOM_SPECIAL_EFFECT/2, BOOM_SPECIAL_EFFECT/2, -BOOM_SPECIAL_EFFECT/2, -BOOM_SPECIAL_EFFECT/2};
    static const double dy[8] = {-BOOM_SPECIAL_EFFECT, 0, BOOM_SPECIAL_EFFECT, 0, -BOOM_SPECIAL_EFFECT, BOOM_SPECIAL_EFFECT / 2, BOOM_SPECIAL_EFFECT, -BOOM_SPECIAL_EFFECT/2};
    for(int i = 0; i < 8; ++i) {
        item[i] = new Boom(x + dx[i], y + dy[i], &parent->scene);
        item[i]->set_invisible();
    }
    index = 0;
}
Boom_Effect::~Boom_Effect()   {
    for(int i = 0; i < 8; ++i)
        delete item[i];
}
void Boom_Effect::operation() {
    if(index < 8)   {item[index++]->set_visible();}
    for(int i = 0;i < index;i ++){
        if(item[i]->getr() < BOOM_MAX_SIZE)
            item[i]->move_one_tick();
        else {
            item[i]->set_invisible();
            item[i]->to_be_destroyed = true;
        }
    }
    for(list<Redpoint>::iterator it = parent->redpoints.begin(); it != parent->redpoints.end(); ) {
        if(check_touched((*it).getc(), c)) {
            it = parent->redpoints.erase(it);
            continue;
        }
        it++;
    }

}
bool Boom_Effect::to_be_destroyed() const {
    return item[7]->to_be_destroyed;
}

