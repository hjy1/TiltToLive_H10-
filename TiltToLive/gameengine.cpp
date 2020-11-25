#include "GameEngine.h"
#include <list>
#include <vector>

using std::vector;

GameEngine::~GameEngine(){
	redpoints.clear();
}

class ufds //union-find disjoint sets
{
	public:
        vector<int> par;
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
}par;

void tik_start()			{}
void effects_turn()			{}
void arrow_turn()			{}


void GameEngine::redpoint_turn() //need more test
{
	list<Redpoint>::iterator iter, iter2;
    static vector<Redpoint*> tar;
	int n = redpoints.size(), i,j;
	par.resize(n);
    tar.resize(n);
	for(iter = redpoints.begin(), i = 0; iter != redpoints.end(); iter ++, i++)
	{
		iter->move_one_tik();
		par.par[i] = i;
        tar[i] = &*iter;
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
            tar[par.getpar(i)]->merge(*iter);
			redpoints.erase(iter);
		}
}



void tools_turn()			{}
void tik_end()				{}
void show_game_map()		{}
void do_delay()				{}

void GameEngine::run_game()
{
	while(true)
	{
		tik_start();
		effects_turn();
 		arrow_turn();
 		redpoint_turn();
 		tools_turn();
 		tik_end();
		show_game_map();
 		do_delay();
	}
}
