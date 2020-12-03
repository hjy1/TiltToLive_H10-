#include "constants.h"
#include <QString>
#include "tool.h"

//constants
static const double rate = 2.0;

double MAP_SIZE_L = rate *            360;
double MAP_SIZE_W = rate *            640;

const double ONE_TIK_TIME =                 30;      /* ms */

const double INITIAL_REDPOINT_SIZE = rate * 5;
const double REDPOINT_ACCELERATION =        50;
const double REDPOINT_DECCELERATION =       100;
const double REDPOINT_SPEED_MAX = rate *    100;
const double REDPOINT_SPEED_MIN = rate *    10;
const double REDPOINT_CREATION_CHANCE =     0.1;    /* for each tick game engine has a chance of REDPOINT_CREATION_CHANCE to create a redpoint*/
const double REDPOINT_MAX_NUMBER =          20;
const double REDPOINT_WAIT_TIME =           3000;   /* ms */

const double INITIAL_BULLET_SIZE = rate *   3;
const double INITIAL_BULLET_SPEED = rate *  300;
const double INITIAL_BULLET_AMOUNT =        100;

const double INITIAL_BOOM_SIZE = rate *     2;
const double BOOM_MAX_SIZE = rate *         52;
const double BOOM_R_CHANGE_SPEED = rate *   10;
const double BOOM_TIME =                    0;

const int INVINCE_MAX_TIME =                3000;

const int FREEZE_MAX_TIME =                 4000;

const double WAVELENTH = rate *             5;
const double WAVESPEED = rate *             100;

const double SAFE_TIME =                    5000;   /* when redpoints approach, it should keep in min speed for SAFE_TIME ms before crash in arrow*/

const double ARROW_SIZE = rate *            10;
const double ARROW_SPEED = rate *           100;

const QColor REDPOINT_COLOR                 (200, 100, 100);
const QColor ARROW_COLOR                    (0, 160, 230);
const QColor GUNBULLET_COLOR                (0, 255, 0);
const QColor BOOM_COLOR                     (255, 255, 0);
const QColor WAVE_COLOR                     (20,20,200);

const double EPSILON = 0.0000001;

const double TOOL_SIZE = rate *             15;
const double TOOL_MAX_NUMBER =              5;
const double TOOL_CREATION_CHANCE =         0.020;
const double TOOL_SPEED = rate *            30;
const double TOOL_LIFE_SPAN =               15000;  /* ms */
const double TOOL_EMPTY_TIME =              8000;   /* ms */


const int Tool::TYPENUM = 7;
const QString Tool::tool_image_lookup[] = { ":/resources/tools/invince.png",
                                       ":/resources/tools/freeze.png",
                                       ":/resources/tools/shoot.png",
                                       ":/resources/tools/boom.png",
                                       ":/resources/tools/explosion.png",
                                       ":/resources/tools/swirl.png",
                                       ":/resources/tools/shockwave.png",
                                     };
