#include "gameengine.h"
#include "constants.h"
#include <list>
#include <vector>
#include <QDebug>
#include <QString>
#include <queue>

#include "object.h"
#include "effect.h"

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
    merge_redpoints();
    create_redpoints();
    tools_turn();
    reset_positions();
}

/*constructor and destructor
--------------------------------------------------------------------------------*/
GameEngine::GameEngine(): arrow(MAP_SIZE_L/2, MAP_SIZE_W/2){}

GameEngine::~GameEngine(){
    redpoints.clear();
    tools.clear();
    effects.clear();
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

void GameEngine::merge_redpoints()
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
        waitlist.push_back(pRi(Redpoint(INITIAL_REDPOINT_SIZE, INITIAL_REDPOINT_SIZE, &scene, &arrow.getp()), 1));
        waitlist.push_back(pRi(Redpoint(MAP_SIZE_L - INITIAL_REDPOINT_SIZE, MAP_SIZE_W - INITIAL_REDPOINT_SIZE, &scene, &arrow.getp()), 1));
        waitlist.push_back(pRi(Redpoint(MAP_SIZE_L - INITIAL_REDPOINT_SIZE, INITIAL_REDPOINT_SIZE, &scene, &arrow.getp()), 1));
        waitlist.push_back(pRi(Redpoint(INITIAL_REDPOINT_SIZE, MAP_SIZE_W - INITIAL_REDPOINT_SIZE, &scene, &arrow.getp()), 1));
        Creation_stage = 1;
    }

    if(Creation_stage == 2 && redpoints.size() + waitlist.size() < REDPOINT_MAX_NUMBER) {
        bool flag = (qrand() * 1.0 / RAND_MAX < REDPOINT_CREATION_CHANCE);
        if(flag)
        {
            Redpoint tmp(&scene, &arrow.getp());
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
    if(!swirl_ongoing) n_target = arrow.getp();
    //qDebug() << n_target.getx() << " " << n_target.gety();
    for(list<Redpoint>::iterator it = redpoints.begin(); it != redpoints.end();){
        //qDebug() << "begin: " << n_target.getx() << " " << n_target.gety();
        (*it).move_one_tick();
        //qDebug() << "end: " << n_target.getx() << " " << n_target.gety();
        if(check_touched(arrow, (*it))) {
            if(invince) {
                it = redpoints.erase(it);
                continue;
            }
            else
                game_is_end = true;
        }
        ++it;
    }

    for(list<Tool>::iterator it = tools.begin(); it != tools.end();  ){
        (*it).move_one_tick();
        if((*it).arrow_reached()){ //check whether a tool hits the arrow
            //delete the tools that have finished its effect
            //debug

            effects.push_back(new Boom_Effect(arrow.getp().getx(), arrow.getp().gety(), this));
            switch ((*it).operation()) {
                case Tool::ToolType::INVINCE :
                    effects.push_back(new Invince_Effect(this));
                    break;
                case Tool::ToolType::FREEZE :
                    effects.push_back(new Freeze_Effect(this));
                    break;
                case Tool::ToolType::SHOOT :
                    effects.push_back()
                case Tool::ToolType
                case Tool::ToolType
                case Tool::ToolType


            }
            it = tools.erase(it);
            qDebug() << "delete a tool that has finished its effect";
            continue;
        }
        it++;
    }

    //start now:
/*
    for(list<Gunbullet>::iterator it = gunbullets.begin(); it != gunbullets.end(); ) {
        (*it).move_one_tick();
        if((*it).touch_wall()) {
            it = gunbullets.erase(it);
            qDebug() << "delete a bullet when it touched the wall";
            continue;
        }
        it++;
    }

    for(list<Gunbullet>::iterator it = gunbullets2.begin(); it != gunbullets2.end(); ) {
        (*it).move_one_tick();
        if((*it).touch_wall()) {
            it = gunbullets2.erase(it);
            qDebug() << "delete a bullet when it touched the wall";
            continue;
        }
        it++;
    }

    for(auto it = Swirls.begin(); it != Swirls.end(); ) {
        (*it).move_one_tick();
        if((*it).getr() >= Swirl_MAX_SIZE && !(*it).holding() && !(*it).squeezing()) {
            (*it).change_sig();
            (*it).hold();
        }
        else if((*it).getr() <= INITIAL_Swirl_SIZE && (*it).squeezing()) {
            it = Swirls.erase(it);
            qDebug() << "delete a Swirl when it minimized";
            continue;
        }
        ++it;
    }
    //end here, package
*/
    for(list<Effect*>::iterator it = effects.begin(); it != effects.end(); it ++){
        (*it)->operation();
        if((*it)->to_be_destroyed())   {delete (*it); effects.erase(it);}
    }

}



void GameEngine::create_tools()
{
    using namespace std;
    static int time = 0;
    time += ONE_TIK_TIME;

    if( time <= TOOL_EMPTY_TIME) return;
    if( tools.size() < TOOL_MAX_NUMBER) {
        bool flag = (qrand() * 1.0 / RAND_MAX < TOOL_CREATION_CHANCE);//whether a new tool will be generated
        if(flag)
        {
            Tool tmp(&scene, &arrow);
            tools.push_back(tmp);        
        }
    }
}

void GameEngine::delete_tools()//to delete the tools that exceed its life span
{

    for(list<Tool>::iterator it = tools.begin(); it != tools.end(); ){
       it->clock_change();
       if( it->get_time() > TOOL_LIFE_SPAN ){
           it = tools.erase(it);
           qDebug() << "delete a tool that exceeds its life span";
           continue;
       }
       it++;
    }
}

//start here:
void GameEngine::create_bullets()
{
    using namespace std;

    if(remain_bullet <= 0) return;
    //debug
    --remain_bullet;
    qDebug() << "remain" << remain_bullet;
    Gunbullet tmp(&scene, arrow.getp().getx(), arrow.getp().gety(), arrow.get_prev());
    gunbullets.push_back(tmp);
    qDebug() << "create a new one";
}

void GameEngine::delete_bullets() {
    using namespace std;

    for(auto i = gunbullets.begin(); i != gunbullets.end(); ) {
        bool flag = false;
        for(auto j = redpoints.begin(); j != redpoints.end(); ) {
            if(check_touched((*i), (*j))) {
                flag = true;
                j = redpoints.erase(j);
                continue;
            }
            ++j;
        }
        if(flag) {
            i = gunbullets.erase(i);
            continue;
        }
        ++i;
    }
}

void GameEngine::set_invince() {
    using namespace std;
    inv_time += ONE_TIK_TIME;
    if( inv_time > INVINCE_MAX_TIME) {
        invince = false;
        arrow.set_color(0, 160, 230);
    }
}

void GameEngine::set_freeze() {
    using namespace std;
    frz_time += ONE_TIK_TIME;
    if( frz_time > FREEZE_MAX_TIME)
        for (auto it = redpoints.begin(); it != redpoints.end(); ++it) {
            (*it).un_freeze();
        }
    else {
        for (auto it = redpoints.begin(); it != redpoints.end(); ++it) {
            (*it).set_freeze();
        }
    }
}

void GameEngine::create_Swirl() {
    using namespace std;
    if(!swirl) return ;
    Swirl tmp(arrow.getp().getx(), arrow.getp().gety(), &scene);
    n_target = arrow.getp();
    Swirls.push_back(tmp);
    swirl_ongoing = true;
    swirl = false;
}

void GameEngine::create_bullet2() {
    using namespace std;
    if(!explosion) return;
    static const double dx[12] = {0, 0.5, 0.86602, 1, 0.86602, 0.5, 0,
                                  -0.5, -0.86602, -1, -0.86602, -0.5};
    static const double dy[12] = {-1, -0.86602, -0.5, 0, 0.5, 0.86602, 1,
                                  0.86602, 0.5, 0, -0.5, -0.86602};
    for(int i = 0; i < 12; ++i) {
        Gunbullet tmp(&scene, arrow.getp().getx(), arrow.getp().gety(), Vector(dx[i], dy[i]));
        gunbullets2.push_back(tmp);
    }
    explosion = false;
}

void GameEngine::delete_bullet2() {
    for(auto i = gunbullets2.begin(); i != gunbullets2.end(); ) {
        bool flag = false;
        for(auto j = redpoints.begin(); j != redpoints.end(); ) {
            if(check_touched((*i), (*j))) {
                flag = true;
                j = redpoints.erase(j);
                continue;
            }
            ++j;
        }
        if(flag) {
            i = gunbullets2.erase(i);
            continue;
        }
        ++i;
    }
}
//end here, package in tool

void GameEngine::tools_turn()			{
    delete_tools();
    create_tools();
}
