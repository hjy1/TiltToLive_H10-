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
    list<Effect*> effects;
    bool game_is_end;
    bool invince;
    bool freeze;
    Vector* redpoint_target;

    void init();
    void create_tools();
    void delete_tools();

    GameEngine();
	~GameEngine();
    void move_objects();
};

#endif
