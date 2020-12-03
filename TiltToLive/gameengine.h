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
#include "boom.h"

using std::list;

class GameEngine{
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

    //boom
    bool boom = false;
    double bm_time = BOOM_TIME;
    list<Boom> booms;
    void create_boom();
    void delete_boom();

    GameEngine();
	~GameEngine();
    void move_objects();
};

#endif
