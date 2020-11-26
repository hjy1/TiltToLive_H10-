#include "GameEngine.h"
#include "constants.h"
#include <list>
#include <vector>

using std::vector;

/*overall workflow
--------------------------------------------------------------------------------*/
void GameEngine::init(){
    arrow.add_scene(&scene);
}

/*overall workflow
--------------------------------------------------------------------------------*/
void GameEngine::move_objects()
{
    //effects_turn();
    arrow_turn();
    //merge_redpoints();
    //tools_turn();
    reset_positions();
}

/*constructor and destructor
--------------------------------------------------------------------------------*/
GameEngine::GameEngine():arrow(MAP_SIZE_W/2, MAP_SIZE_L/2) {}

GameEngine::~GameEngine(){
	redpoints.clear();
}

/* Redpoints related: merge redpoints
 * find redpoints that overlap each other, merge them into one point and delete the others
 * ufds helps with enhancing efficiency
--------------------------------------------------------------------------------*/
class ufds //union-find disjoint sets
{
	public:
        vector<unsigned int> par;
        unsigned int capacity;
        ufds(): capacity(1)	{par.resize(1);}
        ~ufds()	{}

        void resize(const unsigned int& size){
			bool flag = 0;
            while(size > capacity)	{capacity <<= 1; flag = 1;}
            if(flag)
                par.resize(capacity);
		}
        unsigned int getpar(const unsigned int& x){	return par[x] == x ? x : par[x] = getpar(par[x]);}
        void connect(const unsigned int &x,const unsigned int &y)
		{
			getpar(x);
			par[par[x]] = getpar(y);
		}
};

void GameEngine::merge_redpoints() //need more test
{
	list<Redpoint>::iterator iter, iter2;
    static vector<list<Redpoint>::iterator> tar;
    static ufds par;
    unsigned int n = redpoints.size(), i,j;
	par.resize(n);
    tar.resize(n);
	for(iter = redpoints.begin(), i = 0; iter != redpoints.end(); iter ++, i++)
    {
		par.par[i] = i;
        tar[i] = iter;
	}
	for(iter = redpoints.begin(), i = 0; i < n; iter++, i++)
		for(iter2 = iter, j = i; j < n; iter2 ++, j++)
		{
			if(j == i)	continue;
			if(check_overlap(*iter, *iter2))
				par.connect(i,j);
		}
	for(iter = redpoints.begin(), i = 0; i < n; iter++, i++)
		if(par.getpar(i) != i)
		{
            (tar[par.getpar(i)])->merge(*iter);
			redpoints.erase(iter);
		}
}

/*reset_positions: let all types of objects move one tik
 * move_one_tick: virtual function first defined in Object class, will change the position variables stored in Object
 * each subclass have a rewrite one, add statement to move the GraphicItem
 * void SubClass::move_one_tick() {Object::move_one_tick(); modify_QGraphicsItem();}
--------------------------------------------------------------------------------*/
void GameEngine::reset_positions()
{
    arrow.move_one_tick();
    for(list<Redpoint>::iterator it = redpoints.begin(); it != redpoints.end(); it++)
        (*it).move_one_tick();
}


/*uncompleted functions
--------------------------------------------------------------------------------*/
void GameEngine::effects_turn()			{}
void GameEngine::arrow_turn()			{}
void GameEngine::tools_turn()			{}

