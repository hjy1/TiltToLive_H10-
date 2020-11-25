#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <list>
#include <algorithm>
#include "Arrow.h"
#include "Redpoint.h"

using std::list;

class GameEngine{
	private:

	void tik_start();
	void effects_turn();
	void arrow_turn();
	void redpoint_turn();
	void tools_turn();
	void tik_end();
	void show_game_map();
	void do_delay();

	public:
	Arrow arrow;
	list<Redpoint> redpoints;

	~GameEngine();
	void run_game();
};

#endif
