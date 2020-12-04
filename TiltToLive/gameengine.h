#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <list>
#include <algorithm>
#include "arrow.h"
#include "redpoint.h"
#include "tool.h"
#include <QGraphicsScene>
#include "constants.h"
#include "gunbullet.h"
#include "swirl.h"
#include "shockwave.h"
#include "effect.h"

using std::list;

class GameEngine{
    friend class Effect;
private:
	void effects_turn();
	void arrow_turn();
    void merge_redpoints();
    void create_redpoints();
	void tools_turn();
    void reset_positions();

public:
    //scene should be first created!!! Or it will cause crash when deleting
    QGraphicsScene scene;
	Arrow arrow;
    list<Redpoint> redpoints;
    list<Tool> tools;
    typedef std::pair<Redpoint, int> pRi;
    list<pRi> waitlist;
    bool game_is_end;

    void init();
    void create_tools();
    void delete_tools();

    //Effects:
    list<Effect*> effects;

    //HE Jiayou
    //Gunbullets
    list<Gunbullet> gunbullets;
    int remain_bullet = 0;
    void create_bullets();
    void delete_bullets();

    //invince
    bool invince = false;
    int inv_time = INVINCE_MAX_TIME;
    void set_invince();

    //freeze
    bool freeze = false;
    int frz_time = FREEZE_MAX_TIME;
    void set_freeze();

    //Swirl
    bool swirl = false;
    bool swirl_ongoing = false;
    double bm_time = Swirl_TIME;
    list<Swirl> Swirls;
    void create_Swirl();

    //explosion
    bool explosion = false;
    list<Gunbullet> gunbullets2;
    int remain_bullet2 = 0;
    void create_bullet2();
    void delete_bullet2();

    //shockwave


    GameEngine();
	~GameEngine();
    void move_objects();
};

#endif
