#include "gameengine.h"
#include "constants.h"
#include <list>
#include <vector>
#include <QDebug>
#include <QString>
#include <queue>

using std::vector;

/*init
--------------------------------------------------------------------------------*/
void GameEngine::init(){
    game_is_end = false;
    arrow = Arrow(MAP_SIZE_L/2, MAP_SIZE_W/2);
    arrow.add_scene(&scene);
}

/*overall workflow
--------------------------------------------------------------------------------*/
void GameEngine::move_objects()
{
    //effects_turn();
    arrow_turn();
    merge_redpoints();
    create_redpoints();
    //tools_turn();
    reset_positions();
}

/*constructor and destructor
--------------------------------------------------------------------------------*/
GameEngine::GameEngine(): arrow(MAP_SIZE_L/2, MAP_SIZE_W/2){}

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

/* create_redpoints: create a redpoint in gamemap
 * will only create a redpoint when total number of points is less than REDPOINTS_MAX_NUMBER
 * -----------------------------------------------------------------------------*/
void GameEngine::create_redpoints()
{
    using namespace std;
    static int Creation_stage = 0;
    static int num_tick = round(REDPOINT_WAIT_TIME / ONE_TIK_TIME);
    if(num_tick == 0)   num_tick = 1;
    static const double dr = (256.0 - REDPOINT_COLOR.red()) / num_tick;
    static const double dg = (256.0 - REDPOINT_COLOR.green()) / num_tick;
    static const double db = (256.0 - REDPOINT_COLOR.blue()) / num_tick;

    if(Creation_stage == 0){
        waitlist.push_back(pRi(Redpoint(INITIAL_REDPOINT_SIZE, INITIAL_REDPOINT_SIZE, &scene, &arrow), 1));
        waitlist.push_back(pRi(Redpoint(MAP_SIZE_L - INITIAL_REDPOINT_SIZE, MAP_SIZE_W - INITIAL_REDPOINT_SIZE, &scene, &arrow), 1));
        waitlist.push_back(pRi(Redpoint(MAP_SIZE_L - INITIAL_REDPOINT_SIZE, INITIAL_REDPOINT_SIZE, &scene, &arrow), 1));
        waitlist.push_back(pRi(Redpoint(INITIAL_REDPOINT_SIZE, MAP_SIZE_W - INITIAL_REDPOINT_SIZE, &scene, &arrow), 1));
        Creation_stage = 1;
    }

    if(Creation_stage == 2 && redpoints.size() + waitlist.size() < REDPOINT_MAX_NUMBER) {
        bool flag = (qrand() * 1.0 / RAND_MAX < REDPOINT_CREATION_CHANCE);
        if(flag)
        {
            Redpoint tmp(&scene, &arrow);
            tmp.set_Zvalue(0);
            waitlist.push_back(pRi(tmp, 1));
        }
    }
    list<pRi>::iterator it;
    for(it = waitlist.begin();it != waitlist.end(); it++)
    {
        (*it).first.set_color(256 - dr * (*it).second, 256 - dg * (*it).second, 256 - db * (*it).second);
        (*it).second ++;
    }
    while(!waitlist.empty() && waitlist.begin()->second > num_tick){
        redpoints.push_back(waitlist.begin()->first);
        waitlist.pop_front();
    }
    if(Creation_stage == 1 && waitlist.empty())
        Creation_stage = 2;
}

/*reset_positions: let all types of objects move one tik
 * move_one_tick: virtual function first defined in Object class, will change the position variables stored in Object
 * each subclass have a rewrite one, add statement to move the GraphicItem
 * void SubClass::move_one_tick() {Object::move_one_tick(); modify_QGraphicsItem();}
--------------------------------------------------------------------------------*/
void GameEngine::reset_positions()
{
    arrow.move_one_tick();
    for(list<Redpoint>::iterator it = redpoints.begin(); it != redpoints.end(); it++){
        (*it).move_one_tick();
        if((*it).target_reached())
            game_is_end = true;
    }
}


/*uncompleted functions
--------------------------------------------------------------------------------*/
void GameEngine::effects_turn()			{}
void GameEngine::arrow_turn()			{}
void GameEngine::tools_turn()			{}

