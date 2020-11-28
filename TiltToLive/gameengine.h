#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <list>
#include <algorithm>
#include "arrow.h"
#include "redpoint.h"
#include <QGraphicsScene>

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
    bool game_is_end;

    void init();

    GameEngine();
	~GameEngine();
    void move_objects();
};

#endif
