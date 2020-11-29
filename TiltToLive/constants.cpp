#include "constants.h"

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

const double SAFE_TIME =                    5000;   /* when redpoints approach, it should keep in min speed for SAFE_TIME ms before crash in arrow*/

const double ARROW_SIZE = rate *            10;
const double ARROW_SPEED = rate *           100;

const QColor REDPOINT_COLOR                 (200, 100, 100);
const QColor ARROW_COLOR                    (0, 160, 230);

const double EPSILON = 0.0000001;

const double TOOL_MAX_NUMBER =              10;
const double TOOL_CREATION_CHANCE =         0.05;
const double TOOL_SPEED = rate *            50;
